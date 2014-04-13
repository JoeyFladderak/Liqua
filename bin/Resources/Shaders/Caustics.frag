#version 330

in vec2 TexCoord0;
in vec3 Normal0;
in vec4 WPos0;
in vec4 TexCoordProj;

out vec4 FragColor;

uniform vec3 Ambient;
uniform vec3 WaterColor;

uniform vec3 SunLightColor;
uniform vec3 SunLightPosition;
uniform float SunConstantAttenuation;
uniform float SunLinearAttenuation;
uniform float SunQuadraticAttenuation;

uniform vec3 ProjectedLightColor;
uniform vec3 ProjectedLightPosition;
uniform float ProjectedLightIntensity;
uniform float ProjectedConstantAttenuation;
uniform float ProjectedLinearAttenuation;
uniform float ProjectedQuadraticAttenuation;

float ConstantAttenuation;
float LinearAttenuation;
float QuadraticAttenuation;

uniform float WaterLevel;

uniform vec3 EyePosition;

uniform vec3 DiffuseColor;
uniform vec3 AmbientColor;
uniform float Shininess;

uniform sampler2D DiffuseMap;
uniform sampler2D CausticMap;
uniform sampler2D SpecularMap;
 
float Attenuation(vec3 P, vec3 LightPos)
{
	float d = distance(P, LightPos);
	return 1 / (ConstantAttenuation + LinearAttenuation * d + QuadraticAttenuation * d * d);
}

vec4 CalcPhong(vec3 eyepos, vec3 position, vec3 normal, float shininess, vec3 LightPos, vec3 LightCol)
{
	vec3 L = normalize(LightPos - position);
	vec3 V = normalize(eyepos - position);
	vec3 H = normalize(L + V);
	float A = Attenuation(position, LightPos);

	float dotstep = dot(normal, H);
	float maxstep = max(dotstep, 0.0);
	float S = pow(maxstep, shininess);

	return vec4(LightCol * S * A, 0);
}

vec4 CalcLambert(vec3 position, vec3 normal, vec3 LightPos, vec3 LightCol)
{
	vec3 L = normalize(LightPos - position);
	float A = Attenuation(position, LightPos);
	float D = clamp(dot(normal, L), 0.0, 1.0);

	return vec4(LightCol * D * A, 0);
}

void main(void)
{
	vec4 diffuse = texture2D(DiffuseMap, TexCoord0.xy);
	vec4 specular = texture2D(SpecularMap, TexCoord0.xy);
	
	vec4 diffuselight;
	vec4 specularlight;

	vec4 FinalColor;

	if(WPos0.y <= WaterLevel)
	{
		ConstantAttenuation = ProjectedConstantAttenuation;
		LinearAttenuation = ProjectedLinearAttenuation;
		QuadraticAttenuation = ProjectedQuadraticAttenuation;

		diffuselight = CalcLambert(WPos0.xyz, Normal0, ProjectedLightPosition, ProjectedLightColor);
		specularlight = CalcPhong(EyePosition, WPos0.xyz, Normal0, 10, ProjectedLightPosition, ProjectedLightColor);

		vec4 AmbientFinal = vec4(Ambient, 1.0f) * vec4(AmbientColor, 1.0);
		vec4 DiffuseFinal = diffuse * diffuselight;
		vec4 SpecularFinal = specular * specularlight;

		vec4 ProjTexColor = vec4(1, 1, 1, 1);
		if(TexCoordProj.w > 0)
		{
			ProjTexColor = texture2DProj(CausticMap, TexCoordProj);
		}

		// Taken from http://www.ozone3d.net/tutorials/glsl_fog/index.php
		const float log2 = 1.442695;
		float z = gl_FragCoord.z / gl_FragCoord.w;
		float fogFactor = exp2(-0.01 * 0.01 * z * z * log2);
		fogFactor = clamp(fogFactor, 0.0, 1.0);

		float colorDarkener = (0 - WPos0.y) / 250;
		colorDarkener = 1 - clamp(colorDarkener, 0.0, 1.0);

		FinalColor = mix(vec4(WaterColor, 1) * colorDarkener, (ProjTexColor * (AmbientFinal + (DiffuseFinal + SpecularFinal) * ProjectedLightIntensity)), fogFactor);
		FinalColor.a = 1;
	}
	else
	{
		ConstantAttenuation = SunConstantAttenuation;
		LinearAttenuation = SunLinearAttenuation;
		QuadraticAttenuation = SunQuadraticAttenuation;

		diffuselight = CalcLambert(WPos0.xyz, Normal0, SunLightPosition, SunLightColor);
		specularlight = CalcPhong(EyePosition, WPos0.xyz, Normal0, 10.0, SunLightPosition, SunLightColor);

		vec4 AmbientFinal = vec4(Ambient, 1.0f) * vec4(AmbientColor, 1.0);
		vec4 DiffuseFinal = diffuse * diffuselight;
		vec4 SpecularFinal = specular * specularlight;

		FinalColor = AmbientFinal + (DiffuseFinal + SpecularFinal);
		FinalColor.a = diffuse.a;	
	}
	
	FragColor = FinalColor;
}
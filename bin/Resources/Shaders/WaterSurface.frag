#version 330

in vec2 TexCoord0;
in vec3 Normal0;
in vec4 WPos0;
in vec4 Pos;
in vec3 Tangent;
in vec3 Binormal;

uniform sampler2D normalMap;
uniform vec3 CamPos;
uniform vec3 WaterColor;
uniform float UVOffset;

uniform vec3 SunLightColor;
uniform vec3 SunLightPosition;
uniform vec3 SunLightDirection;
uniform float SunConstantAttenuation;
uniform float SunLinearAttenuation;
uniform float SunQuadraticAttenuation;

out vec4 FragColor;

float texwidth = 1.0f/512 * 10;

vec3 expand(vec3 v)
{
	return (v - 0.5) * 2;
}

float Attenuation(vec3 P)
{
	float d = distance(P, SunLightPosition);
	return 1 / (SunConstantAttenuation + SunLinearAttenuation * d + SunQuadraticAttenuation * d * d);
}

vec4 CalcPhong(vec3 eyepos, vec3 position, vec3 normal, float shininess)
{
	vec3 L = normalize(SunLightPosition - position);
	vec3 V = normalize(eyepos - position);
	vec3 H = normalize(L + V);
	float A = Attenuation(position);

	float dotstep = dot(normal, H);
	float maxstep = max(dotstep, 0.0);
	float S = pow(maxstep, shininess);

	return vec4(SunLightColor * S * A, 0);
}

vec4 CalcLambert(vec3 position, vec3 normal)
{
	vec3 L = normalize(SunLightDirection );
	float A = Attenuation(position);
	float D = clamp(dot(normal, L), 0.0, 1.0);

	return vec4(SunLightColor * D * A, 0);
}

void main(void)
{
	mat3 tangentMatrix = mat3(normalize(Tangent), normalize(Binormal), normalize(Normal0));
	
	vec4 normalTex = (texture2D(normalMap, TexCoord0));
	normalTex += texture2D(normalMap, (TexCoord0 + vec2(texwidth, 0)) + UVOffset * 3.1);
	normalTex += texture2D(normalMap, (-TexCoord0 + vec2(-texwidth, 0)) + UVOffset * 5.2);
	normalTex += texture2D(normalMap, (TexCoord0 + vec2(0, texwidth)) + UVOffset * 1.3);
	normalTex += texture2D(normalMap, (-TexCoord0 + vec2(0, -texwidth)) + UVOffset * 4.8);
	vec3 N = normalize(normalTex.xyz);
	
	N = normalize(tangentMatrix * N);

	vec3 V = normalize(CamPos - WPos0.xyz);
	
	float fresnel = dot(V, N);
	
	vec4 diffuselight = CalcLambert(WPos0.xyz, N);
	vec4 specularlight = CalcPhong(CamPos, WPos0.xyz, N, 100.0);
	
	vec4 diffuseCol = vec4(WaterColor, 1) * diffuselight;
	vec4 speccol = vec4(1, 1, 1, 1) * specularlight;
	
	vec4 final = diffuseCol + speccol;
	
	FragColor = final;
	FragColor.a = 1;
}
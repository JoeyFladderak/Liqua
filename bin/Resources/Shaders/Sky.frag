#version 330

out vec4 FragColor;

uniform vec3 WaterColor;
uniform sampler2D SkyGradient;

in vec2 TexCoord0;
in vec4 WPos0;
in vec4 Pos;

void main(void)
{
	if(WPos0.y < 0)
	{
		// Taken from http://www.ozone3d.net/tutorials/glsl_fog/index.php
		const float log2 = 1.442695;
		float z = gl_FragCoord.z / gl_FragCoord.w;
		float fogFactor = exp2(-0.01 * 0.01 * z * z * log2);
		fogFactor = clamp(fogFactor, 0.0, 1.0);

		float colorDarkener = (0 - WPos0.y) / 500;
		colorDarkener = clamp(colorDarkener, 0.0, 1.0);

		FragColor = mix(vec4(WaterColor, 1)  * (1 - colorDarkener ), vec4(WaterColor, 1), fogFactor);
	}
	else
	{
		vec2 skyUV = vec2(Pos.y * 0.5, 0);

		FragColor = clamp(texture2D(SkyGradient, skyUV), 0, 1);
	}
	
	FragColor.a = 1;
}
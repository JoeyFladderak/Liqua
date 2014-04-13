#version 330

in vec2 TexCoord0;
in vec3 Normal0;
in vec3 WPos0;

uniform sampler2D Texture;

out vec4 FragColor;

void main(void)
{
	vec4 Color = texture2D(Texture, TexCoord0.xy);
	FragColor = Color;
}
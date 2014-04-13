#version 330

layout (location = 0) in vec3 Position;

out vec2 TexCoord0;

void main(void)
{
	gl_Position = vec4(Position, 1.0);
	TexCoord0 = (Position.xy + vec2(1, 1)) / 2.0;
} 
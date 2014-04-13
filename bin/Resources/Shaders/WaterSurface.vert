#version 330

layout (location = 0) in vec3 Position;
layout (location = 1) in vec2 TexCoord;
layout (location = 2) in vec3 Normal; 

uniform mat4 ModelViewProjection;
uniform mat4 ModelMatrix;

out vec2 TexCoord0;
out vec3 Normal0;
out vec3 Tangent;
out vec3 Binormal;
out vec4 WPos0;
out vec4 Pos;

void main(void)
{
	gl_Position = ModelViewProjection * vec4(Position.x, Position.y, Position.z, 1.0);
	TexCoord0 = TexCoord;
	Normal0 = vec3(0, 1, 0);
	WPos0 = (ModelMatrix * vec4(Position, 1.0));
	Pos = vec4(Position, 1.0);
	Tangent = vec3(1, 0, 0);
	Binormal = cross(Normal0, Tangent);
}
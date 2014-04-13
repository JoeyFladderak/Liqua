#version 330

layout (location = 0) in vec3 Position;

uniform mat4 MeshViewProjection;

void main(void)
{
	gl_Position = MeshViewProjection * vec4(Position.x, Position.y, Position.z, 1.0);
}
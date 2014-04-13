#version 330

layout (location = 0) in vec3 Position;
layout (location = 1) in vec2 TexCoord;
layout (location = 2) in vec3 Normal;

uniform mat4 ModelViewProjection;
uniform mat4 ModelMatrix;
uniform mat4 TextureMatrix;

out vec2 TexCoord0;
out vec3 Normal0;
out vec4 WPos0;
out vec4 TexCoordProj;

void main(void)
{
 	gl_Position = ModelViewProjection * vec4(Position.x, Position.y, Position.z, 1.0);
 	TexCoord0 = TexCoord;
 	Normal0 = (ModelMatrix * vec4(Normal, 0.0)).xyz;
 	WPos0 = (ModelMatrix * vec4(Position.x, Position.y, Position.z, 1.0));
 
 	TexCoordProj = TextureMatrix * vec4(Position.x, Position.y, Position.z, 1.0);
}
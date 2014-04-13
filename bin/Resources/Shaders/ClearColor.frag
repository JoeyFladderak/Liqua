#version 330

out vec4 FragColor;

uniform vec3 Col;

void main(void)
{
	FragColor = vec4(Col, 1);
}
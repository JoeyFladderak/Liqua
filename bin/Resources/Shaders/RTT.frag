#version 330

in vec2 TexCoord0;
out vec4 FragColor;

uniform sampler2D RenderTarget;

float ZfromDepth( float depth, float zNear, float zFar )
{
	// source: http://olivers.posterous.com/linear-depth-in-glsl-for-real
	// OpenGL only!
	return 2*zFar*zNear / (zFar + zNear - (zFar - zNear)*(2*depth -1));
}

void main(void)
{
	FragColor = texture2D(RenderTarget, TexCoord0.xy);
}
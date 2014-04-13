#version 330

in vec2 TexCoord0;
in vec3 Normal0;
in vec4 WPos0;

uniform sampler2D AlphaGradient;
uniform float Scroll;
uniform float Pulse;

uniform vec3 CamPos;
uniform vec3 ShaftPos;

out vec4 FragColor;

void main(void)
{
	vec2 uv = TexCoord0;
	uv.x += Scroll;

	vec4 Alpha = texture2D(AlphaGradient, uv);
	float decay = TexCoord0.y;
	float decayX = 1;
	float distanceDecay = 1;

	if(distance(CamPos, ShaftPos) < 150)
	{
		distanceDecay = distance(CamPos, ShaftPos) / 150;
	}

  	if(TexCoord0.y >= 0.8)
  	{
  		decay = (1.0 - TexCoord0.y) * 4;
  	}
	if(TexCoord0.x >= 0.8)
  	{
  		decayX = (1.0 - TexCoord0.x) * 4;
  	}
	if(TexCoord0.x <= 0.2)
  	{
  		decayX = (0.0 + TexCoord0.x) * 4;
  	}
	
	Alpha *= (decay * decayX) * ( 1 - distanceDecay );
	FragColor = vec4(1, 1, 1, Alpha.x * Pulse);
}
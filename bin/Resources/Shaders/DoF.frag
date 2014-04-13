#version 330

in vec2 TexCoord0;
out vec4 FragColor;

uniform sampler2D RenderTarget;
uniform sampler2D DepthTexture;
uniform vec2 Samples[64];
uniform float MinRange;
uniform float MaxRange;
uniform float BlurSize;
uniform int UnderWater;

float ZfromDepth( float depth, float zNear, float zFar )
{
	// source: http://olivers.posterous.com/linear-depth-in-glsl-for-real
	// OpenGL only!
	return 2*zFar*zNear / (zFar + zNear - (zFar - zNear)*(2*depth -1));
}

float CalculateBlurriness(float curpixelz, float minrange, float maxrange)
{
	return (clamp( (curpixelz  - minrange) / (maxrange - minrange), 0, 1 ) * 2) - 1;
}

void main(void)
{
	float curpixeldepth = texture2D(DepthTexture, TexCoord0.xy).r;
	float curpixelz = abs(ZfromDepth(curpixeldepth, 0.1, 5000));
	
	float blurriness = CalculateBlurriness(curpixelz, MinRange, MaxRange);
	
	float totalweight = 1.0;
	vec4 finalColor = texture2D(RenderTarget, TexCoord0.xy);

	if(UnderWater == 1)
	{
		for(int i = 0; i < 64; i++)
		{
			vec2 sampleUV = TexCoord0.xy + Samples[i] * abs(blurriness) * BlurSize;
		
			vec4 sampleColor = texture2D(RenderTarget, sampleUV);
			float sampleDepth = texture2D(DepthTexture, sampleUV).r;
		
			float sampleZ = abs(ZfromDepth(sampleDepth, 0.1, 5000));
			float sampleBlurriness = CalculateBlurriness(sampleZ, MinRange, MaxRange);
		
			float sampleWeight = 1.0;
			if(sampleDepth < curpixelz)
			{
				sampleWeight = abs(sampleBlurriness);
			}
		
			totalweight += sampleWeight;
			finalColor += sampleColor * sampleWeight;
		}
	}
		
	FragColor = (finalColor / totalweight);
}
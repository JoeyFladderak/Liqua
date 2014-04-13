#include "Liqua.h"
#include "RenderTarget.h"

// Taken from the Nils Engine
// Credit to Nils Desle

Liqua::RenderTarget::RenderTarget()
{

}

Liqua::RenderTarget::RenderTarget( int a_Width, int a_Height, int a_RenderTargetAmount )
{
	Init(a_Width, a_Height, a_RenderTargetAmount);
}

Liqua::RenderTarget::~RenderTarget()
{

}

void Liqua::RenderTarget::Init( int a_Width, int a_Height, int a_RenderTargetAmount )
{
	m_RenderTargetsAmount = a_RenderTargetAmount;

	glGenFramebuffers(1, &m_FBO); CheckGL();
	glBindFramebuffer(GL_FRAMEBUFFER, m_FBO); CheckGL();

	for(unsigned int i = 0; i < m_RenderTargetsAmount; i++)
	{
		glGenTextures(1, &(m_Texture[i]));
		glBindTexture(GL_TEXTURE_2D, m_Texture[i]);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE); // automatic mipmap generation included in OpenGL v1.4

		GLenum pixelType = GL_UNSIGNED_BYTE;
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, a_Width, a_Height, 0, GL_RGBA, pixelType, 0);
		glBindTexture(GL_TEXTURE_2D, 0);

		// attach a texture to FBO color attachment point
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0+i, GL_TEXTURE_2D, m_Texture[i], 0); CheckGL();
	}

	glGenTextures(1, &m_DepthBuffer);
	glBindTexture(GL_TEXTURE_2D, m_DepthBuffer);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, a_Width, a_Height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_DepthBuffer, 0);

	// check FBO status
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if(status != GL_FRAMEBUFFER_COMPLETE)
	{
		printf("Error creating framebuffer!");
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Liqua::RenderTarget::Activate()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
}

void Liqua::RenderTarget::Deactivate()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Liqua::RenderTarget::BindTexture( unsigned int a_Index )
{
	glBindTexture(GL_TEXTURE_2D, m_Texture[a_Index]);
}

void Liqua::RenderTarget::BindDepthBuffer()
{
	glBindTexture(GL_TEXTURE_2D, m_DepthBuffer);
}

void Liqua::RenderTarget::InitAsShadowBuffer( int a_Width, int a_Height )
{
	int shadowMapWidth = SCRWIDTH;
	int shadowMapHeight = SCRHEIGHT;

	GLenum FBOstatus;

	// Try to use a texture depth component
	glGenTextures(1, &m_DepthBuffer);
	glBindTexture(GL_TEXTURE_2D, m_DepthBuffer);

	// GL_LINEAR does not make sense for depth texture. However, next tutorial shows usage of GL_LINEAR and PCF. Using GL_NEAREST
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// This is to allow usage of shadow2DProj function in the shader
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_INTENSITY);

	// Remove artifact on the edges of the shadowmap
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );

	// No need to force GL_DEPTH_COMPONENT24, drivers usually give you the max precision if available
	glTexImage2D( GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadowMapWidth, shadowMapHeight, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	// create a framebuffer object
	glGenFramebuffersEXT(1, &m_FBO);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_FBO);

	// Instruct openGL that we won't bind a color texture with the currently bound FBO
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	// attach the texture to FBO depth attachment point
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT,GL_TEXTURE_2D, m_DepthBuffer, 0);

	// check FBO status
	FBOstatus = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	if(FBOstatus != GL_FRAMEBUFFER_COMPLETE_EXT)
		printf("GL_FRAMEBUFFER_COMPLETE_EXT failed, CANNOT use FBO\n");

	// switch back to window-system-provided framebuffer
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}

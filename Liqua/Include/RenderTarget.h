#ifndef _RENDERTARGET_H_
#define _RENDERTARGET_H_

namespace Liqua
{
	class LIQUAEXPORT RenderTarget
	{
	public:

		RenderTarget();
		RenderTarget(int a_Width, int a_Height, int a_RenderTargetAmount);
		~RenderTarget();

		void Init(int a_Width, int a_Height, int a_RenderTargetAmount);
		void InitAsShadowBuffer(int a_Width, int a_Height);

		void Activate();
		void Deactivate();

		void BindTexture(unsigned int a_Index);
		void BindDepthBuffer();

	protected:

		GLuint m_FBO;
		GLuint m_Texture[4];
		GLuint m_DepthBuffer;

		unsigned int m_RenderTargetsAmount;
	};
}
#endif
#ifndef _SHADER_H_
#define _SHADER_H_

namespace Liqua
{
	class LIQUAEXPORT Shader
	{
	public:

		Shader();
		~Shader();

		bool CreateShader();

		bool AttachVertexShader(const std::string& a_File);
		bool AttachFragmentShader(const std::string& a_File);

		bool LinkShader();

		void Bind();
		void Unbind();

		void SetUniformMatrix(const char* a_Uniform, const float* a_Val);
		void SetUniformMatrixv(const char* a_Uniform, const int a_Size, const float* a_Val);

		void SetUniform1f(const char* a_Uniform, float a_Val);
		void SetUniform1fv(const char* a_Uniform, const int a_Size, const float* a_Val);
		void SetUniform2fv(const char* a_Uniform, const int a_Size, const float* a_Val);
		void SetUniform2f(const char* a_Uniform, const float* a_Val);
		void SetUniform3f(const char* a_Uniform, const float* a_Val);
		void SetUniform4f(const char* a_Uniform, const float* a_Val);

		void SetUniform1i(const char* a_Uniform, int a_Val);
		void SetUniform2i(const char* a_Uniform, const int* a_Val);
		void SetUniform3i(const char* a_Uniform, const int* a_Val);
		void SetUniform4i(const char* a_Uniform, const int* a_Val);

		void SetUniform1d(const char* a_Uniform, double a_Val);
		void SetUniform2d(const char* a_Uniform, const double* a_Val);
		void SetUniform3d(const char* a_Uniform, const double* a_Val);
		void SetUniform4d(const char* a_Uniform, const double* a_Val);

		GLuint GetShaderID() {return m_ShaderID;}
		GLuint GetVertexID() {return m_VertexProgram;}
		GLuint GetFragmentID() {return m_FragmentProgram;}

	protected:

		bool LoadShader(const std::string& a_File);
		void CheckForErrors(GLuint a_Shader, GLenum a_CheckStatus);

		GLuint m_VertexProgram;
		GLuint m_FragmentProgram;
		GLuint m_ShaderID;
		GLenum m_ShaderType;
	};
}
#endif
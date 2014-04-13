#include "Liqua.h"
#include "Shader.h"

Liqua::Shader::Shader()
{
	m_FragmentProgram = 0;
	m_VertexProgram = 0;
	m_ShaderID = 0;
	m_ShaderType = 0;

	//CreateShader();
}

Liqua::Shader::~Shader()
{
	glDeleteShader(m_VertexProgram);
	glDeleteShader(m_FragmentProgram);
	glDeleteProgram(m_ShaderID);
}

bool Liqua::Shader::LoadShader( const std::string& a_File )
{
	//Valid file?
	std::ifstream file(a_File);
	if(!file.is_open())
	{
		// Could not read file
		printf("Could not open file: %s: \n", a_File.c_str());
		return false;
	}

	// get the name
	// note that std::string (and probably every other std classes) might give some trouble when exporting to a dll as it is a non standard across differen compilers
	// even though it is the "standard" template library.. Although in this us of std functionality there will most likely be no problem due to non different compilers
	// but just to be safe, gonna put it here.
	std::string name = PathFindFileName(a_File.c_str());

	//Determine shader type by extension
	std::string extenstion = PathFindExtension(a_File.c_str());
	if(extenstion.compare(".vert") == 0)
	{
		// .vert extension, vertex shader
		m_ShaderType = GL_VERTEX_SHADER;
	}
	else if(extenstion.compare(".frag") == 0)
	{
		// .frag extenstion, fragment shader
		m_ShaderType = GL_FRAGMENT_SHADER;
	}
	else
	{
		// not a valid shader
		printf("%s is not a valid shader extension. Use .vert of .frag\n", extenstion.c_str());
		return false;
	}

	// read out the source and get the file length
	std::string program(std::istreambuf_iterator<char>(file),  (std::istreambuf_iterator<char>()));
	const char* source = program.c_str();

	// create the shader
	GLuint id = glCreateShader(m_ShaderType); //CheckGL();
	if(id != 0)
	{
		// Shader can be created, so do it
		glShaderSource(id, 1, &source, NULL); //CheckGL();
		glCompileShader(id); //CheckGL();
		CheckForErrors(id, GL_COMPILE_STATUS);
	}
	else
	{
		// Could not create shader
		printf("Could not create shader: %s\n", name.c_str());
		return false;
	}

	if(m_ShaderType == GL_VERTEX_SHADER)
	{
		m_VertexProgram = id;
		glAttachShader(m_ShaderID, m_VertexProgram); //CheckGL();
	}
	else
	{
		m_FragmentProgram = id;
		glAttachShader(m_ShaderID, m_FragmentProgram); //CheckGL();
	}

	return true;
}

void Liqua::Shader::CheckForErrors(GLuint a_Shader, GLenum a_CheckStatus )
{
	GLint success = 0;
	glGetShaderiv(a_Shader, a_CheckStatus, &success);// CheckGL();
	if (!success) {
		char InfoLog[1024];
		glGetShaderInfoLog(a_Shader, 1024, NULL, InfoLog); //CheckGL();
		printf("%s\n", InfoLog);
	}
}

bool Liqua::Shader::CreateShader()
{
	m_ShaderID = glCreateProgram(); //CheckGL();
	if(m_ShaderID == 0)
	{
		// Failed to create shader
		printf("Failed to create program\n");
		return false;
	}
	return true;
}

bool Liqua::Shader::AttachVertexShader( const std::string& a_File )
{
	return LoadShader(a_File);
}

bool Liqua::Shader::AttachFragmentShader( const std::string& a_File )
{
	return LoadShader(a_File);
}

bool Liqua::Shader::LinkShader()
{
	// link it
	glLinkProgram(m_ShaderID); //CheckGL();
	GLint Success = 0;
	GLchar ErrorLog[1024] = { 0 };
	glGetProgramiv(m_ShaderID, GL_LINK_STATUS, &Success);
	if (Success == 0) {
		glGetProgramInfoLog(m_ShaderID, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
	}
	 
	// validate it
 	glValidateProgram(m_ShaderID);// CheckGL();
	glGetProgramiv(m_ShaderID, GL_VALIDATE_STATUS, &Success);
	if (Success == 0) {
		glGetProgramInfoLog(m_ShaderID, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
	}

	return true;
}

void Liqua::Shader::Bind()
{
	glUseProgram(m_ShaderID); //CheckGL();
}

void Liqua::Shader::Unbind()
{
	glUseProgram(0);// CheckGL();
}

void Liqua::Shader::SetUniformMatrix( const char* a_Uniform, const float* a_Val )
{
	GLuint uniform = glGetUniformLocation(m_ShaderID, a_Uniform);
	glUniformMatrix4fv(uniform, 1, GL_FALSE, a_Val);
}

void Liqua::Shader::SetUniformMatrixv( const char* a_Uniform, const int a_Size, const float* a_Val )
{
	GLuint uniform = glGetUniformLocation(m_ShaderID, a_Uniform);
	glUniformMatrix4fv(uniform, a_Size, GL_FALSE, a_Val);
}

void Liqua::Shader::SetUniform1f( const char* a_Uniform, float a_Val )
{
	GLuint uniform = glGetUniformLocation(m_ShaderID, a_Uniform);
	glUniform1f(uniform, a_Val);
}

void Liqua::Shader::SetUniform1fv( const char* a_Uniform, const int a_Size, const float* a_Val )
{
	GLuint uniform = glGetUniformLocation(m_ShaderID, a_Uniform);
	glUniform1fv(uniform, a_Size, a_Val);
}

void Liqua::Shader::SetUniform2f( const char* a_Uniform, const float* a_Val )
{
	GLuint uniform = glGetUniformLocation(m_ShaderID, a_Uniform);
	glUniform2fv(uniform, 1, a_Val);
}

void Liqua::Shader::SetUniform2fv( const char* a_Uniform, const int a_Size, const float* a_Val )
{
	GLuint uniform = glGetUniformLocation(m_ShaderID, a_Uniform);
	glUniform2fv(uniform, a_Size, a_Val);
}

void Liqua::Shader::SetUniform3f( const char* a_Uniform, const float* a_Val )
{
	GLuint uniform = glGetUniformLocation(m_ShaderID, a_Uniform);
	glUniform3fv(uniform, 1, a_Val);
}

void Liqua::Shader::SetUniform4f( const char* a_Uniform, const float* a_Val )
{
	GLuint uniform = glGetUniformLocation(m_ShaderID, a_Uniform);
	glUniform4fv(uniform, 1, a_Val);
}

void Liqua::Shader::SetUniform1i( const char* a_Uniform, int a_Val )
{
	GLuint uniform = glGetUniformLocation(m_ShaderID, a_Uniform);
	glUniform1i(uniform, a_Val);
}

void Liqua::Shader::SetUniform2i( const char* a_Uniform, const int* a_Val )
{
	GLuint uniform = glGetUniformLocation(m_ShaderID, a_Uniform);
	glUniform2iv(uniform, 1, a_Val);
}

void Liqua::Shader::SetUniform3i( const char* a_Uniform, const int* a_Val )
{
	GLuint uniform = glGetUniformLocation(m_ShaderID, a_Uniform);
	glUniform3iv(uniform, 1, a_Val);
}

void Liqua::Shader::SetUniform4i( const char* a_Uniform, const int* a_Val )
{
	GLuint uniform = glGetUniformLocation(m_ShaderID, a_Uniform);
	glUniform4iv(uniform, 1, a_Val);
}

void Liqua::Shader::SetUniform1d( const char* a_Uniform, double a_Val )
{
	GLuint uniform = glGetUniformLocation(m_ShaderID, a_Uniform);
	glUniform1d(uniform, a_Val);
}

void Liqua::Shader::SetUniform2d( const char* a_Uniform, const double* a_Val )
{
	GLuint uniform = glGetUniformLocation(m_ShaderID, a_Uniform);
	glUniform2dv(uniform, 1, a_Val);
}

void Liqua::Shader::SetUniform3d( const char* a_Uniform, const double* a_Val )
{
	GLuint uniform = glGetUniformLocation(m_ShaderID, a_Uniform);
	glUniform3dv(uniform, 1, a_Val);
}

void Liqua::Shader::SetUniform4d( const char* a_Uniform, const double* a_Val )
{
	GLuint uniform = glGetUniformLocation(m_ShaderID, a_Uniform);
	glUniform4dv(uniform, 1, a_Val);
}
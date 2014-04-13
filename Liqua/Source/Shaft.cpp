#include "Liqua.h"
#include "Shader.h"
#include "Mesh.h"
#include "soil/SOIL.h"
#include "Shaft.h"

Liqua::Shaft::Shaft(float a_Width, float a_Height)
{
	// creation of a plane used for the shafts
	m_Vertices[0] = glm::vec3(-(a_Width / 2.0f), -a_Height, 0); // left bottom 
	m_Vertices[1] = glm::vec3(a_Width / 2.0f, -a_Height, 0); // right bottom 
	m_Vertices[2] = glm::vec3(-(a_Width / 2.0f), 0, 0); // left top 
	m_Vertices[3] = glm::vec3(a_Width / 2.0f, 0, 0); // right top 

	// and its UV coordinates
	m_UVs[0] = glm::vec2(0.0f, 0.0f);
	m_UVs[1] = glm::vec2(1.0f, 0.0f);
	m_UVs[2] = glm::vec2(0.0f, 1.0f);
	m_UVs[3] = glm::vec2(1.0f, 1.0f);

	// Index based rendering, the needed indices.
	m_Indices[0] = 0;
	m_Indices[1] = 1;
	m_Indices[2] = 2;
	m_Indices[3] = 2;
	m_Indices[4] = 1;
	m_Indices[5] = 3;

	m_ModelMatrix = glm::mat4(1);
	m_Translation = glm::mat4(1);
	m_Rotation = glm::mat4(1);
	m_Scale = glm::mat4(1);

	// Generate the needed buffers for OpenGL
	glGenBuffers(1, &m_IndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 6, m_Indices, GL_STATIC_DRAW);

	glGenBuffers(1, &m_VertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_Vertices), m_Vertices, GL_STATIC_DRAW);

 	glGenBuffers(1, &m_UVBuffer);
 	glBindBuffer(GL_ARRAY_BUFFER, m_UVBuffer);
 	glBufferData(GL_ARRAY_BUFFER, sizeof(m_UVs), m_UVs, GL_STATIC_DRAW);

	m_Scroll = 0;
	m_ScrollSpeed = 0.1f;
	m_Pulse = 0;
	m_PulseFactor = 0.5f;

	// load the gradient we want to use for the alpha
	m_AlphaGradientID = SOIL_load_OGL_texture("../Resources/Textures/LightShafts/AlphaGradient2.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_TEXTURE_REPEATS);
}

Liqua::Shaft::~Shaft()
{
	// cleaning up
	glDeleteBuffers(1, &m_VertexBuffer);
	glDeleteBuffers(1, &m_UVBuffer);
	glDeleteBuffers(1, &m_IndexBuffer);
	glDeleteTextures(1, &m_AlphaGradientID);
}

void Liqua::Shaft::Update( float a_DT, glm::vec3& a_CamPos )
{
	// Handle all the parameters needed for the shader to handle
	m_Scroll += m_ScrollSpeed * a_DT;

 	if(m_Pulse >= 1.0f || m_Pulse <= 0.0f)
 	{
 		m_PulseFactor = -m_PulseFactor;
 	}
 
 	m_Pulse += m_PulseFactor * a_DT;

	m_CamPos = a_CamPos;
}

void Liqua::Shaft::Translate( const glm::vec3 a_Position )
{
	// Translation of the shaft
	m_Translation = glm::translate(a_Position);
	m_Position = a_Position;
}

void Liqua::Shaft::Rotate( float a_Angle, glm::vec3 a_Axis )
{
	// Rotation of the shaft based on an axis and an angle
	m_Rotation = glm::rotate(a_Angle, a_Axis);
}

void Liqua::Shaft::Rotate( glm::quat& a_Orientation )
{
	// Rotation of the shaft based on a Quaternion
	m_Rotation = glm::toMat4(a_Orientation);
}

void Liqua::Shaft::PassParameters( glm::mat4 a_Projection, glm::mat4 a_View )
{
	// Binding the shaft shader for passing all the needed parameters.
	m_ShaftShader->Bind();

	m_ModelMatrix = m_Translation * m_Rotation * m_Scale;

	glm::mat4 ModelView = a_View * m_ModelMatrix;

	m_ShaftShader->SetUniformMatrix("ProjectionMatrix", glm::value_ptr(a_Projection));
	m_ShaftShader->SetUniformMatrix("ModelViewMatrix", glm::value_ptr(ModelView));

	m_ShaftShader->SetUniform1f("Scroll", m_Scroll);
	m_ShaftShader->SetUniform1f("Pulse", m_Pulse);

	m_ShaftShader->SetUniform3f("CamPos", glm::value_ptr(m_CamPos));
	m_ShaftShader->SetUniform3f("ShaftPos", glm::value_ptr(m_Position));

	m_ShaftShader->Unbind();
}

void Liqua::Shaft::Render()
{
	// Rendering of the actual shaft.
	m_ShaftShader->Bind();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_AlphaGradientID);

 	glEnableVertexAttribArray(0); // 0 for vertex positions
 	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
 	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, m_UVBuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer); 
 	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

 	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	m_ShaftShader->Unbind();

	glBindTexture(GL_TEXTURE_2D, 0);
}
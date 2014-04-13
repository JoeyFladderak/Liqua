#include "Liqua.h"
#include "Shader.h"
#include "soil/SOIL.h"
#include "Light.h"
#include "WaterSurface.h"

Liqua::WaterSurface::WaterSurface()
{
	// Creation of the water surface with matching UV coordinates and indices.
	m_Vertices[0] = glm::vec3(-1000.0f, 0.0f, -1000.0f); // left bottom 
	m_Vertices[1] = glm::vec3(1000.0f, 0.0f, -1000.0f); // right bottom 
	m_Vertices[2] = glm::vec3(-1000.0f, 0.0f, 1000.0f); // left top 
	m_Vertices[3] = glm::vec3(1000.0f, 0.0f, 1000.0f); // right top 

	m_UVs[0] = glm::vec2(0.0f, 0.0f);
	m_UVs[1] = glm::vec2(10.0f, 0.0f);
	m_UVs[2] = glm::vec2(0.0f, 10.0f);
	m_UVs[3] = glm::vec2(10.0f, 10.0f);

	m_Indices[0] = 0;
	m_Indices[1] = 1;
	m_Indices[2] = 2;

	m_Indices[3] = 1;
	m_Indices[4] = 2;
	m_Indices[5] = 3;

	m_ModelMatrix = glm::mat4(1);

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

	// Create the shader for the water surface,
	m_SurfaceShader = new Shader();
	m_SurfaceShader->CreateShader();
	m_SurfaceShader->AttachVertexShader("../Resources/Shaders/WaterSurface.vert");
	m_SurfaceShader->AttachFragmentShader("../Resources/Shaders/WaterSurface.frag");
	m_SurfaceShader->LinkShader();

	// load the normalmap
	m_NormalMap = SOIL_load_OGL_texture("../Resources/Textures/Surface/waternormal.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_TEXTURE_REPEATS);

	m_Offset = 0;
	m_Height = 0;
}

Liqua::WaterSurface::~WaterSurface()
{
	// cleaning up
	delete m_SurfaceShader;
	glDeleteTextures(1, &m_NormalMap);
	glDeleteBuffers(1, &m_VertexBuffer);
	glDeleteBuffers(1, &m_UVBuffer);
	glDeleteBuffers(1, &m_IndexBuffer);
}

void Liqua::WaterSurface::Update( float a_DT )
{
	// increment the offset used for animating the water.
	m_Offset += 0.005f * a_DT;
}

void Liqua::WaterSurface::PassParameters( glm::mat4 a_Projection, glm::mat4 a_View, glm::vec3 a_CamPos, Light* a_SunLight, glm::vec3& a_WaterColor )
{
	// Bind the shader and pass all needed parameters.
	m_SurfaceShader->Bind();

	glm::mat4 ModelViewProjection = a_Projection * a_View * m_ModelMatrix;

	m_SurfaceShader->SetUniformMatrix("ModelViewProjection", glm::value_ptr(ModelViewProjection));
	m_SurfaceShader->SetUniformMatrix("ModelMatrix", glm::value_ptr(m_ModelMatrix));
	m_SurfaceShader->SetUniform3f("CamPos", glm::value_ptr(a_CamPos));
	m_SurfaceShader->SetUniform1f("UVOffset", m_Offset);

	m_SurfaceShader->SetUniform3f("SunLightColor", glm::value_ptr(a_SunLight->GetColor()));
	m_SurfaceShader->SetUniform3f("SunLightPosition", glm::value_ptr(a_SunLight->GetPosition()));
	m_SurfaceShader->SetUniform3f("SunLightDirection", glm::value_ptr(a_SunLight->GetDirection()));

	m_SurfaceShader->SetUniform1f("SunConstantAttenuation", a_SunLight->GetConstantAttenuation());
	m_SurfaceShader->SetUniform1f("SunLinearAttenuation", a_SunLight->GetLinearAttenuation());
	m_SurfaceShader->SetUniform1f("SunQuadraticAttenuation", a_SunLight->GetQuadraticAttenuation());

	m_SurfaceShader->SetUniform3f("WaterColor", glm::value_ptr(a_WaterColor));

	m_SurfaceShader->Unbind();
}

void Liqua::WaterSurface::Render()
{
	// render the actual geometry.
	m_SurfaceShader->Bind();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_NormalMap);

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

	m_SurfaceShader->Unbind();

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Liqua::WaterSurface::SetHeight( float a_Height )
{
	// Change the waterlevel.
	m_Height = a_Height;
	m_ModelMatrix = glm::translate(glm::vec3(0, a_Height, 0));
}

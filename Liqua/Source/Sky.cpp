#include "Liqua.h"
#include "Light.h"
#include "Mesh.h"
#include "Shader.h"
#include "Sky.h"

Liqua::Sky::Sky()
{
	// load the skydome model (actually a sphere now)
	m_Dome = new Mesh("../Resources/Models/Skydome/Skydome.omd");

	// scale it up so it encapsulates the entire scene
	m_Dome->Scale(glm::vec3(400, 400, 400));
		
	// Load the shader for the skydome
	m_SkyShader = new Shader();
	m_SkyShader->CreateShader();
	m_SkyShader->AttachVertexShader("../Resources/Shaders/Sky.vert");
	m_SkyShader->AttachFragmentShader("../Resources/Shaders/Sky.frag");
	m_SkyShader->LinkShader();

	m_Dome->SetShader(m_SkyShader);

	// load the gradient texture used for the skydome
	m_SkyGradient = SOIL_load_OGL_texture("../Resources/Textures/Sky/skygradient_blue.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_TEXTURE_REPEATS);
}

Liqua::Sky::~Sky()
{
	// clean up
	glDeleteTextures(1, &m_SkyGradient);
	delete m_SkyShader;
	delete m_Dome;
}

void Liqua::Sky::Update( float a_DT )
{

}

void Liqua::Sky::PassParameters( glm::mat4 a_ProjectionMatrix, glm::mat4 a_ViewMatrix, glm::vec3 a_CamPos, Light* a_SunLight, glm::vec3& a_WaterColor )
{
	// bind the shader and pass all needed parameters.
	m_SkyShader->Bind();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_SkyGradient);

	glm::mat4 ModelViewProjection = a_ProjectionMatrix * a_ViewMatrix * m_Dome->GetModelMatrix();
	m_SkyShader->SetUniformMatrix("ModelViewProjection", glm::value_ptr(ModelViewProjection));

	m_SkyShader->SetUniformMatrix("ModelMatrix", glm::value_ptr(m_Dome->GetModelMatrix()));

	m_SkyShader->SetUniform3f("WaterColor", glm::value_ptr(a_WaterColor));

	m_SkyShader->Unbind();
}

void Liqua::Sky::Render()
{
	// actually render the model
	m_Dome->Render();
}


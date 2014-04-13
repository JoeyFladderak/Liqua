#include "Liqua.h"
#include "Shader.h"
#include "Light.h"
#include "Caustics.h"

Liqua::Caustics::Caustics()
{
	// Creation of the shader
	m_CausticsShader = new Shader();
	m_CausticsShader->CreateShader();
	m_CausticsShader->AttachVertexShader("../Resources/Shaders/Caustics.vert");
	m_CausticsShader->AttachFragmentShader("../Resources/Shaders/Caustics.frag");
	m_CausticsShader->LinkShader();

	// Index for the caustic textures
	m_CurrentCaustic = 0;

	// Creation of the light that handles all the lighting effects under the water surface
	m_ProjectingLight = new Light();
	m_ProjectingLight->SetPosition(glm::vec3(0.1f, 750.0f, 0.1f));
	m_ProjectingLight->SetQuadraticAttenuation(0.0000025f);
	m_ProjectingLight->SetFoV(4.0f);

	// Creation of the projectionmatrix as seen through the light and the texture bias matrix, both used for projective textures
	m_LightProjectionMatrix = glm::perspective(m_ProjectingLight->GetFoV(), (float)(SCRWIDTH/SCRHEIGHT), m_ProjectingLight->GetNearPlane(), m_ProjectingLight->GetFarPlane());
	m_TextureBiasMatrix = glm::scaleBias(0.5f, 0.5f);

	m_FrameTime = 0;

	m_CausticsTextures.clear();
}

Liqua::Caustics::~Caustics()
{
	// cleaning up
	delete m_CausticsShader;
	delete m_ProjectingLight;
	for(unsigned int i = 0; i < m_CausticsTextures.size(); i++)
	{
		glDeleteTextures(1, &m_CausticsTextures[i]);
	}
	m_CausticsTextures.clear();
}

void Liqua::Caustics::Update( float a_DT )
{
	// Increment the frame time with the deltatime
	m_FrameTime += a_DT;

	// if we get above 0.05
	if(m_FrameTime >= 0.05f)
	{
		// we increment the index
		m_CurrentCaustic++;

		// if the index is bigger than the total amount of texture we have
		if(m_CurrentCaustic >= m_CausticsTextures.size() - 1)
		{
			// set the index back to zero
			m_CurrentCaustic = 0;
		}
		
		// and reset the time passed
		m_FrameTime = 0;
	}
}

void Liqua::Caustics::PassParameters(glm::mat4 a_ModelMatrix, glm::mat4 a_ViewMatrix, glm::mat4 a_ProjectionMatrix, glm::vec3 a_CamPos, Light* a_Light, glm::vec3 a_Ambient, glm::vec3& a_WaterColor, float a_WaterLevel /* = 0 */)
{
	// Bind the shader for passing all the needed parameters
	m_CausticsShader->Bind();

	// Pass the caustic texture with the current textureindex
	m_CausticsShader->SetUniform1i("CausticMap", 1);
	glActiveTexture(GL_TEXTURE1); CheckGL();
	glBindTexture(GL_TEXTURE_2D, m_CausticsTextures[m_CurrentCaustic]); CheckGL();

	// create the modelviewprojection matrix and pass it to the shader
	glm::mat4 ModelViewProjection = a_ProjectionMatrix * a_ViewMatrix * a_ModelMatrix;
	m_CausticsShader->SetUniformMatrix("ModelViewProjection", glm::value_ptr(ModelViewProjection));

	m_CausticsShader->SetUniform3f("EyePosition", glm::value_ptr(a_CamPos));

	m_CausticsShader->SetUniformMatrix("ModelMatrix", glm::value_ptr(a_ModelMatrix));

	// creation of the viewmatrix, as seen from the light and create the texturematrix before passing it for projective textures.
	m_LightViewMatrix = glm::lookAt(m_ProjectingLight->GetPosition(), glm::vec3(0), glm::vec3(0, -1, 0));
	m_TextureMatrix = m_TextureBiasMatrix * m_LightProjectionMatrix * m_LightViewMatrix;
	m_CausticsShader->SetUniformMatrix("TextureMatrix", glm::value_ptr(m_TextureMatrix * a_ModelMatrix));

	m_CausticsShader->SetUniform3f("ProjectedLightPosition", glm::value_ptr(m_ProjectingLight->GetPosition()));
	m_CausticsShader->SetUniform3f("ProjectedLightDirection", glm::value_ptr(m_ProjectingLight->GetDirection()));
	m_CausticsShader->SetUniform3f("ProjectedLightColor", glm::value_ptr(m_ProjectingLight->GetColor()));
	m_CausticsShader->SetUniform1f("ProjectedLightIntensity", m_ProjectingLight->GetIntensity());

	m_CausticsShader->SetUniform1f("ProjectedConstantAttenuation", m_ProjectingLight->GetConstantAttenuation());
	m_CausticsShader->SetUniform1f("ProjectedLinearAttenuation", m_ProjectingLight->GetLinearAttenuation());
	m_CausticsShader->SetUniform1f("ProjectedQuadraticAttenuation", m_ProjectingLight->GetQuadraticAttenuation());

	m_CausticsShader->SetUniform1f("WaterLevel", a_WaterLevel);
	m_CausticsShader->SetUniform3f("Ambient", glm::value_ptr(a_Ambient));
	m_CausticsShader->SetUniform3f("WaterColor", glm::value_ptr(a_WaterColor));

	m_CausticsShader->SetUniform3f("SunLightPosition", glm::value_ptr(a_Light->GetPosition()));
	m_CausticsShader->SetUniform3f("SunLightColor", glm::value_ptr(a_Light->GetColor()));

	m_CausticsShader->SetUniform1f("SunConstantAttenuation", a_Light->GetConstantAttenuation());
	m_CausticsShader->SetUniform1f("SunLinearAttenuation", a_Light->GetLinearAttenuation());
	m_CausticsShader->SetUniform1f("SunQuadraticAttenuation", a_Light->GetQuadraticAttenuation());

	m_CausticsShader->Unbind();
}

void Liqua::Caustics::AddCausticTexture( GLuint a_TextureID )
{
	m_CausticsTextures.push_back(a_TextureID);
}
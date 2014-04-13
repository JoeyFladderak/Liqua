#include "Liqua.h"
#include "Shader.h"
#include "Mesh.h"
#include "Light.h"

Liqua::Light::Light()
{
	// Initial values of a light
	m_Position = glm::vec3(0.1f, 0.1f, 0.1f);
	m_Direction = glm::vec3(0.1f, 1.0f, 0.1f);

	m_MeshMatrix = glm::translate(m_MeshMatrix, m_Position);
	m_MeshMatrix = glm::scale(m_MeshMatrix, glm::vec3(1, 1, 1));

	m_Color = glm::vec3(1.0f, 1.0f, 1.0f);
	m_Intensity = 5.0f;

	m_NearPlane = 0.1f;
	m_FarPlane = 5000.0f;
	m_FieldOfView = 5.0f;

	m_ConstantAttenuation = 1.0f;
	m_LinearAttenuation = 0.0f;
	m_QuadraticAttenuation = 0.0f;
	m_InnerCosAngle = 0.25f;
	m_OuterCosAngle = 0.15f;

	m_ClearShader = new Shader();
	m_ClearShader->CreateShader();
	m_ClearShader->AttachVertexShader("../Resources/Shaders/ClearColor.vert");
	m_ClearShader->AttachFragmentShader("../Resources/Shaders/ClearColor.frag");
	m_ClearShader->LinkShader();

// 	m_LightMesh = new Mesh("../Resources/Meshs/Light/Light.omd");
// 	m_LightMesh->SetShader(m_ClearShader);
}

Liqua::Light::~Light()
{
	if(m_LightMesh)
	{
		delete m_LightMesh;
	}

	delete m_ClearShader;
}

void Liqua::Light::Render(glm::mat4 WorldViewProjection)
{
	// Should we want to render the light, do it with shader that simply draws it in a certain color
	m_ClearShader->Bind();
	m_ClearShader->SetUniform3f("Col", glm::value_ptr(m_Color));
	m_ClearShader->SetUniformMatrix("ModelViewProjection", glm::value_ptr(WorldViewProjection));
	m_LightMesh->Render();
	m_ClearShader->Unbind();
}

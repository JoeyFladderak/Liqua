#include "Liqua.h"
#include "Shader.h"
#include "soil/SOIL.h"
#include "ParticleSystem.h"

Liqua::ParticleSystem::ParticleSystem(unsigned int a_ParticleAmount)
{
	m_ParticleBuffer.resize(a_ParticleAmount);
	m_VertexBuffer.resize(a_ParticleAmount);
	m_UVBuffer.resize(a_ParticleAmount);
	m_IndexBuffer.resize(a_ParticleAmount);

	m_ModelMatrix = glm::mat4(1);
	m_ViewMatrix = glm::mat4(1);

	m_Vertices[0] = glm::vec3(-0.5f, -0.5f, 0.0f); // left bottom 
	m_Vertices[1] = glm::vec3(0.5f, -0.5f, 0.0f); // right bottom 
	m_Vertices[2] = glm::vec3(-0.5f, 0.5f, 0.0f); // left top 
	m_Vertices[3] = glm::vec3(0.5f, 0.5f, 0.0f); // right top 

	m_UVs[0] = glm::vec2(0.0f, 0.0f);
	m_UVs[1] = glm::vec2(1.0f, 0.0f);
	m_UVs[2] = glm::vec2(0.0f, 1.0f);
	m_UVs[3] = glm::vec2(1.0f, 1.0f);

	m_Indices[0] = 0;
	m_Indices[1] = 1;
	m_Indices[2] = 2;
	m_Indices[3] = 1;
	m_Indices[4] = 2;
	m_Indices[5] = 3;

	for(unsigned int i = 0; i < m_ParticleBuffer.size(); i++)
	{
		m_ParticleBuffer[i].m_Age = 0.0f;
		m_ParticleBuffer[i].m_Lifetime = MathHelper::rFloatRange(10, 20);
		m_ParticleBuffer[i].m_Rotation = glm::vec3(0);
		m_ParticleBuffer[i].m_RotationSpeed = MathHelper::rFloatRange(500.0f, 750.0f);
		m_ParticleBuffer[i].m_StartRotation = glm::vec3(MathHelper::rFloatRange(0, 360));
		m_ParticleBuffer[i].m_EndRotation = glm::vec3(MathHelper::rFloatRange(0, 360));
		m_ParticleBuffer[i].m_Size = MathHelper::rFloatRange(0.15f, 0.25f);
		m_ParticleBuffer[i].m_Color = glm::vec3(0, 0, 0);
		m_ParticleBuffer[i].m_Position = glm::vec3(MathHelper::rFloatRange(150.0f, 400.0f), MathHelper::rFloatRange(-1.0f, -50.0f), MathHelper::rFloatRange(-200.0f, 200.0f));
		m_ParticleBuffer[i].m_Velocity = glm::vec3(MathHelper::rFloatRange(-0.1f, 0.1f), MathHelper::rFloatRange(-0.1f, 0.1f), MathHelper::rFloatRange(-0.1f, 0.1f));
		m_ParticleBuffer[i].m_Alpha = 0;
	}

	m_ParticleShader = new Shader();
	m_ParticleShader->CreateShader();
	m_ParticleShader->AttachVertexShader("../Resources/Shaders/Particle.vert");
	m_ParticleShader->AttachFragmentShader("../Resources/Shaders/Particle.frag");
	m_ParticleShader->LinkShader();

	m_Tex = 0;

	glGenBuffers(1, &m_IndexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_IndexBuffer.size(), &m_IndexBuffer[0], GL_DYNAMIC_DRAW);

	glGenBuffers(1, &m_VertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, m_VertexBuffer.size() * sizeof(glm::vec3), &m_VertexBuffer[0], GL_DYNAMIC_DRAW);

	glGenBuffers(1, &m_UVBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, m_UVBufferID);
	glBufferData(GL_ARRAY_BUFFER, m_UVBuffer.size() * sizeof(glm::vec2), &m_UVBuffer[0], GL_DYNAMIC_DRAW);
}

Liqua::ParticleSystem::~ParticleSystem()
{
	delete m_ParticleShader;
	glDeleteTextures(1, &m_Tex);
	glDeleteBuffers(1, &m_VertexBufferID);
	glDeleteBuffers(1, &m_UVBufferID);
	glDeleteBuffers(1, &m_IndexBufferID);
}

void Liqua::ParticleSystem::Update( float a_DT )
{
	for(unsigned int i = 0; i < m_ParticleBuffer.size(); i++)
	{
		Particle& particle = m_ParticleBuffer[i];

		if(particle.m_Position.y >= -particle.m_Size)
			particle.m_Velocity.y = -particle.m_Velocity.y;

		particle.m_Position = particle.m_Position + particle.m_Velocity * a_DT;

		particle.m_Age += 0.002f * a_DT;
		if(particle.m_Age > particle.m_Lifetime)
		{
		 	particle.m_Age = 0.0f;
		 	particle.m_Lifetime = MathHelper::rFloatRange(10.0f, 20.0f);
			particle.m_Velocity = glm::vec3(MathHelper::rFloatRange(-0.075f, 0.075f), MathHelper::rFloatRange(-0.075f, 0.075f), MathHelper::rFloatRange(-0.075f, 0.075f));

			m_ParticleBuffer[i].m_RotationSpeed = MathHelper::rFloatRange(500.0f, 750.0f);
			particle.m_StartRotation = particle.m_EndRotation;
			particle.m_EndRotation = glm::vec3(MathHelper::rFloatRange(0.0f, 360.0f));
		}

		float liferatio = MathHelper::Clamp((particle.m_Age / particle.m_Lifetime), 0, 1) * particle.m_RotationSpeed;

		particle.m_Rotation.x = MathHelper::Lerp(particle.m_StartRotation.x, particle.m_EndRotation.x, liferatio);
		particle.m_Rotation.y = MathHelper::Lerp(particle.m_StartRotation.y, particle.m_EndRotation.y, liferatio);
		particle.m_Rotation.z = MathHelper::Lerp(particle.m_StartRotation.z, particle.m_EndRotation.z, liferatio);
	}

	BuildBuffer();
}

void Liqua::ParticleSystem::BuildBuffer()
{
	m_VertexBuffer.resize(m_ParticleBuffer.size() * 4, glm::vec3());
	m_UVBuffer.resize(m_ParticleBuffer.size() * 4, glm::vec2());
	m_IndexBuffer.resize(m_ParticleBuffer.size() * 6, 0);

	glm::quat camrot = glm::toQuat(m_ViewMatrix);

	for(unsigned int i = 0; i < m_ParticleBuffer.size(); i++)
	{
		Particle& particle = m_ParticleBuffer[i];

		glm::quat rotx = glm::angleAxis(particle.m_Rotation.x, glm::vec3(1, 0, 0));
		glm::quat roty = glm::angleAxis(particle.m_Rotation.x, glm::vec3(0, 1, 0));
		glm::quat rotz = glm::angleAxis(particle.m_Rotation.x, glm::vec3(0, 0, 1));
		glm::quat rot = rotx * roty * rotz;

		unsigned int vertindex = i * 4;
		glm::vec3& v0 = m_VertexBuffer[vertindex + 0];
		glm::vec3& v1 = m_VertexBuffer[vertindex + 1];
		glm::vec3& v2 = m_VertexBuffer[vertindex + 2];
		glm::vec3& v3 = m_VertexBuffer[vertindex + 3];

		glm::vec2& uv0 = m_UVBuffer[vertindex + 0];
		glm::vec2& uv1 = m_UVBuffer[vertindex + 1];
		glm::vec2& uv2 = m_UVBuffer[vertindex + 2];
		glm::vec2& uv3 = m_UVBuffer[vertindex + 3];

		v0 = particle.m_Position + (rot * m_Vertices[0] * particle.m_Size);// * camrot;
		uv0 = m_UVs[0];

		v1 = particle.m_Position + (rot * m_Vertices[1] * particle.m_Size);// * camrot;
		uv1 = m_UVs[1];

		v2 = particle.m_Position + (rot * m_Vertices[2] * particle.m_Size);// * camrot;
		uv2 = m_UVs[2];

		v3 = particle.m_Position + (rot * m_Vertices[3] * particle.m_Size);// * camrot;
		uv3 = m_UVs[3];

		unsigned int idx = i * 6;
		unsigned int& index0 = m_IndexBuffer[idx + 0];
		unsigned int& index1 = m_IndexBuffer[idx + 1];
		unsigned int& index2 = m_IndexBuffer[idx + 2];
		unsigned int& index3 = m_IndexBuffer[idx + 3];
		unsigned int& index4 = m_IndexBuffer[idx + 4];
		unsigned int& index5 = m_IndexBuffer[idx + 5];

		index0 = i * 4;
		index1 = (i * 4) + 1;
		index2 = (i * 4) + 2;
		index3 = (i * 4) + 1;
		index4 = (i * 4) + 2;
		index5 = (i * 4) + 3;
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_IndexBuffer.size(), &m_IndexBuffer[0], GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, m_VertexBuffer.size() * sizeof(glm::vec3), &m_VertexBuffer[0], GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m_UVBufferID);
	glBufferData(GL_ARRAY_BUFFER, m_UVBuffer.size() * sizeof(glm::vec2), &m_UVBuffer[0], GL_DYNAMIC_DRAW);
}

void Liqua::ParticleSystem::Render(glm::mat4 a_Projection, glm::mat4 a_View)
{
	glDepthMask(GL_FALSE);
	m_ParticleShader->Bind();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_Tex);

	m_ViewMatrix = a_View;

	glm::mat4 ModelView = a_Projection * a_View * m_ModelMatrix;

	m_ParticleShader->SetUniformMatrix("ProjectionMatrix", glm::value_ptr(ModelView));
	m_ParticleShader->SetUniformMatrix("ModelViewMatrix", glm::value_ptr(ModelView));

	glEnableVertexAttribArray(0); // 0 for vertex positions
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, m_UVBufferID);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID); 
	glDrawElements(GL_TRIANGLES, m_IndexBuffer.size(), GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	m_ParticleShader->Unbind();

	glBindTexture(GL_TEXTURE_2D, 0);
	glDepthMask(GL_TRUE);
}
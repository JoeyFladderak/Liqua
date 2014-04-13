#ifndef _PARTICLE_SYSTEM_H_
#define _PARTICLE_SYSYEM_H_

namespace Liqua
{
	struct Particle
	{
		glm::vec3 m_Position;
		glm::vec3 m_Velocity;
		glm::vec3 m_Color;
		float m_Alpha;
		glm::vec3 m_Rotation;
		float m_RotationSpeed;
		glm::vec3 m_StartRotation;
		glm::vec3 m_EndRotation;
		float m_Size;
		float m_Age;
		float m_Lifetime;
	};

	class Shader;
	class LIQUAEXPORT ParticleSystem
	{
	public:

		ParticleSystem(unsigned int a_ParticleAmount);
		~ParticleSystem();

		void Update(float a_DT);
		void Render(glm::mat4 a_Projection, glm::mat4 a_View);

		void SetTexture(unsigned int a_TextureID) {m_Tex = a_TextureID;}

	protected:

		void BuildBuffer();

		GLuint m_UVBufferID;
		GLuint m_VertexBufferID;
		GLuint m_IndexBufferID;

		glm::vec3 m_Vertices[4];
		glm::vec2 m_UVs[4];
		unsigned int m_Indices[6];

		std::vector<glm::vec3> m_VertexBuffer;
		std::vector<glm::vec2> m_UVBuffer;
		std::vector<unsigned int> m_IndexBuffer;

		std::vector<Particle> m_ParticleBuffer;

		glm::mat4 m_ModelMatrix;
		glm::mat4 m_ViewMatrix;

		Shader* m_ParticleShader;
		GLuint m_Tex;
	};
}
#endif
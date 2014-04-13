#ifndef _SHAFT_H_
#define _SHAFT_H_

namespace Liqua
{
	class Texture;
	class Mesh;
	class Shader;
	class LIQUAEXPORT Shaft
	{
	public:

		Shaft(float a_Width, float a_Height);
		~Shaft();

		void Update(float a_DT, glm::vec3& a_CamPos);

		void PassParameters(glm::mat4 a_Projection, glm::mat4 a_View);

		void Render();

		void Translate(const glm::vec3 a_Position);
		void Rotate(float a_Angle, glm::vec3 a_Axis);
		void Rotate(glm::quat& a_Orientation);
		void SetShader(Shader* a_Shader) {m_ShaftShader = a_Shader;}

		void SetStartPulse(float a_Pulse) {m_Pulse = a_Pulse;}
		void SetPulseFactor(float a_PulseFactor) {m_PulseFactor = a_PulseFactor;}

		void SetScrollSpeed(float a_Speed) {m_ScrollSpeed = a_Speed;}

	protected:

		Shader* m_ShaftShader;

		GLuint m_UVBuffer;
		GLuint m_VertexBuffer;
		GLuint m_IndexBuffer;

		glm::vec3 m_Vertices[4];
		glm::vec3 m_drawvert[4];
		glm::vec2 m_UVs[4];
		unsigned int m_Indices[6];

		float m_Scroll;
		float m_ScrollSpeed;

		float m_Pulse;
		float m_PulseFactor;

		float m_Distance;

		glm::quat m_CamRot;
		glm::vec3 m_Position;
		glm::vec3 m_CamPos;

		unsigned int m_AlphaGradientID;

		glm::mat4 m_ModelMatrix;
		glm::mat4 m_Translation;
		glm::mat4 m_Rotation;
		glm::mat4 m_Scale;
	};
}
#endif
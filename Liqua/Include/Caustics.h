#ifndef _CAUSTICS_H_
#define _CAUSTICS_H_

namespace Liqua
{
	class Light;
	class Shader;
	class LIQUAEXPORT Caustics
	{
	public:

		Caustics();
		~Caustics();

		void Update(float a_DT);

		void PassParameters(glm::mat4 a_ModelMatrix, glm::mat4 a_ViewMatrix, glm::mat4 a_ProjectionMatrix, glm::vec3 a_CamPos, Light* a_Light, glm::vec3 a_Ambient, glm::vec3& a_WaterColor, float a_WaterLevel = 0);
		void AddCausticTexture(GLuint a_TextureID);

		Shader* GetShader() {return m_CausticsShader;}
		void SetShader(Shader* a_Shader) {m_CausticsShader = a_Shader;}

		float GetWaterLevel() {return m_WaterLevel;}
		void SetWaterLevel(float a_WaterLevel) {m_WaterLevel = a_WaterLevel;}

	protected:

		Shader* m_CausticsShader;

		float m_WaterLevel;

		Light* m_ProjectingLight;

		std::vector<GLuint> m_CausticsTextures;
		unsigned int m_CurrentCaustic;

		float m_FrameTime;

		glm::mat4 m_LightViewMatrix;
		glm::mat4 m_LightProjectionMatrix;
		glm::mat4 m_TextureBiasMatrix;
		glm::mat4 m_TextureMatrix;
	};
}
#endif
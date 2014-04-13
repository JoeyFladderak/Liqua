#ifndef _SKY_H_
#define _SKY_H_

namespace Liqua
{
	class Mesh;
	class Shader;
	class LIQUAEXPORT Sky
	{
	public:

		Sky();
		~Sky();

		void Update(float a_DT);

		void PassParameters(glm::mat4 a_ProjectionMatrix, glm::mat4 a_ViewMatrix, glm::vec3 a_CamPos, Light* a_SunLight, glm::vec3& a_WaterColor);

		void Render();

	protected:

		Mesh* m_Dome;
		Shader* m_SkyShader;

		unsigned int m_SkyGradient;
	};
}
#endif
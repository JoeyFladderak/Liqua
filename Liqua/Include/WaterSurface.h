#ifndef _WATER_SURFACE_H_
#define _WATER_SURFACE_H_

namespace Liqua
{
	class Light;
	class Shader;
	class LIQUAEXPORT WaterSurface
	{
	public:

		WaterSurface();
		~WaterSurface();

		void Update(float a_DT);

		void PassParameters(glm::mat4 a_Projection, glm::mat4 a_View, glm::vec3 a_CamPos, Light* a_SunLight, glm::vec3& a_WaterColor);
		
		void SetHeight(float a_Height);
		float GetHeight() {return m_Height;}

		void Render();

	protected:

		float m_Height;

		Shader* m_SurfaceShader;

		GLuint m_UVBuffer;
		GLuint m_VertexBuffer;
		GLuint m_IndexBuffer;

		glm::vec3 m_Vertices[4];
		glm::vec2 m_UVs[4];
		unsigned int m_Indices[6];

		unsigned int m_NormalMap;
		float m_Offset;

		glm::mat4 m_ModelMatrix;
	};
}
#endif
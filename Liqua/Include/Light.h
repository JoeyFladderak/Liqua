#ifndef _LIGHT_H_
#define _LIGHT_H_

namespace Liqua
{
	class Mesh;
	class Shader;
	class LIQUAEXPORT Light
	{
	public:

		Light();
		~Light();

		void Render(glm::mat4 WorldViewProjection);

		const glm::vec3& GetPosition() const {return m_Position;}
		const glm::vec3& GetDirection() const {return m_Direction;}
		
		const glm::vec3& GetColor() const {return m_Color;}
		const float GetIntensity() const {return m_Intensity;}

		const float GetNearPlane() const {return m_NearPlane;}
		const float GetFarPlane() const {return m_FarPlane;}
		const float GetFoV() const {return m_FieldOfView;}

		const float GetConstantAttenuation() const {return m_ConstantAttenuation;}
		const float GetLinearAttenuation() const {return m_LinearAttenuation;}
		const float GetQuadraticAttenuation() const {return m_QuadraticAttenuation;}

		void SetPosition(const glm::vec3& a_Position) {m_Position = a_Position;}
		void SetDirection(const glm::vec3& a_Direction) {m_Direction = a_Direction;}

		void SetColor(const glm::vec3& a_Color) {m_Color = a_Color;}
		void SetIntensity(const float a_Intensity) {m_Intensity = a_Intensity;}

		void SetNearPlane(const float a_NearPlane) {m_NearPlane = a_NearPlane;}
		void SetFarPlane(const float a_FarPlane) {m_FarPlane = a_FarPlane;}
		void SetFoV(const float a_FoV) {m_FieldOfView = a_FoV;}

		void SetConstantAttenuation(const float a_ConstantAttenuation) {m_ConstantAttenuation = a_ConstantAttenuation;}
		void SetLinearAttenuation(const float a_LinearAttenuation) {m_LinearAttenuation = a_LinearAttenuation;}
		void SetQuadraticAttenuation(const float a_QuadraticAttenuation) {m_QuadraticAttenuation = a_QuadraticAttenuation;}

	protected:

		Mesh* m_LightMesh;
		Shader* m_ClearShader;
		glm::mat4 m_MeshMatrix;

		glm::vec3 m_Position;
		glm::vec3 m_Direction;

		glm::vec3 m_Color;
		float m_Intensity;

		float m_NearPlane;
		float m_FarPlane;
		float m_FieldOfView;

		float m_ConstantAttenuation;
		float m_LinearAttenuation;
		float m_QuadraticAttenuation;

		float m_InnerCosAngle;
		float m_OuterCosAngle;
	};
}
#endif
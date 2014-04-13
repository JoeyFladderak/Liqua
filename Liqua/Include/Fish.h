#ifndef _FISH_H_
#define _FISH_H_

namespace Liqua
{
	class Mesh;
	class Shader;
	class LIQUAEXPORT Fish
	{
	public:

		enum FishState
		{
			State_Schooling,
			State_Shoaling,
			State_Hungry,
			State_Alerted
		};

		Fish();
		~Fish();

		void Update(float a_DT);

		void SetShader(Shader* a_Shader);

		const glm::vec3& GetPosition() const {return m_Position;}
		const glm::vec3& GetVelocity() const {return m_Velocity;}
		float GetTurningSpeed() {return m_TurningSpeed;}
		float GetspeedModifier() {return m_SpeedModifier;}
		FishState& GetCurrentState() {return m_State;}
		FishState& GetPreviousState() {return m_PreviousState;}

		void SetPosition(glm::vec3& a_Position) {m_Position = a_Position;}
		void SetVelocity(glm::vec3& a_Velocity) {m_Velocity = a_Velocity;}
		void SetTurningSpeed(float a_TurningSpeed) {m_TurningSpeed = a_TurningSpeed;}
		void SetSpeedModifier(float a_SpeedModifier) {m_SpeedModifier = a_SpeedModifier;}
		void SetState(FishState a_State) {m_State = a_State;}
		void SetPreviousState(FishState a_State) {m_PreviousState = a_State;}

		Mesh* GetMesh() {return m_Fish;}

	protected:
		
		glm::vec3 Integrate(glm::vec3& a_Position, glm::vec3& a_Velocity, float a_DT);
		glm::quat CalculateOrientation(glm::vec3& a_Velocity);

		glm::vec3 m_Position;
		glm::vec3 m_Velocity;
		glm::quat m_Orientation;
		glm::quat m_PreviousOrientation;
		float m_TurningSpeed;

		float m_SpeedModifier;

		FishState m_State;
		FishState m_PreviousState;

		Mesh* m_Fish;
		Shader* m_Shader;
	};
}
#endif
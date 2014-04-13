 #ifndef _SCHOOL_H_
 #define _SCHOOL_H_
 
 namespace Liqua
 {
	class Fish;
 	class LIQUAEXPORT School
 	{
 	public:
 
 		School();
 		School(float a_Amount);
 		~School();
 
 		void Update(float a_DT);

		void SetTarget(glm::vec3& a_Target) {m_CurrentTarget = a_Target;}

		std::vector<Fish*> GetFishArray() {return m_School;}

		float GetMaxSpeed() {return m_MaxSpeed;}
		void SetMaxSpeed(float a_Speed) {m_MaxSpeed = a_Speed;}

		void Scatter(Fish* a_Fish, float a_ScatterSpeed);
 
 	protected:
 
		glm::vec3 TargetAttraction(Fish* a_Fish, float a_DT);
 		glm::vec3 Seperation(Fish* a_Fish, float a_DT);
 		glm::vec3 Cohesion(Fish* a_Fish, float a_DT);
 		glm::vec3 Alignment(Fish* a_Fish, float a_DT);
		glm::vec3 DampenVelocity(Fish* a_Fish, glm::vec3& a_Velocity, float a_DT);
 
 		std::vector<Fish*> m_School;
		std::vector<glm::vec3> m_Targets;
		glm::vec3 m_CurrentTarget;
		glm::vec3 m_ShoalPlace;

		glm::vec3 m_SchoolCenter;

		float m_MaxSpeed;
		float m_DistanceTreshold;
		float m_TargetTreshold;

		unsigned int m_TargetIndex;

		float m_Counter;
		float m_CountTarget;

		float m_ShoalCounter;
		float m_ShoalCountTarget;

		bool m_AssingHungerTarget;
		glm::vec3 m_HungerTarget;
 	};
 }
 #endif
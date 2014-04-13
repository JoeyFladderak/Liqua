#include "Liqua.h"
#include "Fish.h"
#include "School.h"

#define ALIGNMENT_DIVIDER 100.0f
#define TARGET_DIVIDER 100.0f
#define COHESION_DIVIDER 8.0f

Liqua::School::School()
{

}

Liqua::School::School( float a_Amount )
{
	// Creating the passed amount of fish and giving it a random position.
	for(int i = 0; i < a_Amount; i++)
	{
		Fish* newfish = new Fish();
		glm::vec3 pos = newfish->GetPosition();
		pos += glm::vec3(MathHelper::rFloatRange(-25, 25), MathHelper::rFloatRange(-10, 0), MathHelper::rFloatRange(-25, 25));
		newfish->SetPosition(pos);
		m_School.push_back(newfish);
	}

	m_Targets.clear();

	// Creation of 30 randomized points that act as a point to swim to for the fish.
	for(int i = 0; i < 30; i++)
	{
		glm::vec3 target = glm::vec3(MathHelper::rFloatRange(200, 400), MathHelper::rFloatRange(-30, -10), MathHelper::rFloatRange(-200, 200));
		m_Targets.push_back(target);
	}

	// Set the current target to a random value.
	m_TargetIndex = MathHelper::rIntRange(0, m_Targets.size());
	m_CurrentTarget = m_Targets[m_TargetIndex];

	// Initializing some initial values.
	m_MaxSpeed = 7.50f;
	m_DistanceTreshold = 7.5f;
	m_TargetTreshold = 40.0f;

	m_Counter = 0.0f;
	m_ShoalCounter = 0.0f;
	m_CountTarget = MathHelper::rFloatRange(30, 60);
	m_ShoalCountTarget = MathHelper::rFloatRange(60, 90);
	m_AssingHungerTarget = false;
}

Liqua::School::~School()
{
	// cleaning up
	for(unsigned int i = 0; i < m_School.size(); i++)
	{
		delete m_School[i];
	}

	m_School.clear();
}

void Liqua::School::Update(float a_DT)
{
	// if the distance between the current target the school is swimming towards and the center of the school
	// is smaller than the target treshold
	if(glm::distance(m_CurrentTarget, m_SchoolCenter) <= m_TargetTreshold)
	{
		// assign a new target
		m_TargetIndex = MathHelper::rIntRange(0, m_Targets.size());
		m_ShoalPlace = m_CurrentTarget;
		m_CurrentTarget = m_Targets[m_TargetIndex];

		// Decide wether we want to shoal or not
		int rnd = MathHelper::rIntRange(0, 100);
		if(rnd > 80)
		{
			// If yes, change the state of the fish to shoaling and store the previous state.
			for(unsigned int i = 0; i < m_School.size(); i++)
			{
				m_School[i]->SetPreviousState(m_School[i]->GetCurrentState());
				m_School[i]->SetState(Fish::State_Shoaling);
			}
		}
	}

	for(unsigned int i = 0; i < m_School.size(); i++)
	{
		// When pressing F1, change the state to alerted.
		if(GetAsyncKeyState(VK_F1))
		{
			m_School[i]->SetPreviousState(m_School[i]->GetCurrentState());
			m_School[i]->SetState(Fish::FishState::State_Alerted);
		}

		glm::vec3 Target;
		glm::vec3 SchoolSeperation;
		glm::vec3 SchoolAllignment;
		glm::vec3 SchoolCohesion;
		glm::vec3 velocity;

		switch(m_School[i]->GetCurrentState())
		{
		case Fish::FishState::State_Schooling:
			{
				// Set the turning speed to 1, so the fish don't turn to fast.
				m_School[i]->SetTurningSpeed(1.0f);

				// calculations of the velocity based on Graig Reynolds mathmatical model
				Target = TargetAttraction(m_School[i], a_DT);
				SchoolSeperation = Seperation(m_School[i], a_DT);
				SchoolAllignment = Alignment(m_School[i], a_DT);
				SchoolCohesion = Cohesion(m_School[i], a_DT);

				velocity = m_School[i]->GetVelocity();
				velocity = velocity + SchoolAllignment + SchoolSeperation + SchoolCohesion + Target;

				velocity = DampenVelocity(m_School[i], velocity, a_DT);

				m_School[i]->SetVelocity(velocity);

				// increment the counter
				m_Counter += 0.1f * a_DT;
				
				// and if the counter reaches its limit
				if(m_Counter >= m_CountTarget)
				{
					// reset the counter and randomly set 1 fish to a hungry state
					m_Counter = 0;
					int RandomFish = MathHelper::rIntRange(0, m_School.size() - 1);
					m_School[i]->SetPreviousState(m_School[i]->GetCurrentState());
					m_School[RandomFish]->SetState(Fish::State_Hungry);
				}
			}
			break;
		case Fish::FishState::State_Shoaling:
			{		
				// Simplified version of the Schooling state with slight adjustments.
				m_School[i]->SetTurningSpeed(1.0f);

				Target = (m_ShoalPlace - m_School[i]->GetPosition()) / (10.0f);
				SchoolSeperation = Seperation(m_School[i], a_DT);
				SchoolCohesion = Cohesion(m_School[i], a_DT);

				velocity = m_School[i]->GetVelocity() * m_School[i]->GetspeedModifier();
				velocity = velocity + SchoolSeperation + SchoolCohesion + Target;

				velocity = DampenVelocity(m_School[i], velocity, a_DT);

				m_School[i]->SetVelocity(velocity);

				m_Counter += 0.1f * a_DT;
				m_ShoalCounter += 0.1f * a_DT;

				if(m_Counter >= m_CountTarget)
				{
					m_Counter = 0;
					int RandomFish = MathHelper::rIntRange(0, m_School.size() - 1);
					m_School[RandomFish]->SetPreviousState(m_School[RandomFish]->GetCurrentState());
					m_School[RandomFish]->SetState(Fish::State_Hungry);
				}

				if(m_ShoalCounter >= m_ShoalCountTarget)
				{
					m_ShoalCounter = 0;
					m_ShoalCountTarget = MathHelper::rFloatRange(60, 90);
					for(unsigned int j = 0; j < m_School.size(); j++)
						m_School[j]->SetState(Fish::State_Schooling);

					std::cout << "Schooling" << std::endl;
				}
			}
			break;
		case Fish::FishState::State_Hungry:
			{
				if(!m_AssingHungerTarget)
				{
					// Only once create a random target based on the fish's current position
					float x = MathHelper::rFloatRange(-50, 50);
					float y = MathHelper::rFloatRange(-25, 0);
					float z = MathHelper::rFloatRange(-50, 50);
					m_HungerTarget = m_School[i]->GetPosition() + glm::vec3(x, y, z);
					velocity = m_School[i]->GetVelocity() * m_School[i]->GetspeedModifier();
					m_AssingHungerTarget = true;
				}

				// and let the fish go there
				Target = (m_HungerTarget - m_School[i]->GetPosition());// / 10.0f;
				velocity += Target;
				velocity = DampenVelocity(m_School[i], velocity, a_DT);
				m_School[i]->SetVelocity(velocity);

				// if the fish gets within its range
				if(glm::distance(m_HungerTarget, m_School[i]->GetPosition()) <= 10)
				{
					// reset the state and variables
					m_School[i]->SetState(m_School[i]->GetPreviousState());
					m_Counter = 0;
					m_CountTarget = MathHelper::rFloatRange(40, 80);
					m_AssingHungerTarget = false;
				}
			}
			break;
		case Fish::FishState::State_Alerted:
			{
				// scatter the fish
				Scatter(m_School[i], 100.0f);
				m_School[i]->SetState(m_School[i]->GetPreviousState());
			}
			break;
		}

		m_School[i]->Update(a_DT);
	}
}

glm::vec3 Liqua::School::Seperation(Fish* a_Fish,  float a_DT )
{
	// The separation rule, so fish will not collide with each other.
	glm::vec3 avoidance = glm::vec3(0, 0, 0);
	for(unsigned int i = 0; i < m_School.size(); i++)
	{
		if(a_Fish != m_School[i] && m_School[i]->GetCurrentState() != Fish::FishState::State_Hungry)
		{
			glm::vec3 difference = m_School[i]->GetPosition() - a_Fish->GetPosition();
			float dist = glm::length(difference);

			if(a_Fish->GetCurrentState() == Fish::FishState::State_Schooling)
			{
				if(dist < m_DistanceTreshold)
				{
					avoidance = avoidance - difference;
				}
			}
			else
			{
				if(dist < m_DistanceTreshold * 2.5f)
				{
					avoidance = avoidance - difference;
				}
			}
		}
	}

	return avoidance * 0.5f;
}

glm::vec3 Liqua::School::Cohesion(Fish* a_Fish,  float a_DT )
{
	// The cohesion rule, so fish have the tendency to get to the middle of the school
	// The center is stored for checking against the target goal of the school
	m_SchoolCenter = glm::vec3(0, 0, 0);
	int FishAmount = 0;
	for(unsigned int i = 0; i < m_School.size(); i++)
	{
		if(a_Fish != m_School[i] && m_School[i]->GetCurrentState() != Fish::FishState::State_Hungry)
		{
			m_SchoolCenter += m_School[i]->GetPosition();
			FishAmount++;
		}
	}

	m_SchoolCenter = m_SchoolCenter / (float)FishAmount;

	return (m_SchoolCenter - a_Fish->GetPosition()) / COHESION_DIVIDER;
	
}

glm::vec3 Liqua::School::Alignment(Fish* a_Fish,  float a_DT )
{
	// The allignment rule to make sure all fish roughly go in the same direction and orientation.
	glm::vec3 velocity = glm::vec3(0, 0, 0);
	int FishAmount = 0;
	for(unsigned int i = 0; i < m_School.size(); i++)
	{
		if(a_Fish != m_School[i] && m_School[i]->GetCurrentState() != Fish::FishState::State_Hungry)
		{
			velocity += m_School[i]->GetVelocity();
			FishAmount++;
		}
	}

	velocity = velocity / (float)FishAmount;

	velocity = (velocity - a_Fish->GetVelocity()) / ALIGNMENT_DIVIDER;


	return velocity;
}

glm::vec3 Liqua::School::TargetAttraction( Fish* a_Fish, float a_DT )
{
	// Make the fish go towards a set point.
	return (m_CurrentTarget - a_Fish->GetPosition()) / TARGET_DIVIDER;
}

void Liqua::School::Scatter(Fish* a_Fish, float a_ScatterSpeed)
{
	// Set the velocity and turning speed of the fish for them to scatter to.
	glm::vec3 scattervel = glm::vec3(MathHelper::rFloatRange(-a_ScatterSpeed, a_ScatterSpeed), MathHelper::rFloatRange(-a_ScatterSpeed, a_ScatterSpeed), MathHelper::rFloatRange(-a_ScatterSpeed, a_ScatterSpeed));
	a_Fish->SetTurningSpeed(10.0f);
	a_Fish->SetVelocity(scattervel);
}

glm::vec3 Liqua::School::DampenVelocity( Fish* a_Fish, glm::vec3& a_Velocity, float a_DT )
{
	// Limit the total velocity based on what is set as the max speed.
	if(glm::length(a_Velocity) > m_MaxSpeed)
	{
		a_Velocity = (a_Velocity / glm::length(a_Velocity)) * m_MaxSpeed;
	}

	glm::vec3 vel = a_Fish->GetVelocity();
	a_Velocity.x = MathHelper::Lerp(vel.x, a_Velocity.x, a_DT * m_MaxSpeed);
	a_Velocity.y = MathHelper::Lerp(vel.y, a_Velocity.y, a_DT * m_MaxSpeed);
	a_Velocity.z = MathHelper::Lerp(vel.z, a_Velocity.z, a_DT * m_MaxSpeed);

	return a_Velocity;
}

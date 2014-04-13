#include "Liqua.h"
#include "Mesh.h"
#include "Shader.h"
#include "Fish.h"

Liqua::Fish::Fish()
{
	// load the fish model
	m_Fish = new Mesh("../Resources/Models/Fish/LemonFish.omd");

	// set initial values.
	m_Position = glm::vec3(100, -17, 0);
	m_Velocity = glm::vec3(0, 0, 0);
	m_Orientation = glm::quat();
	m_PreviousOrientation = glm::quat();

	m_Fish->Scale(glm::vec3(0.4f, 0.4f, 0.4f));

	m_TurningSpeed = 1.0f;

	m_SpeedModifier = MathHelper::rFloatRange(0.1f, 0.3f);

	m_State = State_Schooling;
}

Liqua::Fish::~Fish()
{
	// cleaning up
	delete m_Fish;
}

void Liqua::Fish::SetShader( Shader* a_Shader )
{
	// Set the shader the fish should use.
	m_Shader = a_Shader;
	m_Fish->SetShader(m_Shader);
}

void Liqua::Fish::Update( float a_DT )
{
	// push the fish down if it gets to close to waterlevel
	if(m_Position.y >= -2.5)
		m_Velocity.y -= 0.25;

	// Integrate the position of the fish with the velocity over time.
	m_Position = Integrate(m_Position, m_Velocity, a_DT);
	// Calculate the orientation of the fish based on the velocity.
	m_Orientation = CalculateOrientation(m_Velocity);

	// slerp the orientation with the previous orientation to make a smooth turn.
	m_Orientation = glm::slerp(m_PreviousOrientation, m_Orientation, m_TurningSpeed * a_DT);

	// set the rotation of the fish
	m_Fish->Rotate(m_Orientation);

	// and store it as the previous orientation
	m_PreviousOrientation = m_Orientation;

	// set the position of the fish
	m_Fish->Translate(m_Position);	
}

glm::quat Liqua::Fish::CalculateOrientation( glm::vec3& a_Velocity )
{
	// Calculate the heading of the fish
	float heading = -atan2(a_Velocity.x, -a_Velocity.z) - (3.14f/2.0f);
	heading *= 180.0f / 3.14f;

	float pitch = 0;

	// Calculate the pitch of the fish, make sure the Y component isn't 0. else it crashes
	if(a_Velocity.y != 0)
	{
		float YoverX = a_Velocity.y / sqrt(a_Velocity.z * a_Velocity.z + a_Velocity.x * a_Velocity.x);
		pitch = -atan(YoverX);
	}

	pitch *= 180.0f / 3.14f;

	// clamp the pitch so the fish won't end up looking straight up
	pitch = MathHelper::Clamp(pitch, -40.0f, 40.0f);

	// Create the final oriantation and return it
	glm::quat H = glm::angleAxis(heading, glm::vec3(0, 1, 0));
	glm::quat P = glm::angleAxis(pitch, glm::vec3(0, 0, 1));

	glm::quat Orientation = H * P;

	return Orientation;
}

glm::vec3 Liqua::Fish::Integrate( glm::vec3& a_Position, glm::vec3& a_Velocity, float a_DT )
{
	// simple integration 
	return a_Position += a_Velocity * a_DT;
}

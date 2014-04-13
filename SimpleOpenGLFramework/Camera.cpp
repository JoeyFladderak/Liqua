#include "Liqua.h"
#include "Camera.h"

#ifdef WIN32
#define _USE_MATH_DEFINES 
#include <cmath>
#else
#include <math.h>
#endif

#define ToRadian(x) (float)(((x) * 3.14159265358979323846f / 180.0f))
#define ToDegree(x) (float)(((x) * 180.0f / 3.14159265358979323846f))

Camera::Camera()
{
	m_IsInitialized = false;

	m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
	m_Target = glm::vec3(0.0f, 0.0f, 1.0f);
	m_Target = glm::normalize(m_Target);
	m_Up = glm::vec3(0.0f, 1.0f, 0.0f);

	Init();
}

Camera::Camera( const glm::vec3& a_Position, const glm::vec3& a_Target )
{
	m_IsInitialized = false;

	m_Position = a_Position;
	m_Target = a_Target;
	m_Target = glm::normalize(m_Target);
	m_Up = glm::vec3(0.0f, 1.0f, 0.0f);

	Init();
}

Camera::~Camera()
{

}

void Camera::SetViewport( int a_X, int a_Y, int a_Width, int a_Height )
{
	glViewport(a_X, a_Y, a_Width, a_Height);
}

void Camera::SetProjection( float a_FoV, float a_Aspect, float a_ZNear, float a_ZFar )
{
	m_ProjectionMatrix = glm::perspective(a_FoV, a_Aspect, a_ZNear, a_ZFar);
}

bool Camera::OnKeyboard( int a_Key )
{
	bool ret = false;

	switch(a_Key)
	{
	case GLUT_KEY_UP:
		{
			m_Position += (-m_Target * 1.0f);
			ret = true;
		}
		break;
	case GLUT_KEY_DOWN:
		{
			m_Position -= (-m_Target * 1.0f);
			ret = true;
		}
		break;
	case GLUT_KEY_LEFT:
		{
			glm::vec3 left = glm::cross(m_Target, m_Up);
			left = glm::normalize(left);
			left *= 1.0f;
			m_Position += left;
			ret = true;
		}
		break;
	case GLUT_KEY_RIGHT:
		{
			glm::vec3 right = glm::cross(m_Up, m_Target);
			right = glm::normalize(right);
			right *= 1.0f;
			m_Position += right;
			ret = true;
		}
		break;
	}

	Update();

	return ret;
}

void Camera::OnMouse( int a_X, int a_Y )
{
	const int DeltaX = a_X - m_MousePosition.x;
	const int DeltaY = a_Y - m_MousePosition.y;	

	m_AngleH -= (float)DeltaX / 30.0f;
	m_AngleV -= (float)DeltaY / 30.0f;

	Update();
}

void Camera::Update()
{
	const glm::vec3 vaxis = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::vec3 view = glm::vec3(1.0f, 0.0f, 0.0f);
	view = glm::rotate(view, m_AngleH, vaxis);
	view = glm::normalize(view);

	glm::vec3 haxis = glm::cross(vaxis, view);
	haxis = glm::normalize(haxis);
	view = glm::rotate(view, m_AngleV, haxis);

	m_Target = view;
	m_Target = glm::normalize(m_Target);

	m_Up = glm::cross(m_Target, haxis);
	m_Up = glm::normalize(m_Up);

	glm::vec3 N = m_Target;
	N = glm::normalize(N);

	glm::vec3 U = m_Up;
	U = glm::normalize(U);
	U = glm::cross(U, N);

	glm::vec3 V = glm::cross(N, U);

	glm::mat4 pos(1.0f);
	pos[0][0] = 1.0f; pos[1][0] = 0.0f; pos[2][0] = 0.0f; pos[3][0] = -m_Position.x;
	pos[0][1] = 0.0f; pos[1][1] = 1.0f; pos[2][1] = 0.0f; pos[3][1] = -m_Position.y; 
	pos[0][2] = 0.0f; pos[1][2] = 0.0f; pos[2][2] = 1.0f; pos[3][2] = -m_Position.z; 
	pos[0][3] = 0.0f; pos[1][3] = 0.0f; pos[2][3] = 0.0f; pos[3][3] = 1.0f;

	glm::mat4 rot(1.0f);
	rot[0][0] = U.x; rot[1][0] = U.y; rot[2][0] = U.z; rot[3][0] = 0.0f;
	rot[0][1] = V.x; rot[1][1] = V.y; rot[2][1] = V.z; rot[3][1] = 0.0f; 
	rot[0][2] = N.x; rot[1][2] = N.y; rot[2][2] = N.z; rot[3][2] = 0.0f; 
	rot[0][3] = 0.0f; rot[1][3] = 0.0f; rot[2][3] = 0.0f; rot[3][3] = 1.0f;

	m_ViewMatrix = rot * pos;

	//m_ViewMatrix = glm::reflect3D(m_ViewMatrix, glm::vec3(0, 1, 0));
}

void Camera::Init()
{
	glm::vec3 Htarget = glm::vec3(m_Target.x, 0.0f, m_Target.z);
	Htarget = glm::normalize(Htarget);

	if(Htarget.z >= 0.0f)
	{
		if(Htarget.x >= 0.0f)
		{
			m_AngleH = 360.0f - ToDegree(asin(Htarget.z));
		}
		else
		{
			m_AngleH = 180.0f + ToDegree(asin(Htarget.z));
		}
	}
	else
	{
		if(Htarget.x >= 0.0f)
		{
			m_AngleH = ToDegree(asin(-Htarget.z));
		}
		else
		{
			m_AngleH = 90.0f + ToDegree(asin(-Htarget.z));
		}
	}

	m_AngleV = -ToDegree(asin(m_Target.y));

	m_MousePosition.x = SCRWIDTH / 2;
	m_MousePosition.y = SCRHEIGHT / 2;

	glutWarpPointer(m_MousePosition.x, m_MousePosition.y);

	Update();

	m_IsInitialized = true;
}

void Camera::Forward()
{
	m_Position += (-m_Target * 1.0f);
	Update();
}

void Camera::BackWard()
{
	m_Position -= (-m_Target * 1.0f);
	Update();
}

void Camera::Left()
{
	glm::vec3 left = glm::cross(m_Target, m_Up);
	left = glm::normalize(left);
	left *= 1.0f;
	m_Position += left;
	Update();
}

void Camera::Right()
{
	glm::vec3 right = glm::cross(m_Up, m_Target);
	right = glm::normalize(right);
	right *= 1.0f;
	m_Position += right;
	Update();
}

void Camera::HorizontalRotate( float a_Amount )
{
	m_AngleH += a_Amount;
	Update();
}

void Camera::VerticalRotate( float a_Amount )
{
	m_AngleV += a_Amount;
	Update();
}

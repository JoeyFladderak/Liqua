#ifndef _CAMERA_H_
#define _CAMERA_H_

class Camera
{
public:
	Camera();
	Camera(const glm::vec3& a_Position, const glm::vec3& a_Target);
	~Camera();

	void SetViewport(int a_X, int a_Y, int a_Width, int a_Height);
	void SetProjection(float a_FoV, float a_Aspect, float a_ZNear, float a_ZFar);

	bool OnKeyboard(int a_Key);
	void OnMouse(int a_X, int a_Y);

	glm::mat4 GetViewMatrix() {return m_ViewMatrix;}
	glm::mat4 GetProjectionMatrix() {return m_ProjectionMatrix;}
	glm::mat4 GetViewProjectionMatrix();

	glm::vec3 GetPosition() {return m_Position;}

	void Forward();
	void BackWard();
	void Left();
	void Right();
	void HorizontalRotate(float a_Amount);
	void VerticalRotate(float a_Amount);

	bool IsInitialized() {return m_IsInitialized;}

protected:

	void Init();
	void Update();

	glm::vec3 m_Position;
	glm::vec3 m_Target;
	glm::vec3 m_Up;

	float m_AngleH;
	float m_AngleV;

	glm::mat4 m_ViewProjectionMatrix;
	glm::mat4 m_ViewMatrix;
	glm::mat4 m_ProjectionMatrix;

	glm::ivec2 m_MousePosition;

	bool m_NeedsUpdate;
	bool m_IsInitialized;

};
#endif
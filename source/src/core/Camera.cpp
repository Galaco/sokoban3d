#include "Camera.h"

#include <core/helpers/Keyboard.h>

#define PI 3.14159265359
#define TO_RAD(x) (x*(PI/180))

const static float StepScale = 0.1f;
const static glm::mat4 ModelMatrix = glm::mat4(1.0);

Camera::Camera(){
	oldHorizontalAngle = -1;
	oldVerticalAngle = -1;
	oldPosition = glm::vec3(-63.65432f);
	horizontalAngle = 3.14f;
	verticalAngle = 0.0f;
	speed = 5.0f; // 3 units / second
	mouseSpeed = 0.010f;

	m_target = glm::vec3(0.0f, 0.0f, 1.0f);
	m_up = glm::vec3(0.0f, 1.0f, 0.0f);
	m_right = glm::vec3(1.0f, 0.0f, 0.0f);

	this->fov = 70.f;
	this->aspect_ratio = static_cast<float>(Config::_WINDOWWIDTH / Config::_WINDOWHEIGHT);
	this->near_plane = 0.25f;
	this->far_plane = 4096.f;

	useMouse = false;

	m_id.gen();
	Pipeline::setProjectionMatrix(glm::perspective(fov, aspect_ratio, near_plane, far_plane));
	rebuildView();

	cameraMode = CameraMode::CAMERA_FREE_LOOK;
}


Camera::Camera(const char* name){
	horizontalAngle = 3.14f;
	verticalAngle = 0.0f;
	speed = 5.0f; // 3 units / second
	mouseSpeed = 0.010f;

	m_target = glm::vec3(0.0f, 0.0f, 1.0f);
	m_up     = glm::vec3(0.0f, 1.0f, 0.0f);

	float width = (float)Config::_WINDOWWIDTH;
	float height = (float)Config::_WINDOWHEIGHT;
	float  ratio = (width /height);
	this->fov = 70.f;
	this->aspect_ratio = ratio;
	this->near_plane = 0.25f;
	this->far_plane = 4096.f;

	m_id.gen(name);
	Pipeline::setProjectionMatrix(glm::perspective(fov, this->aspect_ratio, near_plane, far_plane));
	rebuildView();

	cameraMode = CameraMode::CAMERA_FREE_LOOK;
}

Camera::~Camera(){
}

void Camera::update(){
	if (cameraMode == CameraMode::CAMERA_FREE_LOOK)
	{
		if (useMouse)
		{
			m_transform.getOrientation().y += Config::_SENSITIVITY * float(Config::_WINDOWWIDTH / 2 - Mouse::_X);
			m_transform.getOrientation().x += Config::_SENSITIVITY * float(Config::_WINDOWHEIGHT / 2 - Mouse::_Y);
		}
		//Rebuild MVP only when camera moved
		if (m_transform.getOrientation().x == oldVerticalAngle &&
			m_transform.getOrientation().y == oldHorizontalAngle &&
			m_transform.getPosition() == oldPosition &&
			m_transform.getOrientation() == oldRotation
			) {


			oldPosition = m_transform.getPosition();
			oldRotation = m_transform.getOrientation();

			return;
		}

		if (m_transform.getOrientation().x != oldVerticalAngle ||
			m_transform.getOrientation().y != oldHorizontalAngle){
			m_dir = glm::vec3(
				-cos(m_transform.getOrientation().x) * sin(m_transform.getOrientation().y),
				sin(m_transform.getOrientation().x),
				-cos(m_transform.getOrientation().x) * cos(m_transform.getOrientation().y)
				);

			m_right = glm::vec3(
				-sin(m_transform.getOrientation().y - 3.1415f / 2.0f),
				0,
				-cos(m_transform.getOrientation().y - 3.1415f / 2.0f)
				);
			m_up = glm::cross(m_right, m_dir);
		}



		Pipeline::setViewMatrix(glm::lookAt(m_transform.getPosition(), m_transform.getPosition() + m_dir, m_up));
	}
	if (cameraMode == CameraMode::CAMERA_ORBIT)
	{
		float x = Config::_SENSITIVITY * float(Config::_WINDOWWIDTH / 2 - Mouse::_X);
		float y = Config::_SENSITIVITY * float(Config::_WINDOWHEIGHT / 2 - Mouse::_Y);

		if (Keyboard::get("left"))
		{
			x = -0.1f;
		}
		else {
			if (Keyboard::get("right"))
			{
				x = 0.1f;
			}
		}
		if (Keyboard::get("up"))
		{
			y = -0.1f;
		}
		else {
			if (Keyboard::get("down"))
			{
				y = 0.1f;
			}
		}
		m_transform.getOrientation().y += x;
		m_transform.getOrientation().x += y;

		if ((m_transform.getOrientation().x > 360) || (m_transform.getOrientation().x < -360)) m_transform.getOrientation().x = 0;
		if ((m_transform.getOrientation().y > 360) || (m_transform.getOrientation().y < -360)) m_transform.getOrientation().y = 0;

		glm::vec3 forward = glm::normalize(m_transform.getPosition() - glm::vec3(0,0,0));
		glm::vec3 right = glm::cross(glm::vec3(0, 1, 0), forward);
		glm::vec3 up = glm::cross(right, forward);

		m_transform.getPosition() = glm::rotate(m_transform.getPosition(), -x, up);
		m_transform.getPosition() = glm::rotate(m_transform.getPosition(), y, right);


		forward = glm::vec3(0,0,0) - m_transform.getPosition();

		m_right = glm::cross(up, forward);
		up = glm::normalize(glm::cross(forward, m_right));
		Pipeline::setViewMatrix(glm::lookAt(m_transform.getPosition(), glm::vec3(0, 0, 0), up));
	}


	Pipeline::Eye = m_transform.getPosition();

	oldHorizontalAngle = m_transform.getOrientation().y;
	oldVerticalAngle = m_transform.getOrientation().x;
	oldPosition = m_transform.getPosition();
	oldRotation = m_transform.getOrientation();
}

void Camera::addSkybox(std::string filename){
	m_pSkybox.load(filename);
	m_pSkybox.setzFar(far_plane);
	m_pSkybox.createCube();
}


Skybox& Camera::getSkybox(){
    return m_pSkybox;  
}

void Camera::goForward(){
    m_transform.getPosition() += (m_dir * speed);
}

void Camera::goBackward(){
    m_transform.getPosition() -= (m_dir * speed);
}

void Camera::goLeft(){
    m_transform.getPosition() -= (m_right * speed);
}

void Camera::goRight(){
	m_transform.getPosition() += (m_right * speed);
}

void Camera::goUp(){
	m_transform.getPosition() += (m_up * speed);
}

void Camera::goDown(){
	m_transform.getPosition() -= (m_up * speed);
}

bool Camera::toggleMouseControl()
{
	useMouse = !useMouse;
	return useMouse;
}

void Camera::rebuildView()
{
	m_dir = glm::vec3(
		-cos(m_transform.getOrientation().x) * sin(m_transform.getOrientation().y),
		sin(m_transform.getOrientation().x),
		-cos(m_transform.getOrientation().x) * cos(m_transform.getOrientation().y)
		);

	m_right = glm::vec3(
		-sin(m_transform.getOrientation().y - 3.1415f / 2.0f),
		0,
		-cos(m_transform.getOrientation().y - 3.1415f / 2.0f)
		);
	m_up = glm::cross(m_right, m_dir);

	Pipeline::setViewMatrix(glm::lookAt(m_transform.getPosition(), m_transform.getPosition() + m_dir, m_up));
	Pipeline::Eye = m_transform.getPosition();
}


void Camera::rotate(glm::vec3 axis, float angle, bool additive)
{
	if (cameraMode == CameraMode::CAMERA_ORBIT)
	{
		float x = 0;
		float y = 0;

		if (axis.x == 1)
		{
			x = angle;
		}
		if (axis.y == 1)
		{
			y = angle;
		}

		if (additive)
		{
			m_transform.getOrientation().y += x;
			m_transform.getOrientation().x += y;
		}
		else {
			m_transform.getOrientation().y = x;
			m_transform.getOrientation().x = y;
		}

		if (m_transform.getOrientation().x > 360) m_transform.getOrientation().x -= 360;
		if (m_transform.getOrientation().x < -360)  m_transform.getOrientation().x += 360;

		if (m_transform.getOrientation().y > 360) m_transform.getOrientation().y -= 360;
		if (m_transform.getOrientation().y < -360)  m_transform.getOrientation().y += 360;

		glm::vec3 forward = glm::normalize(m_transform.getPosition() - glm::vec3(0, 0, 0));
		glm::vec3 right = glm::cross(glm::vec3(0, 1, 0), forward);
		glm::vec3 up = glm::cross(right, forward);

		m_transform.getPosition() = glm::rotate(m_transform.getPosition(), -x, up);
		m_transform.getPosition() = glm::rotate(m_transform.getPosition(), y, right);


		forward = glm::vec3(0, 0, 0) - m_transform.getPosition();

		m_right = glm::cross(up, forward);
		up = glm::normalize(glm::cross(forward, m_right));
		Pipeline::setViewMatrix(glm::lookAt(m_transform.getPosition(), glm::vec3(0, 0, 0), up));
	}


	Pipeline::Eye = m_transform.getPosition();

	oldHorizontalAngle = m_transform.getOrientation().y;
	oldVerticalAngle = m_transform.getOrientation().x;
	oldPosition = m_transform.getPosition();
	oldRotation = m_transform.getOrientation();

}
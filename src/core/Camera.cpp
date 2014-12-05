#include "Camera.h"


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
        
    m_pSkybox = nullptr;

	//m_transform = new CTransform();

	m_id.gen();
	Pipeline::setProjectionMatrix(glm::perspective(fov, aspect_ratio, near_plane, far_plane));
	rebuildView();
}


Camera::Camera(const char* name){
	horizontalAngle = 3.14f;
	verticalAngle = 0.0f;
	speed = 5.0f; // 3 units / second
	mouseSpeed = 0.010f;

	m_target = glm::vec3(0.0f, 0.0f, 1.0f);
	m_up     = glm::vec3(0.0f, 1.0f, 0.0f);

	this->fov = 70.f;
	this->aspect_ratio = static_cast<float>(Config::_WINDOWWIDTH / Config::_WINDOWHEIGHT);
	this->near_plane = 0.25f;
	this->far_plane = 4096.f;

	m_pSkybox = nullptr;

	//m_transform = new CTransform();

	m_id.gen(name);
	Pipeline::setProjectionMatrix(glm::perspective(fov, aspect_ratio, near_plane, far_plane));
	rebuildView();
}

Camera::~Camera(){
}

void Camera::update(){
	if (useMouse)
	{
		m_transform.getOrientation().y += mouseSpeed * float(Config::_WINDOWWIDTH / 2 - Keyboard::MOUSEX);
		m_transform.getOrientation().x += mouseSpeed * float(Config::_WINDOWHEIGHT / 2 - Keyboard::MOUSEY);
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
		m_up = glm::cross( m_right, m_dir );
	}

	
	
	Pipeline::setViewMatrix(glm::lookAt(m_transform.getPosition(), m_transform.getPosition()+m_dir, m_up));

	//Pipeline::MVP = Pipeline::VP * ModelMatrix;
	Pipeline::Eye = m_transform.getPosition();

	oldHorizontalAngle = m_transform.getOrientation().y;
	oldVerticalAngle = m_transform.getOrientation().x;
	oldPosition = m_transform.getPosition();
	oldRotation = m_transform.getOrientation();
}

void Camera::addSkybox(Skybox* skybox){
    m_pSkybox = skybox;
	m_pSkybox->setzFar(far_plane);
	m_pSkybox->createCube();
}


Skybox* Camera::getSkybox(){
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
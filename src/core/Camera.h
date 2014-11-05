#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include <core/Config.h>
#include <core/Keyboard.h>
#include <core/Pipeline.h>

#include "Entity.h"
#include <core/resources/Skybox.h>

class Camera: public Entity{
public:
	Camera();
	Camera(const char*);
	~Camera();

	void update();
        
	void addSkybox(Skybox*);
	Skybox* getSkybox();
    
	void goForward();
	void goBackward();
	void goLeft();
	void goRight();

	float horizontalAngle, verticalAngle;
private:
	Skybox* m_pSkybox;
	glm::vec3 m_up, m_target, m_dir, m_right;
	float fov, aspect_ratio, near_plane, far_plane;

	float speed, mouseSpeed;

	float oldHorizontalAngle, oldVerticalAngle;
	glm::vec3 oldPosition;
};
#endif

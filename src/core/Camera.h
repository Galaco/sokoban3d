/*********************************************************************
Project: Dissertation
Author: Josh Martin

Name: Camera
Description: Representation of the players view.
*********************************************************************/
#ifndef CAMERA_H
#define CAMERA_H

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "Entity.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <core/helpers/Config.h>
#include "helpers/Mouse.h"
#include "helpers/Pipeline.h"

#include <core/resources/Skybox.h>
enum CameraMode{
	CAMERA_FREE_LOOK = 0,
	CAMERA_ORBIT
};

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
	void goUp();
	void goDown();

	void setCameraMode(int i){
		cameraMode = i;
	};

	bool toggleMouseControl();
	void rebuildView();

	float horizontalAngle, verticalAngle;
private:
	Skybox* m_pSkybox;
	glm::vec3 m_up, m_target, m_dir, m_right;
	float fov, aspect_ratio, near_plane, far_plane;

	float speed, mouseSpeed;

	float oldHorizontalAngle, oldVerticalAngle;
	glm::vec3 oldPosition, oldRotation;

	bool useMouse;
	int cameraMode;
};
#endif

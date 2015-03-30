/*********************************************************************
Project: Dissertation
Author: Josh Martin

Name: State
Description: A state within the state machine. Could also be referred 
			 to as a scene. More than anything, its a data store that 
			 classes can get and set, and are contained within.
*********************************************************************/
#ifndef STATE_H
#define STATE_H

#include <string>

#include <core/Entity.h>
#include <core/Camera.h>
#include <core/resources/DirectionalLight.h>
#include <core/resources/PointLight.h>
#include <core/resources/LuaScript.h>

#include <json/json.h>

class State {
public:
	State();
	virtual ~State();

	virtual void update(float dt);
	
	std::map<std::string, Entity>& getEntities();
	std::vector<Camera>& getCameras();
	std::vector<PointLight>& getPointLights();

	bool load(std::string filename);

	void addEntity(Entity);
	void addCamera(Camera);
	void addPointLight(PointLight);

	Entity& getEntity(std::string);
	Camera& getCamera(std::string);
	Camera* getCurrentCamera();
	void setCurrentCamera(Camera* camera);
	DirectionalLight& getDirectionalLight();


	bool& wantsPriority();
	bool& canDeprioritise();

	unsigned int priority;
	std::string m_name;
	
protected:

	bool requestedPriority;
	bool canHalt;
	float m_runningTime;

	Camera* m_currentCamera;

	std::map<std::string, Entity>	m_mEntityList;
	std::vector<Camera>	m_mCameraList;
	std::vector<PointLight>	m_listPointLight;
	DirectionalLight	m_directionalLight;
};
#endif
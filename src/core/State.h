#ifndef STATE_H
#define STATE_H

#include <string>

#include <core/Camera.h>
#include <core/Entity.h>

class State {
public:
	State();
	virtual ~State();

	virtual void update(float dt);
	
	std::map<std::string, Entity*>& getEntities();
	std::vector<Camera*>& getCameras();

	void addEntity(Entity*);
	void addCamera(Camera*);

	Entity* getEntity(std::string);
	Camera* getCamera(std::string);
	Camera* getCurrentCamera();

	bool& wantsPriority();
	bool& canDeprioritise();

	unsigned int priority;
	
protected:
	std::string m_name;

	bool requestedPriority;
	bool canHalt;
	float m_runningTime;

	Camera* m_currentCamera;

	std::map<std::string, Entity*>	m_mEntityList;
	std::vector<Camera*>	m_mCameraList;
};
#endif
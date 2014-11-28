#include "State.h"

State::State()
{
	priority = 1;
	requestedPriority = false;
	canHalt = false;
	m_runningTime = 0;
	m_currentCamera = nullptr;
	m_directionalLight = new DirectionalLight;
}

State::~State()
{  
	auto it = m_mEntityList.begin();
	while (it != m_mEntityList.end())
	{
		delete it->second;
	}
	auto it2 = m_mCameraList.begin();
	while (it2 != m_mCameraList.end())
	{
		delete it->second;
	}

	delete m_currentCamera;
	delete m_directionalLight;
}


void State::update(float dt = 0)
{
	m_runningTime += dt;
	auto it = m_mCameraList.begin();
	while(it != m_mCameraList.end()) {
		(*it)->update();
		++it;
	}
}


std::map<std::string, Entity*>& State::getEntities()
{
	return m_mEntityList;
}

std::vector<Camera*>& State::getCameras()
{
	return m_mCameraList;
}

std::vector<PointLight*>& State::getPointLights()
{
	return m_listPointLight;
}

Entity* State::getEntity(std::string name)
{
	if (m_mEntityList.find(name) != m_mEntityList.end()) 
	{
		return m_mEntityList[name];
	}
	else
	{
		return nullptr;
	}

}

Camera* State::getCamera(std::string name)
{
	auto it = m_mCameraList.begin();
	while (it != m_mCameraList.end())
	{
		if ((*it)->getId() == name)
		{
			return (*it);
		}
	}
	return nullptr;

}

void State::addEntity(Entity* entity){
	if (m_mEntityList.find(entity->getId()) != m_mEntityList.end())
	{
		delete entity;
		return;
	}
	m_mEntityList[entity->getId()] = entity;
}

void State::addCamera(Camera* entity){
	auto it = m_mCameraList.begin();
	while (it != m_mCameraList.end())
	{
		if (entity->getId() == (*it)->getId()){
			return;
		}
		++it;
	}
	m_mCameraList.push_back(entity);

	if (m_mCameraList.size() == 1)
	{
		m_currentCamera = entity;
	}
}

void State::addPointLight(PointLight* light){
	m_listPointLight.push_back(light);
}

Camera* State::getCurrentCamera()
{
	return m_currentCamera;
}

DirectionalLight* State::getDirectionalLight()
{
	return m_directionalLight;
}

bool& State::wantsPriority()
{
	return requestedPriority;
}
bool& State::canDeprioritise()
{
	return canHalt;
}
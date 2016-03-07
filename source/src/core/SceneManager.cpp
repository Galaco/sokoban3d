#include "SceneManager.h"

std::map<std::string, Scene*> SceneManager::m_stateList;
Scene* SceneManager::m_pActiveState = nullptr;

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
    
}

void SceneManager::initialize()
{
    
}

void SceneManager::terminate()
{
    
}

void SceneManager::update(float dt)
{
	Scene::ForceRecache = false;
	m_pActiveState->update(dt);
	auto it = m_stateList.begin();
	while (it != m_stateList.end())
	{
		if ( (*it).second->wantsPriority() && (*it).second != m_pActiveState)
		{
			if (m_pActiveState->canDeprioritise())
			{
				setActiveState((*it).second);
				(*it).second->wantsPriority() = false;
			}
		}
		++it;
	}
}

void SceneManager::setActiveState(Scene* newState)
{
	m_pActiveState = newState;
	System::setCurrentState(newState);
}

Scene* SceneManager::getActiveState()
{
	return m_pActiveState;
}


Scene* SceneManager::getState(std::string stateName)
{
	if (m_stateList.find(stateName) == m_stateList.end()) return nullptr;
	return m_stateList[stateName];
}


void SceneManager::addState(Scene* state, std::string name)
{
	if (m_stateList.find(name) != m_stateList.end())
	{
		return;
	}
	m_stateList[name] = state;
	if (m_stateList.size() == 1)
	{
		setActiveState(m_stateList[name]);
	}
}
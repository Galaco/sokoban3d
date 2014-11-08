#include "StateManager.h"

std::map<std::string, State*> StateManager::m_stateList;
State* StateManager::m_pActiveState = nullptr;

StateManager::StateManager()
{
}

StateManager::~StateManager()
{
    
}

void StateManager::initialize()
{
    
}

void StateManager::terminate()
{
    
}

void StateManager::update(float dt)
{
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
				System::setCurrentCamera((*it).second->getCurrentCamera());
			}
		}
		++it;
	}
}

void StateManager::setActiveState(State* newState)
{
	m_pActiveState = newState;
	System::setCurrentState(newState);
}

State* StateManager::getActiveState()
{
	return m_pActiveState;
}


State* StateManager::getState(std::string stateName)
{
	if (m_stateList.find(stateName) == m_stateList.end()) return nullptr;
	return m_stateList[stateName];
}


void StateManager::addState(State* state, std::string name)
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
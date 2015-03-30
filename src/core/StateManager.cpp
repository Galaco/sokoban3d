#include "StateManager.h"

std::map<std::string, State> StateManager::m_stateList;
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
		if ( (*it).second.wantsPriority() && &((*it).second) != m_pActiveState)
		{
			if (m_pActiveState->canDeprioritise())
			{
				setActiveState((*it).second.m_name);
				(*it).second.wantsPriority() = false;
			}
		}
		++it;
	}
}

void StateManager::setActiveState(std::string statename)
{
	if (m_stateList.find(statename) != m_stateList.end())
	{
		m_pActiveState = &m_stateList[statename];
		System::setCurrentState(&m_stateList[statename]);
	}
	//System::setCurrentCamera((*it).second->getCurrentCamera());
}

State* StateManager::getActiveState()
{
	return m_pActiveState;
}


State& StateManager::getState(std::string stateName)
{
	if (m_stateList.find(stateName) == m_stateList.end())
		return m_stateList[stateName];
	else
		return *m_pActiveState;
}


State& StateManager::addState(std::string name)
{
	if (m_stateList.find(name) != m_stateList.end())
	{
		return m_stateList[name];
	}
	m_stateList[name] = State();
	if (m_stateList.size() == 1)
	{
		setActiveState(name);
	}

	return m_stateList[name];
}


State& StateManager::addState(State state, std::string name)
{
	if (m_stateList.find(name) != m_stateList.end())
	{
		return m_stateList[name];
	}
	m_stateList[name] = state;
	if (m_stateList.size() == 1)
	{
		setActiveState(name);
	}

	return m_stateList[name];


}
#include "System.h"

EventManager System::m_EventManager;
//Camera* System::m_currentCamera;
State*	System::m_CurrentState;
State*	System::m_PreviousState;

System::System(){
    //m_currentCamera = nullptr;
	m_PreviousState = nullptr;
}

System::~System(){
    
}

void System::initialize(){
    
}

void System::update(float dt){
	
}

void System::terminate(){
    
}

//void System::setCurrentCamera(Camera* camera){
//	m_currentCamera = camera;
//}


void System::setCurrentState(State* state){
	m_PreviousState = m_CurrentState;
	m_CurrentState = state;
}

void System::rebuildCache()
{

}

void System::FixedUpdate()
{
	static int i = 0;
	if (i == 2)
	{
		m_PreviousState = m_CurrentState;
		i = 0;
	}
	else {
		++i;
	}
}
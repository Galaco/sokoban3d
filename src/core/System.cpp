#include "System.h"

EventManager System::m_EventManager;
Scene*	System::m_CurrentState;
Scene*	System::m_PreviousState;

System::System(){
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

void System::setCurrentState(Scene* state){
	m_PreviousState = m_CurrentState;
	m_CurrentState = state;
}

void System::rebuildCache()
{

}

void System::FixedUpdate()	//Function exists to allow system to properly re-cache themselves
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
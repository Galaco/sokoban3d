#include "System.h"

EventManager System::m_EventManager;
Camera* System::m_currentCamera;
State*	System::m_CurrentState;

System::System(){
    m_currentCamera = nullptr;
}

System::~System(){
    
}

void System::initialize(){
    
}

void System::update(float dt){
    
}

void System::terminate(){
    
}

void System::setCurrentCamera(Camera* camera){
	m_currentCamera = camera;
}


void System::setCurrentState(State* state){
	m_CurrentState = state;
}
/*********************************************************************
Project: Dissertation
Author: Josh Martin

Name: System
Description: Abstract System class of the component-system 
			 architecture. Should never be instantiated itself, only
			 inherited from.
*********************************************************************/
#ifndef SYSTEM_H
#define SYSTEM_H

#include "EventManager.h"
#include "State.h"
//#include "Camera.h"

class System {
public:
	System();
	~System();
        
    virtual void initialize();
       
    virtual void update(float);
        
    virtual void terminate();

	//static void setCurrentCamera(Camera*);
	static void setCurrentState(State*);

protected:
	static EventManager m_EventManager;
	//static Camera*		m_currentCamera;
	static State*		m_CurrentState;
};
#endif
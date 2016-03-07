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

#include <core/Logger.h>

#include "EventManager.h"
#include "Scene.h"


#include <core/Entity.h>

class System {
public:
	System();
	~System();
        
    virtual void initialize();
       
    virtual void update(float);
        
    virtual void terminate();

	static void setCurrentState(Scene*);

	static void FixedUpdate();

protected:
	virtual void rebuildCache();
	static EventManager m_EventManager;
	static Scene*		m_CurrentState;
	static Scene*		m_PreviousState;
};
#endif
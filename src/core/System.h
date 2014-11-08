#ifndef SYSTEM_H
#define SYSTEM_H

#include "Camera.h"
#include "EventManager.h"
#include "State.h"

class System {
public:
	System();
	~System();
        
    virtual void initialize();
       
    virtual void update(float);
        
    virtual void terminate();

	static void setCurrentCamera(Camera*);
	static void setCurrentState(State*);

protected:
	static EventManager m_EventManager;
	static Camera*		m_currentCamera;
	static State*		m_CurrentState;
};
#endif
#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <map>

#include <core/State.h>
#include <core/System.h>

class StateManager {
public:
	StateManager();
	~StateManager();
        
	static void initialize();
	static void terminate();
	static void update(float dt);

	static void addState(State*, std::string);

	static void setActiveState(State*);
	static State* getActiveState();


	static State* getState(std::string);


	static void requestPriority(std::string);
        

private:
	static std::map<std::string, State*> m_stateList;
	static State* m_pActiveState;
};
#endif
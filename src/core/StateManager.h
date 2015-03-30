/*********************************************************************
Project: Dissertation
Author: Josh Martin

Name: State Machine
Description: Responsible for handling what state is the current state.
			 A state is rsponsible for its own priority and requesting
			 priority. The manager determines what should be active.
			 Only 1 state can be active at once. Non-active states are
			 on-hold.
*********************************************************************/
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

	static State& addState(std::string);
	static State& addState(State state, std::string name);

	static void setActiveState(std::string statename);
	static State* getActiveState();


	static State& getState(std::string);


	static void requestPriority(std::string);
        

private:
	static std::map<std::string, State> m_stateList;
	static State* m_pActiveState;
};
#endif
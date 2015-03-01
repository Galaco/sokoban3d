/*********************************************************************
Project: Dissertation
Author: Josh Martin

Name: Splash Logo State
Description: Exception to rules. Splash state is non-optional, hence
			 the inclusion. The core gamestate that must execute 
			 before game specific code.
*********************************************************************/
#ifndef SPLASHSTATE_H
#define SPLASHSTATE_H

#include <string>

#include <core/State.h>

#include "../../components/CGraphics.h"

class SplashState : public State {
public:
	SplashState();

	void update(float dt);
	int priority;

	Entity* splash;
protected:
};
#endif
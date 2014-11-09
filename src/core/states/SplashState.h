#ifndef SPLASHSTATE_H
#define SPLASHSTATE_H

#include <string>

#include <core/State.h>

#include "../../components/CGraphics.h"

class SplashState: public State {
public:
	SplashState();

	void update(float dt);
	int priority;
protected:
};
#endif
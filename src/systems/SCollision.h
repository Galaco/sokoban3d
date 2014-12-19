/*********************************************************************
Project: Dissertation
Author: Josh Martin

Name: Collision System
Description: System that handles and processes collisions
*********************************************************************/
#ifndef SCOLLISION_H
#define SCOLLISION_H

#include <map>
#include <vector>
#include <core/System.h>


#include <core/helpers/Mouse.h>

#include "../components/CCollision.h"
#include "../components/CSelectable.h"


class SCollision: public System {
public:
	SCollision();
	~SCollision();

	void initialize();
	
	void update(float);

private:
	void processSelectable(CSelectable*);
	void processCollideable(CCollision*);
};
#endif

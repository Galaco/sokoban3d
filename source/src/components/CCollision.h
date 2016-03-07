/*********************************************************************
Project: Dissertation
Author: Josh Martin

Name: Component Selectable
Description: Holds information on whether an object has been selected 
			 by the mouse
*********************************************************************/
#ifndef CCOLLISION_H
#define CCOLLISION_H

#include <string>

#include <core/Component.h>
#include <core/resources/CollisionBoxes.h>

#include <core/Entity.h>

class CCollision: public Component {
public:
	CCollision();
	~CCollision();

	void rebuildCollisionBox(Model* model);
	void buildBoxFromPrimitive(std::string);

	AABB& getCollisionBox();

	void setCollisionBox(AABB bb){ m_collisionBox = bb; };

	float weight;
	bool dynamic;

private:
	AABB m_collisionBox;
};
#endif
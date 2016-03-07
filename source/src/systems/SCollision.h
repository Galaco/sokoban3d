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
#include <math.h>
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
	void processCollideable(CCollision* pCollision, CTransform* pTransform, CCollision* opCollision, CTransform* opTransform);

	glm::vec3 calcMTD(std::vector<glm::vec3> bb1, std::vector<glm::vec3> bb2);
	void rebuildCache();

	static std::map<CCollision*, CTransform*> CCollisionCTransformCache;
	static std::map<CCollision*, CTransform*> DynamicCCollisionCTransformCache;
};
#endif

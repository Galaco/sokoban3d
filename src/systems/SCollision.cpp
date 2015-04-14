#include "SCollision.h"

std::map<CCollision*, CTransform*> SCollision::CCollisionCTransformCache;
std::map<CCollision*, CTransform*> SCollision::DynamicCCollisionCTransformCache;

SCollision::SCollision(){
}

SCollision::~SCollision(){
}

void SCollision::initialize(){
}
	
void SCollision::update(float dt){
	if (m_CurrentState != m_PreviousState)
	{
		rebuildCache();
	}

	auto it = DynamicCCollisionCTransformCache.begin();
	while (it != DynamicCCollisionCTransformCache.end()) {
		auto other = CCollisionCTransformCache.begin();
		while (other != CCollisionCTransformCache.end()) {
			processCollideable((*it).first, (*it).second, (*other).first, (*other).second);
			++other;
		}
		++it;
	}
}

void SCollision::processCollideable(CCollision* pCollision, CTransform* pTransform, CCollision* opCollision, CTransform* opTransform)
{
	if (pCollision == opCollision)
	{
		return;
	}
	std::vector<glm::vec3> box1 = pCollision->getCollisionBox().getBox();
	box1[0] += pTransform->getPosition();
	box1[1] += pTransform->getPosition();
	std::vector<glm::vec3> box2 = opCollision->getCollisionBox().getBox();
	box2[0] += opTransform->getPosition();
	box2[1] += opTransform->getPosition();
	bool gotCollision = true;
	if (box1[1].x < box2[0].x ||
		box1[1].y < box2[0].y ||
		box1[1].z < box2[0].z ||
		box1[0].x > box2[1].x ||
		box1[0].y > box2[1].y ||
		box1[0].z > box2[1].z)
	{
		gotCollision = false;
	}
	if (gotCollision)
	{
		glm::vec3 mtd = calcMTD(box1, box2);

		if (!opCollision->dynamic)	// If the second object is static, it should not be moved
		{
			if (pCollision->getOwner()->getId() != "PLAYER")
			{
				pTransform->getPosition() += mtd;
			}
		}
		else {
			if (opCollision->getOwner()->getId() == "PLAYER")
			{
				pTransform->getPosition() += mtd;
			}
			else {
				opTransform->getPosition() += mtd;
			}
		}
	}
}


glm::vec3 SCollision::calcMTD(std::vector<glm::vec3> bb1, std::vector<glm::vec3> bb2)
{
	//change second box position. bb1 will not change

	glm::vec3 amin = bb1[0];
	glm::vec3 amax = bb1[1];
	glm::vec3 bmin = bb2[0];
	glm::vec3 bmax = bb2[1];

	glm::vec3 mtd;

	float left = (bmin.x - amax.x);
	float right = (bmax.x - amin.x);
	float top = (bmin.y - amax.y);
	float bottom = (bmax.y - amin.y);
	float front = (bmin.z - amax.z);
	float back = (bmax.z - amin.z);

	// box dont intersect   
	if (left > 0 || right < 0) return mtd;
	if (top > 0 || bottom < 0) return mtd;
	if (front > 0 || back < 0) return mtd;

	// box intersect. work out the mtd on both x and y axes.
	if (abs(left) < right)
		mtd.x = left;
	else
		mtd.x = right;

	if (abs(top) < bottom)
		mtd.y = top;
	else
		mtd.y = bottom;
	if (abs(back) < front)
		mtd.z = back;
	else
		mtd.z = front;

	// 0 the axis with the largest mtd value.
	if (abs(mtd.x) < abs(mtd.y)) {
		mtd.y = 0;
		if (abs(mtd.x) < abs(mtd.z)) {
			mtd.z = 0;
		}
		else {
			mtd.x = 0;
		}
	} else {
		mtd.x = 0;
		if (abs(mtd.z) < abs(mtd.y)) {
			mtd.y = 0;
		}
		else {
			mtd.z = 0;
		}
	}

	return mtd;
}

void SCollision::rebuildCache()
{
	CCollisionCTransformCache.clear();
	std::map<std::string, Entity*> entityList = m_CurrentState->getEntities();
	auto it = entityList.begin();
	while (it != entityList.end())
	{
		std::vector<Component*> cList = (*it).second->getComponentsByType("Collision");
		auto CIterator = cList.begin();
		while (CIterator != cList.end())
		{
			CCollisionCTransformCache[static_cast<CCollision*>(*CIterator)] = (*CIterator)->getOwner()->GetTransform();
			if ((static_cast<CCollision*>(*CIterator))->dynamic)
			{
				DynamicCCollisionCTransformCache[static_cast<CCollision*>(*CIterator)] = (*CIterator)->getOwner()->GetTransform();
			}
			++CIterator;
		}
		++it;
	}
}
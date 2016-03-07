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
	if ((m_CurrentState != m_PreviousState) || Scene::ForceRecache)
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

		glm::vec3 mtd;

		mtd = calcMTD(box1, box2);

		
		if (pTransform->getPosition() == pTransform->getOldPosition()) {
			mtd = opTransform->getPosition() - opTransform->getOldPosition();
		} else {
			mtd = pTransform->getPosition() - pTransform->getOldPosition();
		}

		if (!opCollision->dynamic)	// If the second object is static, it should not be moved
		{
			glm::vec3 diff = opTransform->getPosition() - opTransform->getOldPosition();
			glm::vec3 mult;
			if (diff.x != 0) {
				mtd.y = 0;
				mtd.z = 0;
			}
			if (diff.y != 0) {
				mtd.x = 0;
				mtd.z = 0;
			}
			if (diff.z != 0) {
				mtd.y = 0;
				mtd.x = 0;
			}

			pTransform->setPosition(pTransform->getPosition() += mtd);
			return;
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

	float left = (bmax.x - amin.x);
	float right = (bmin.x - amax.x);
	float top = (bmin.y - amax.y);
	float bottom = (bmax.y - amin.y);
	float front = (bmin.z - amax.z);
	float back = (bmax.z - amin.z);

	// box dont intersect   
	if (right > 0 || left < 0) return mtd;
	if (top > 0 || bottom < 0) return mtd;
	if (front > 0 || back < 0) return mtd;


	// box intersect. work out the mtd on both x and y and z axes.
	//X
	if (abs(left) < right) {
		mtd.x = left;
	}
	else {
		mtd.x = right;
	}
	//Y
	if (abs(top) < bottom) {
		mtd.y = top;
	}
	else {
		mtd.y = bottom;
	}
	//Z
	if (abs(back) < front)
		mtd.z = back;
	else
		mtd.z = front;

	// 0 the axis with the largest mtd value.
	if (abs(mtd.x) < abs(mtd.y)) {
		mtd.y = 0;

		if (abs(mtd.x) < abs(mtd.z)) 
			mtd.z = 0;
		else
			mtd.x = 0;
	} else {
		mtd.x = 0;

		if (abs(mtd.y) < abs(mtd.z)) 
			mtd.z = 0;
		else 
			mtd.y = 0;
	}

	return mtd;
}

void SCollision::rebuildCache()
{
	CCollisionCTransformCache.clear();	//Empty cache
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
				DynamicCCollisionCTransformCache[static_cast<CCollision*>(*CIterator)] = (*CIterator)->getOwner()->GetTransform();	//Add transform to collision map cache
			}
			++CIterator;
		}
		++it;
	}
}
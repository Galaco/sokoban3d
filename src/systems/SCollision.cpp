#include "SCollision.h"

SCollision::SCollision(){
}

SCollision::~SCollision(){
}

void SCollision::initialize(){
}
	
void SCollision::update(float dt){
	std::map<std::string, Entity> entityList = m_CurrentState->getEntities();

	auto it = entityList.begin();
	while(it != entityList.end()) {
		std::vector<Component*> cList = (*it).second.getComponentsByType("Selectable");
		auto CIterator = cList.begin();
		while(CIterator != cList.end())
		{
			processSelectable(static_cast<CSelectable*>(*CIterator));
			++CIterator;
		}

		cList = (*it).second.getComponentsByType("Collision");
		CIterator = cList.begin();
		while (CIterator != cList.end())
		{
			processCollideable(static_cast<CCollision*>(*CIterator));
			++CIterator;
		}
		++it;
	}
}


void SCollision::processSelectable(CSelectable* pComponent)
{
	//Prepare mouse values for screenspace
	double mx = (Mouse::_X / (Config::_WINDOWWIDTH / 2)) -1;
	double my = (Mouse::_Y / (Config::_WINDOWHEIGHT / 2)) - 1;


	//check if mouse X and Y inside object.
	std::vector<Component*> cList = pComponent->getOwner()->getComponentsByType("Collision");
	if (cList.size() < 1) return;

	CCollision* c = static_cast<CCollision*>(cList[0]);
	AABB& bb = c->getCollisionBox();
	if (bb.collisionMode())
	{
		//for now no 3d selection code. Todo.
		return;
	}

	glm::vec3 min = bb.getBox()[0];
	glm::vec3 max = bb.getBox()[1];
	if (mx > min[0] && mx < max[0] && my > min[1] && my < max[1])
	{
		pComponent->setHovered(true);
		if (Mouse::_LEFT){
			pComponent->setSelected(true);
		}
	}
	else {
		pComponent->setHovered(false);
		pComponent->setSelected(false);
	}
}

void SCollision::processCollideable(CCollision* pComponent)
{

}
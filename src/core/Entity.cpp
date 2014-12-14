#include "Entity.h"

EventManager Entity::m_EventManager;

Entity::Entity() {
	m_pParent = nullptr;
	m_id.gen();
}

Entity::Entity(const char* name) {
	m_pParent = nullptr;
	m_id.gen(name);
}

Entity::~Entity(){
	m_pParent = nullptr;
}

void Entity::addComponent(Component* component, const char* type) {

	component->setOwner(this);
	component->setType(type);
	component->setName(type);
	m_components.push_back(component);
}

void Entity::removeComponent(Component*) {
}

Component* Entity::getComponent(std::string name) {
	auto it = m_components.begin();
	while ( it != m_components.end() ){
		if ((*it)->getName() == name){
			return (*it);
		}
		++it;
	}

	return nullptr;
}

std::vector<Component*> Entity::getComponentsByType(std::string type) {
	std::vector<Component*> tmpVec;
	auto it = m_components.begin();
	while ( it != m_components.end() ){
		if ((*it)->getType() == type){
			tmpVec.push_back((*it));
		}
		++it;
	}

	return tmpVec;
}

std::string Entity::getId() { 
	return m_id.get();
}

void Entity::setId(std::string id) { 
	m_id.gen(id.c_str());
}

CTransform* Entity::GetTransform() { 
	return &m_transform; 
}

void Entity::SetTransform(CTransform* newTransform){
	if (&m_transform == newTransform || newTransform == nullptr)
		return;
	m_transform = *newTransform; 
}

Entity* Entity::getParent(){
	return m_pParent;
}
void Entity::setParent(Entity* e){
	m_pParent = e;
}

void Entity::removeParent(){
	m_pParent = nullptr;
}
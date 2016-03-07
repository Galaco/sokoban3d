#include "Component.h"
#include "Entity.h"

Component::Component()
{
	m_entity = nullptr;
	m_enabled = true;
	m_name = "";
}

Component::~Component()
{

}

void Component::update(float dt)
{

}

void Component::setEnabled(bool enabled) { 
	m_enabled = enabled; 
}

bool Component::getEnabled() { 
	return m_enabled; 
}

void Component::setType(std::string type) { 
	m_type = type; 
}

const std::string& Component::getType() { 
	return m_type; 
}

Entity* Component::getOwner() { 
	return m_entity; 
}

void Component::setOwner(Entity* entity) { 
	m_entity = entity; 
}

void Component::setName(std::string name){
	m_name = name;
}

std::string Component::getName(){
	return m_name;
}
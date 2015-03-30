/*********************************************************************
Project: Dissertation
Author: Josh Martin

Name: Entity
Description: THE game object. Any object in the world will either be,
			 or inherit from this class. Contains a component list 
			 used to control the object.
*********************************************************************/
#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <string>

#include "EventManager.h"
#include "helpers/Identifier.h"
#include "Component.h"
#include "components/CTransform.h"


class Entity {
public:
	Entity();
    Entity(const char*);
	~Entity();

	void addComponent(Component*, const char*);
	void removeComponent(Component*);

	Component* getComponent(std::string);
	std::vector<Component*> getComponentsByType(std::string);

	std::string getId();
	void setId(std::string id);

	CTransform* GetTransform();
	void SetTransform(CTransform*);

	Entity* getParent();
	void setParent(Entity*);
	void removeParent();

	CTransform m_transform;

protected:
	std::vector<Component*> 	m_components;

    Identifier      m_id;

	std::map<std::string, Component*>::iterator m_mComponentListIterator;

	Entity* m_pParent;

	static EventManager m_EventManager;
};
#endif

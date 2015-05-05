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

	void addComponent(Component*, const char*);	//Add a component to entity storage
	void removeComponent(Component*);	//Remove a component from storage

	Component* getComponent(std::string);	//Get a component from storage
	std::vector<Component*> getComponentsByType(std::string);	//Get a list of components of a given type

	std::string getId();
	void setId(std::string id);

	CTransform* GetTransform();
	void SetTransform(CTransform*);

	Entity* getParent();
	void setParent(Entity*);
	void removeParent();

protected:
	std::vector<Component*> 	m_components;

    Identifier      m_id;


	std::map<std::string, Component*>::iterator m_mComponentListIterator;
	CTransform m_transform;

	Entity* m_pParent;

	static EventManager m_EventManager;
};
#endif

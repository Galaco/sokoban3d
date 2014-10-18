#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <string>

#include "Identifier.h"
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

protected:
	std::vector<Component*> 	m_components;

    Identifier      m_id;


	std::map<std::string, Component*>::iterator m_mComponentListIterator;
	CTransform* m_transform;

	Entity* m_pParent;
};
#endif

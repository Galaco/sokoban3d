/*********************************************************************
Project: Dissertation
Author: Josh Martin

Name: Component
Description: Base component of the component-system architecture.
			 Essentially a entity specific data-store.
*********************************************************************/
#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

#include <core/ResourceManager.h>

class Entity;

class Component {
public:
	Component();
	~Component();

	virtual void update(float);

	void setEnabled(bool enabled);
	bool getEnabled();

	void setType(std::string);
	const std::string& getType();

	Entity* getOwner();
	void setOwner(Entity* entity);

	void setName(std::string);
	std::string getName();

protected:
	bool m_enabled;
	std::string m_type;
	Entity* m_entity;

	std::string m_name;

	ResourceManager m_Resources;
};
#endif

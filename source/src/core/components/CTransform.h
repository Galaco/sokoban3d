/*********************************************************************
Project: Dissertation
Author: Josh Martin

Name: Component Transform
Description: Requirement of all gameobjects. Stores Position, 
			 Orientation, Rotation
*********************************************************************/
#ifndef CTRANSFORM_H
#define CTRANSFORM_H

#include <core/Component.h>

#include <glm/glm.hpp>

class CTransform: public Component {
public:
	CTransform();
	CTransform(glm::vec3 pos, glm::vec3 rot);
	CTransform(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale);
	~CTransform();

	glm::vec3& getPosition();
	glm::vec3& getOldPosition();
	void setPosition(glm::vec3 pos);

	glm::vec3& getOrientation();
	void setOrientation(glm::vec3 pos);

	glm::vec3& getScale();
	void setScale(glm::vec3 pos);

private:
	glm::vec3 m_position;
	glm::vec3 m_orientation;
	glm::vec3 m_scale;

	glm::vec3 m_oldPosition;

};
#endif;

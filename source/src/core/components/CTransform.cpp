#include "CTransform.h"
	
CTransform::CTransform() {
	m_position = glm::vec3(0,0,0); 
	m_orientation = glm::vec3(0,0,0); 
	m_scale = glm::vec3(1,1,1);
}

CTransform::CTransform(glm::vec3 pos, glm::vec3 rot) {
	m_position = pos;
	m_orientation = rot; 
	m_scale = glm::vec3(1,1,1);
}

CTransform::CTransform(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale) {
	m_position = pos;
	m_orientation = rot;
	m_scale = scale;
}

CTransform::~CTransform() {

}

glm::vec3& CTransform::getPosition() { 
	return m_position;
}

glm::vec3& CTransform::getOldPosition() {
	return m_oldPosition;
}


void CTransform::setPosition(glm::vec3 pos) { 
	m_oldPosition = m_position;
	m_position = pos; 
}

glm::vec3& CTransform::getOrientation() { 
	return m_orientation;
}

void CTransform::setOrientation(glm::vec3 pos) { 
	m_orientation = pos; 
}

glm::vec3& CTransform::getScale() { 
	return m_scale;
}

void CTransform::setScale(glm::vec3 pos) { 
	m_scale = pos; 
}

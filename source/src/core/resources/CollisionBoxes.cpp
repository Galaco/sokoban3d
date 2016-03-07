#include "CollisionBoxes.h"

Collision::Collision() {
	m_type = "generic";
}

Collision::~Collision() {

}

void AABB::buildFromModel(Model* model)
{
	/*auto it = model->getMeshes().begin();
	while (it != model->getMeshes().end())
	{
		for (unsigned int i = 0; i < (*it).m_PositionBuffer.size(); i++)
		{

			if ((*it).m_PositionBuffer[i].x < m_minXYZ.x)
			{
				m_minXYZ.x = (*it).m_PositionBuffer[i].x;
			}
			else if ((*it).m_PositionBuffer[i].x > m_maxXYZ.x) {
				m_maxXYZ.x = (*it).m_PositionBuffer[i].x;
			}

			if ((*it).m_PositionBuffer[i].y < m_minXYZ.y)
			{
				m_minXYZ.y = (*it).m_PositionBuffer[i].y;
			}
			else if ((*it).m_PositionBuffer[i].y > m_maxXYZ.y) {
				m_maxXYZ.y = (*it).m_PositionBuffer[i].y;
			}

			if ((*it).m_PositionBuffer[i].z < m_minXYZ.z)
			{
				m_minXYZ.z = (*it).m_PositionBuffer[i].z;
			}
			else if ((*it).m_PositionBuffer[i].z > m_maxXYZ.z) {
				m_maxXYZ.z = (*it).m_PositionBuffer[i].z;
			}


		}


		++it;
	}


	if (m_minXYZ.z == m_maxXYZ.z){
		m_mode = false;	//false equals 2d collision in XY
	}
	else {
		m_mode = true;
	}*/
}


void AABB::resize(glm::vec3 scale, glm::vec3 position)
{
	m_minXYZ.x = (m_minXYZ.x * scale.x)+position.x;
	m_minXYZ.y = (m_minXYZ.y * scale.y)+position.y;
	m_minXYZ.z = (m_minXYZ.z * scale.z)+position.z;
	m_maxXYZ.x = (m_maxXYZ.x * scale.x)+position.x;
	m_maxXYZ.y = (m_maxXYZ.y * scale.y)+position.y;
	m_maxXYZ.z = (m_maxXYZ.z * scale.z)+position.z;
}
#ifndef COLLISIONBOXES_H
#define COLLISIONBOXES_H

#include <string>
#include <vector>
#include <glm/glm.hpp>

#include "Model.h"

class Collision {
public:
	Collision();
	~Collision();



protected:
	std::string m_type;
};



class AABB : public Collision {
public:
	AABB(){ m_mode = true; };
	~AABB(){};
	void build(float minX, float minY, float minZ, float maxX, float maxY, float maxZ)
	{
		m_minXYZ = glm::vec3(minX, minY, minZ);
		m_maxXYZ = glm::vec3(maxX, maxY, maxZ);

		if (minZ == maxZ){
			m_mode = false;	//false equals 2d collision in XY
		}
		else {
			m_mode = true;
		}
	}

	void buildFromModel(Model* model);
	void resize(glm::vec3 scale, glm::vec3 position);


	bool collisionMode() { return m_mode; };

	std::vector<glm::vec3> getBox(){
		std::vector<glm::vec3> tmpVec;
		tmpVec.push_back(m_minXYZ);
		tmpVec.push_back(m_maxXYZ);

		return tmpVec;
	};

protected:
	std::string m_type;
	bool m_mode;

	glm::vec3 m_minXYZ, m_maxXYZ;
};






#endif

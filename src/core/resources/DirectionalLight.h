/*********************************************************************
Project: Dissertation
Author: Josh Martin

Name: Directional Light
Description: A presentation of the sun. Multiple instance at once are
			 very uncommon
*********************************************************************/
#ifndef DIRECTIONALIGHT_H
#define DIRECTIONALIGHT_H

#include <glm/glm.hpp>

class DirectionalLight{
public:
	DirectionalLight();
	~DirectionalLight();

	void setColor(glm::vec3 color){ Color = color; }

	glm::vec3 Color;
	float AmbientIntensity;
	float DiffuseIntensity;
	glm::vec3 Direction;

private:
};
#endif
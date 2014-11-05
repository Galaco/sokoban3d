#ifndef DIRECTIONALIGHT_H
#define DIRECTIONALIGHT_H

#include <core/resources/Model.h>

class DirectionalLight{
public:
	DirectionalLight();
	~DirectionalLight();


	static Model* Quad;
	glm::vec3 Color;
	float AmbientIntensity;
	float DiffuseIntensity;
	glm::vec3 Direction;

	static bool m_meshLoaded;

private:
};
#endif
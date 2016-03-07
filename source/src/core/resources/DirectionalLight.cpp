#include "DirectionalLight.h"


DirectionalLight::DirectionalLight(){
	AmbientIntensity = 0.5f;
	DiffuseIntensity = 0.5f;
	Color = glm::vec3(0.5f);
	Direction = glm::vec3(1.f, 0.f, 0.f);
};

DirectionalLight::~DirectionalLight(){
};
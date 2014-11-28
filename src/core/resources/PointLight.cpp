#include "PointLight.h"

PointLight::PointLight(){
	Color = glm::vec3(1.f, 1.f, 1.f);
	AmbientIntensity = 0.0f;
	DiffuseIntensity = 200.0f;
	Attenuation.Constant = 0.0f;
	Attenuation.Linear = 0.0f;
	Attenuation.Exp = 0.3f;
}

PointLight::~PointLight(){
}

glm::vec3 PointLight::getColor(){ 
	return Color; 
}
float PointLight::getAmbience(){ 
	return AmbientIntensity; 
}
float PointLight::getDiffuse(){ 
	return DiffuseIntensity; 
}
float PointLight::getAttenuationConstant(){ 
	return Attenuation.Constant; 
}
float PointLight::getAttenuationLinear(){ 
	return Attenuation.Linear; 
}
float PointLight::getAttenuationExp(){ 
	return Attenuation.Exp; 
}

void PointLight::setColor(glm::vec3 color){ 
	Color = color; 
}
void PointLight::setAmbience(float a){ 
	AmbientIntensity = a; 
}
void PointLight::setDiffuse(float d){ 
	DiffuseIntensity = d; 
}
void PointLight::setAttenuationConstant(float c){ 
	Attenuation.Constant = c; 
}
void PointLight::setAttenuationLinear(float l){ 
	Attenuation.Linear = l; 
}
void PointLight::setAttenuationExp(float e){ 
	Attenuation.Exp = e; 
}

void PointLight::setPosition(glm::vec3 pos)
{
	Position = pos;
}

glm::vec3 PointLight::getPosition()
{
	return Position;
}
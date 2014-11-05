#include "PointLight.h"

bool PointLight::m_meshLoaded = false;
Model* PointLight::m_mesh = nullptr;

PointLight::PointLight(){
	Color = glm::vec3(0.0f, 0.0f, 0.0f);
	AmbientIntensity = 0.0f;
	DiffuseIntensity = 0.0f;
	Attenuation.Constant = 0.0f;
	Attenuation.Linear = 0.0f;
	Attenuation.Exp = 0.0f;
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

Model* PointLight::getMesh() { 
	return m_mesh; 
}

void PointLight::setMesh(Model* m) {
    m_mesh = m;
    m_meshLoaded = true;
}
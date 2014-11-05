#include "DirectionalLight.h"

Model* DirectionalLight::Quad;
bool DirectionalLight::m_meshLoaded;

DirectionalLight::DirectionalLight(){
	if (Quad != nullptr){
		m_meshLoaded = true;
	} else {
		m_meshLoaded = false;
	}
};

DirectionalLight::~DirectionalLight(){
};
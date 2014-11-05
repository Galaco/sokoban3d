#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include <glm/glm.hpp>

#include "Model.h"

class PointLight {
public:
	PointLight();
	~PointLight();

	glm::vec3 getColor();
	float getAmbience();
	float getDiffuse();
	float getAttenuationConstant();
	float getAttenuationLinear();
	float getAttenuationExp();

	void setColor(glm::vec3 color);
	void setAmbience(float a);
	void setDiffuse(float d);
	void setAttenuationConstant(float c);
	void setAttenuationLinear(float l);
	void setAttenuationExp(float e);

	Model* getMesh();
    void setMesh(Model*);
        
        
    static bool m_meshLoaded;
private:
	glm::vec3 Color;
	float AmbientIntensity;
	float DiffuseIntensity;

	struct
	{
		float Constant;
		float Linear;
		float Exp;
	} Attenuation;

	static Model* m_mesh;
};
#endif

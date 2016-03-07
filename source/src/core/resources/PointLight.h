/*********************************************************************
Project: Dissertation
Author: Josh Martin

Name: Point Light
Description: A light emulation non-directional, non-natural light. Is
			 Color data could be used for any light type, but is 
			 normally used for spheres.
*********************************************************************/
#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include <glm/glm.hpp>
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

	void setPosition(glm::vec3 pos);
	glm::vec3 getPosition();

private:
	glm::vec3 Position;
	glm::vec3 Color;
	float AmbientIntensity;
	float DiffuseIntensity;

	struct
	{
		float Constant;
		float Linear;
		float Exp;
	} Attenuation;
};
#endif

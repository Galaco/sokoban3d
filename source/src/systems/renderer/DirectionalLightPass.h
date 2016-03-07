/*********************************************************************
Project: Dissertation
Author: Josh Martin

Name: Directional Light Pass
Description: Renders the directional light(s?) stored in the current 
			 active state
*********************************************************************/
#ifndef DIRECTIONALLIGHTPASS_H
#define DIRECTIONALLIGHTPASS_H

#include <GL\glew.h>
#include <GL\wglew.h>

#include <core/helpers/Pipeline.h>
#include <core/resources/Mesh.h>
#include <core/resources/DirectionalLight.h>
#include "DeferredPass.h"

class DirectionalLightPass: public DeferredPass{
public:
	DirectionalLightPass();
	~DirectionalLightPass();

	void initialize();
	
	void startPass(DirectionalLight* light);
	void endPass();

private:
	DirectionalLight* Light;

	GLuint m_MVPLocation;
	GLuint m_posTextureUnitLocation;
	GLuint m_normalTextureUnitLocation;
	GLuint m_colorTextureUnitLocation;
	GLuint m_eyeWorldPosLocation;
	GLuint m_matSpecularIntensityLocation;
	GLuint m_matSpecularPowerLocation;
	GLuint m_screenSizeLocation;

	GLuint Color;
	GLuint AmbientIntensity;
	GLuint DiffuseIntensity;
	GLuint Direction;

	float fmax(float a, float b)
	{
		if (a > b)
			return a;
		else
			return b;
	}
};
#endif

/*********************************************************************
Project: Dissertation
Author: Josh Martin

Name: Point Light Pass
Description: Sets up the point light shaders, and render data for all
			 point lights.
*********************************************************************/
#ifndef POINTLIGHTPASS_H
#define POINTLIGHTPASS_H

#include <GL\glew.h>
#include <GL\wglew.h>

#include <core/helpers/Pipeline.h>
#include <core/Entity.h>
#include <core/resources/PointLight.h>

#include "DeferredPass.h"
#include "../../components/CGraphics.h"

class PointLightPass: public DeferredPass{
public:
	PointLightPass();
	~PointLightPass();

	void initialize();
	
	void startPass(CGraphics*, PointLight*);
	void endPass();

private:
	float CalcPointLightBSphere(PointLight* );

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
	GLuint Position;
	struct {
		GLuint Constant;
		GLuint Linear;
		GLuint Exp;
	} Atten;

	float fmax(float a, float b)
	{
		if (a > b)
			return a;
		else
			return b;
	}
};
#endif

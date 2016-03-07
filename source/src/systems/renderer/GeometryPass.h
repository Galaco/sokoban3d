/*********************************************************************
Project: Dissertation
Author: Josh Martin

Name: Geometry Pass
Description: Sets up and renders all geometry data to the screen. 
			 Possibly to be unsued for unlit geometry.
*********************************************************************/
#ifndef GEOMETRYPASS_H
#define GEOMETRYPASS_H

#include <GL\glew.h>
#include <GL\wglew.h>

#include "DeferredPass.h"

#include <core/helpers/Pipeline.h>

class GeometryPass: public DeferredPass{
public:
	GeometryPass();
	~GeometryPass();

	void initialize();
	
	void startPass();
	void endPass();

private:
	GLint m_colorTextureUnitLocation;
};
#endif

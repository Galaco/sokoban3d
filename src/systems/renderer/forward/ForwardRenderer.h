/*********************************************************************
Project: Dissertation
Author: Josh Martin

Name: Geometry Pass
Description: Sets up and renders all geometry data to the screen. 
			 Possibly to be unsued for unlit geometry.
*********************************************************************/
#ifndef FORWARDRENDERER_H
#define FORWARDRENDERER_H

#include <GL\glew.h>
#include <GL\wglew.h>

#include <core/helpers/Pipeline.h>

#include <core/helpers/Config.h>
#include <core/Logger.h>

#include <core/resources/Shader.h>

class ForwardRenderer{
public:
	ForwardRenderer();
	~ForwardRenderer();

	void initialize();
	
	void startPass();
	void endPass();

private:
	Logger*     m_pLogger;

	CShaderProgram	m_shaderProg;
	CShader m_shader[2];

	GLuint m_MVPLocation;
};
#endif

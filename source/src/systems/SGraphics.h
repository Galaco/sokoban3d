/*********************************************************************
Project: Dissertation
Author: Josh Martin

Name: Graphics System
Description: Responsible for rendering all objects to screen. Uses a
			 Deferred Renderer (this could be swapped out for another 
			 rendering method if desired. 
*********************************************************************/
#ifndef SGRAPHICS_H
#define SGRAPHICS_H

#include <map>
#include <vector>

#include <GL\glew.h>
#include <GL\wglew.h>

#include <core/helpers/Config.h>
#include <core/ResourceManager.h>

#include <core/System.h>

#include <core/Camera.h>
#include <core/resources/PointLight.h>
#include <core/resources/Shader.h>

#include <core/helpers/Pipeline.h>


#include "../components/CGraphics.h"

#include "renderer/DeferredRenderer.h"
#include "renderer/GeometryPass.h"
#include "renderer/PointLightPass.h"
#include "renderer/DirectionalLightPass.h"
#include "renderer/StencilPass.h"
#include "renderer/TransparencyPass.h"

class SGraphics: public System{
public:
	SGraphics();
	~SGraphics();

	void initialize();
	void update();

private:
	void drawEntity(CGraphics*);
	void drawText(CGraphics*);
	void drawSkybox();

	void generateShadowBuffer();



	void rebuildCache();

	static ResourceManager m_Resources;
	static std::vector<CGraphics*> CGraphicsCache;
	static CShaderProgram	m_shaderProg;
	static CShader m_shader[3];
	static GLuint shadowFBO, pass1Index, pass2Index;
};
#endif

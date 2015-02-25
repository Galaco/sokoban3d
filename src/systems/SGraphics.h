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

	void drawLight(CGraphics*);
	void drawDirectionalLight();

	void rebuildCache();


    static DeferredRenderer m_deferredRenderer;
	static GeometryPass	m_geometryPass;
    static PointLightPass  m_pointLightPass;
	static DirectionalLightPass m_directionalLightPass;
    static StencilPass     m_stencilPass;
	static TransparencyPass m_transparencyPass;

	static ResourceManager m_Resources;
	static Model*	m_directionalQuad;
	static Model*	m_pointSphere;

	static std::vector<CGraphics*> CGraphicsCache;
};
#endif

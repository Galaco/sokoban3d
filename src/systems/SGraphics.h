#ifndef SGRAPHICS_H
#define SGRAPHICS_H

#include <map>
#include <vector>

#include <GL\glew.h>
#include <GL\wglew.h>

#include <core/Config.h>
#include <core/Logger.h>

#include <core/System.h>

#include <core/Entity.h>
#include <core/Camera.h>
#include "../components/CGraphics.h"
#include <core/resources/PointLight.h>
#include <core/resources/Shader.h>

#include <core/Pipeline.h>

#include "renderer/DeferredRenderer.h"
#include "renderer/GeometryPass.h"
#include "renderer/PointLightPass.h"
#include "renderer/DirectionalLightPass.h"
#include "renderer/StencilPass.h"

class SGraphics: public System{
public:
	SGraphics();
	~SGraphics();

	void initialize();
	void update();

private:
	void drawEntity(CGraphics*);
	void drawLight(CGraphics*);
	void drawSkybox();
	void drawDirectionalLight(const DirectionalLight*);


    static DeferredRenderer m_deferredRenderer;
	static GeometryPass	m_geometryPass;
    static PointLightPass  m_pointLightPass;
	static DirectionalLightPass m_directionalLightPass;
    static StencilPass     m_stencilPass;


        
	Logger* m_pLogger;
};
#endif

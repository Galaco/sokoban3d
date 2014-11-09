#include "CGraphics.h"

CGraphics::CGraphics(){
	m_pModel = nullptr;
	m_pPointlight = nullptr;
	m_type = "Graphics";

	m_renderMode = RENDER_MODE_3D;
}

CGraphics::~CGraphics(){
	if (m_pModel != nullptr) delete m_pModel;
	if (m_pPointlight != nullptr) delete m_pPointlight;
}

void CGraphics::setPointLight(PointLight* light) {
	m_pPointlight = light;
}
	
PointLight* CGraphics::getPointLight() { 
	return m_pPointlight;
}
void CGraphics::addModel(const char* dir) { 
	m_pModel = m_Resources.add<Model>(dir);
}
void CGraphics::addTexture(const char* dir) { 
	if (m_pModel != nullptr){
		m_pModel->addTexture(dir, m_Resources.add<Texture>(dir));
	}
}

void CGraphics::setModel(Model* model) { 
	m_pModel = model;
}

Model* CGraphics::getModel() { 
	if (m_pModel == nullptr) {
		return nullptr;
	}
	return m_pModel; 
}



unsigned int& CGraphics::getRenderMode()
{
	return m_renderMode;
}
void CGraphics::setRenderMode(unsigned int renderMode)
{
	m_renderMode = renderMode;
}
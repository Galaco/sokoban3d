#include "CGraphics.h"

CGraphics::CGraphics()
{
	m_pModel = nullptr;
	m_pPointlight = nullptr;
	m_pText = nullptr;
	m_type = "Graphics";

	m_renderMode = RENDER_MODE_3D;
}

CGraphics::~CGraphics()
{
	if (m_pModel != nullptr) delete m_pModel;
	if (m_pPointlight != nullptr) delete m_pPointlight;
	if (m_pText != nullptr) delete m_pText;
}

void CGraphics::setPointLight(PointLight* light) 
{
	m_pPointlight = light;
}
	
PointLight* CGraphics::getPointLight() { 
	return m_pPointlight;
}

void CGraphics::addModel(const char* dir) 
{ 
	m_pModel = m_Resources.add<Model>(dir);
}

void CGraphics::setModel(Model* model) 
{ 
	m_pModel = model;
}

Model* CGraphics::getModel() 
{ 
	if (m_pModel == nullptr) 
	{
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

Material* CGraphics::getOverrideMaterial(unsigned int index)
{
	if (m_materialList.size() > index) 
	{
		return &m_materialList[index];
	}
	else {
		return nullptr;
	}
}

void CGraphics::addText(const char* string, double size)
{
	m_pText = new Text(string, size);

	m_pText->texture = m_Resources.add<Texture>("vgui/fonts/default.png");
}

void CGraphics::setText(Text* text)
{
	m_pText = text;
}

Text* CGraphics::getText()
{
	return m_pText;
}

void CGraphics::addMaterial(const char* filename)
{
	Material m;
	m.load(filename);
	m_materialList.push_back(m);
}
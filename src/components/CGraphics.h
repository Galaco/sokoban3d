/*********************************************************************
Project: Dissertation
Author: Josh Martin

Name: Component Graphics
Description: Stores renderable data for use with the render system
*********************************************************************/
#ifndef CGRAPHICS_H
#define CGRAPHICS_H

#define RENDER_MODE_2D 0
#define RENDER_MODE_3D 1


#include <core/Component.h>
#include <core/resources/Model.h>
#include <core/resources/PointLight.h>
#include <core/resources/Texture.h>

class CGraphics: public Component {
public:
	CGraphics();
	~CGraphics();

	void setPointLight(PointLight* light);
	PointLight* getPointLight();
	void addModel(const char*);
	void addTexture(const char*);
	void setModel(Model*);
	Model* getModel();

	Texture* getOverrideTexture(unsigned int);

	unsigned int& getRenderMode();
	void setRenderMode(unsigned int);
private:
	Model* m_pModel;
	PointLight* m_pPointlight;
	std::vector<Texture*> m_pOverrideTextures;

	unsigned int m_renderMode;
};
#endif
#ifndef GEOMETRYPASS_H
#define GEOMETRYPASS_H

#include <GL\glew.h>
#include <GL\wglew.h>

#include "DeferredPass.h"

#include <core/Pipeline.h>

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

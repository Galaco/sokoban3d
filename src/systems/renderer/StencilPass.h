#ifndef STENCILPASS_H
#define STENCILPASS_H

#include <GL\glew.h>
#include <GL\wglew.h>

#include <core/Pipeline.h>
#include <core/Entity.h>
#include <core/resources/PointLight.h>

#include "DeferredPass.h"

#include "../../components/CGraphics.h"


class StencilPass: public DeferredPass{
public:
	StencilPass();
	~StencilPass();

	void initialize();
	
	void startPass(CGraphics*, PointLight*);
	void endPass();

private:
	float CalcPointLightBSphere(PointLight* );

	float fmax(float a, float b)
	{
		if (a > b)
			return a;
		else
			return b;
	}
};
#endif

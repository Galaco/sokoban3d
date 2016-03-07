/*********************************************************************
Project: Dissertation
Author: Josh Martin

Name: Deferred Renderer
Description: Responsible for setting up and handling the display each
			 frame.
*********************************************************************/
#ifndef DEFERREDRENDERER_H
#define DEFERREDRENDERER_H

#include <GL\glew.h>
#include <GL\wglew.h>

#include <core/helpers/Config.h>
#include <core/Logger.h>

#include <core/resources/Shader.h>


class DeferredRenderer{
public:
	DeferredRenderer();
	~DeferredRenderer();

	void initialize();
	
	void startFrame();
	void endFrame();
	void endFrameDebug();

	GLuint& getFbo();
        
        void bindBufferTextures();

private:
	Logger*     m_pLogger;
    
    
	GLuint  m_fbo, gbuffer_tex[4];
	GLuint m_depthTexture;
	GLuint m_finalTexture;
};
#endif

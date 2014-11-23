#include "DeferredRenderer.h"

DeferredRenderer::DeferredRenderer(){
}

DeferredRenderer::~DeferredRenderer(){
}

void DeferredRenderer::initialize(){
	glGenFramebuffers(1, &m_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

	glGenTextures(4, gbuffer_tex);
	glGenTextures(1, &m_depthTexture);
	glGenTextures(1, &m_finalTexture);

	for(unsigned int i=0; i<4; ++i){
		glBindTexture(GL_TEXTURE_2D, gbuffer_tex[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, Config::_WINDOWWIDTH, Config::_WINDOWHEIGHT, 0, GL_RGB, GL_FLOAT, NULL); 
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, gbuffer_tex[i], 0);
	}

	//depth
	glBindTexture(GL_TEXTURE_2D, m_depthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH32F_STENCIL8, Config::_WINDOWWIDTH, Config::_WINDOWHEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_depthTexture, 0);
	//final
	glBindTexture(GL_TEXTURE_2D, m_finalTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Config::_WINDOWWIDTH, Config::_WINDOWHEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT4, GL_TEXTURE_2D, m_finalTexture, 0);	

	GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (Status != GL_FRAMEBUFFER_COMPLETE) {
		std::string status = "FrameBuffer error, status code: 0x%x\n: " + std::to_string(static_cast<float>(Status));
		m_pLogger->log(FATAL, status.c_str() );
	}
	// restore default FBO
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

void DeferredRenderer::startFrame(){
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);
	glDrawBuffer(GL_COLOR_ATTACHMENT4);
	glClear(GL_COLOR_BUFFER_BIT);
}

void DeferredRenderer::endFrame(){
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, m_fbo);
	glReadBuffer(GL_COLOR_ATTACHMENT4);

	glBlitFramebuffer(0, 0, Config::_WINDOWWIDTH, Config::_WINDOWHEIGHT,
	0, 0, Config::_WINDOWWIDTH, Config::_WINDOWHEIGHT, GL_COLOR_BUFFER_BIT, GL_LINEAR);
}

void DeferredRenderer::endFrameDebug(){
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindFramebuffer(GL_READ_FRAMEBUFFER, m_fbo);

	GLint HalfWidth = (GLint)(Config::_WINDOWWIDTH / 2.0f);
	GLint HalfHeight = (GLint)(Config::_WINDOWHEIGHT / 2.0f);

	glReadBuffer(GL_COLOR_ATTACHMENT0 + 0);
	glBlitFramebuffer(0, 0, Config::_WINDOWWIDTH, Config::_WINDOWHEIGHT, 0, 0, HalfWidth, HalfHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);

	glReadBuffer(GL_COLOR_ATTACHMENT0 + 1);
	glBlitFramebuffer(0, 0, Config::_WINDOWWIDTH, Config::_WINDOWHEIGHT, 0, HalfHeight, HalfWidth, Config::_WINDOWHEIGHT, GL_COLOR_BUFFER_BIT, GL_LINEAR);

	glReadBuffer(GL_COLOR_ATTACHMENT0 + 2);
	glBlitFramebuffer(0, 0, Config::_WINDOWWIDTH, Config::_WINDOWHEIGHT, HalfWidth, HalfHeight, Config::_WINDOWWIDTH, Config::_WINDOWHEIGHT, GL_COLOR_BUFFER_BIT, GL_LINEAR);

	glReadBuffer(GL_COLOR_ATTACHMENT0 + 3);
	glBlitFramebuffer(0, 0, Config::_WINDOWWIDTH, Config::_WINDOWHEIGHT, HalfWidth, 0, Config::_WINDOWWIDTH, HalfHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);
}

GLuint& DeferredRenderer::getFbo(){
	return m_fbo;
}

void DeferredRenderer::bindBufferTextures(){
	for (unsigned int i = 0 ; i < 4; i++) {
		glActiveTexture(GL_TEXTURE0 + i);		
		glBindTexture(GL_TEXTURE_2D, gbuffer_tex[0 + i]);
	}
}
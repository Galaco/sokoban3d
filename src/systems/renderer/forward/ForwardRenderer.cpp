#include "ForwardRenderer.h"

ForwardRenderer::ForwardRenderer(){
}

ForwardRenderer::~ForwardRenderer(){
	m_shaderProg.deleteProgram();
	m_shader[0].deleteShader();
	m_shader[1].deleteShader();
}

void ForwardRenderer::initialize(){
	bool vsLoad = m_shader[0].loadShader("binaries/shaders/forward/main.vs.glsl", GL_VERTEX_SHADER);
	bool fsLoad = m_shader[1].loadShader("binaries/shaders/forward/main.fs.glsl", GL_FRAGMENT_SHADER);

	if (!vsLoad || !fsLoad) 
		m_pLogger->log(FATAL, "Could not load core forward shader/s.");

	m_shaderProg.createProgram();
	m_shaderProg.addShaderToProgram(&m_shader[0]);
	m_shaderProg.addShaderToProgram(&m_shader[1]);
	m_shaderProg.linkProgram();

	m_shaderProg.useProgram();
}

void ForwardRenderer::startPass() {
	m_shaderProg.useProgram();

	glUniformMatrix4fv(Pipeline::m_VPMatrix, 1, GL_TRUE, &Pipeline::getWorldMatrix()[0][0]);
}

void ForwardRenderer::endPass(){
}
#include "TransparencyPass.h"

TransparencyPass::TransparencyPass(){
}
TransparencyPass::~TransparencyPass(){
	m_shaderProg.deleteProgram();
	m_shader[0].deleteShader();
	m_shader[1].deleteShader();
}

void TransparencyPass::initialize(){
	bool vsLoad = m_shader[0].loadShader("binaries/shaders/deferred/transparency.vs.glsl", GL_VERTEX_SHADER);
	bool fsLoad = m_shader[1].loadShader("binaries/shaders/deferred/transparency.fs.glsl", GL_FRAGMENT_SHADER);

	if (!vsLoad || !fsLoad) m_pLogger->log(FATAL, "Could not load transparency shader/s.");

	m_shaderProg.createProgram();
	m_shaderProg.addShaderToProgram(&m_shader[0]);
	m_shaderProg.addShaderToProgram(&m_shader[1]);
	m_shaderProg.linkProgram();


	m_MVPLocation = glGetUniformLocation(m_shaderProg.getProgramID(), "MVP");

	if (m_MVPLocation == 0xFFFFFFFF ) {    
			m_pLogger->log(FATAL, "Transparency shader could not be correctly Initialised.");
	}
}

void TransparencyPass::startPass() {
	m_shaderProg.useProgram();
	glEnable(GL_BLEND);
}

void TransparencyPass::endPass(){
	glDisable(GL_BLEND);
}

void TransparencyPass::setTransformation(const glm::mat4 mat){
	glUniformMatrix4fv(m_MVPLocation, 1, GL_FALSE, &mat[0][0]);
}
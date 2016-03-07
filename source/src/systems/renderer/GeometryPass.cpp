#include "GeometryPass.h"

#include "DeferredShaders.h"

GeometryPass::GeometryPass(){
}

GeometryPass::~GeometryPass(){
	m_shaderProg.deleteProgram();
	m_shader[0].deleteShader();
	m_shader[1].deleteShader();
}

void GeometryPass::initialize(){
	bool vsLoad = m_shader[0].loadShader("binaries/shaders/deferred/geometry_pass.vs.glsl", GL_VERTEX_SHADER);
	bool fsLoad = m_shader[1].loadShader("binaries/shaders/deferred/geometry_pass.fs.glsl", GL_FRAGMENT_SHADER);
	//bool fsLoad = m_shader[1].loadFromString(spire::deferred::geometryFrag, spire::deferred::geometryFragLines, GL_FRAGMENT_SHADER);

	if (!vsLoad || !fsLoad) 
		m_pLogger->log(FATAL, "Could not load core geometry shader/s.");

	m_shaderProg.createProgram();
	m_shaderProg.addShaderToProgram(&m_shader[0]);
	m_shaderProg.addShaderToProgram(&m_shader[1]);
	m_shaderProg.linkProgram();

	Pipeline::m_MVPMatrix = glGetUniformLocation(m_shaderProg.getProgramID(), "MVP");
	Pipeline::m_VPMatrix = glGetUniformLocation(m_shaderProg.getProgramID(), "VP");
	m_colorTextureUnitLocation = glGetUniformLocation(m_shaderProg.getProgramID(), "gColorMap");

	m_shaderProg.useProgram();
	glUniform1i(m_colorTextureUnitLocation, 0);

	if (Pipeline::m_MVPMatrix == 0xFFFFFFFF ||
		Pipeline::m_VPMatrix == 0xFFFFFFFF ||
		m_colorTextureUnitLocation == 0xFFFFFFFF) {
			m_pLogger->log(FATAL, "Geometry Shader could not be correctly initialised.");
	}
}

void GeometryPass::startPass() {
	m_shaderProg.useProgram();
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);
	GLenum DrawBuffers[] = { 
		GL_COLOR_ATTACHMENT0, 
		GL_COLOR_ATTACHMENT1,
		GL_COLOR_ATTACHMENT2 };
	glDrawBuffers(3, DrawBuffers);

	glDepthMask(GL_TRUE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);


	glDisable(GL_CULL_FACE);
	// 
	// Render to the stencil buffer
	glEnable(GL_STENCIL_TEST);
	glStencilFunc( GL_ALWAYS, 1, 1 );
	glStencilOp( GL_REPLACE, GL_REPLACE, GL_REPLACE );



	glUniformMatrix4fv(Pipeline::m_VPMatrix, 1, GL_TRUE, &Pipeline::getWorldMatrix()[0][0]);

	//fix inverted faces
	glFrontFace(GL_CW);
}

void GeometryPass::endPass(){
	glDepthMask(GL_FALSE);


	glFrontFace(GL_CCW);
	//glDisable(GL_STENCIL_TEST);


	// Turn back on color buffer
	glColorMask( GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE );

	//Where a 1 was not rendered
	glStencilFunc( GL_NOTEQUAL, 1, 1 );

	//Keep the pixel
	glStencilOp( GL_KEEP, GL_KEEP, GL_KEEP );
}
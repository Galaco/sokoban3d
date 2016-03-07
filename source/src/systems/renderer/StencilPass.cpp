#include "StencilPass.h"

StencilPass::StencilPass(){
}
StencilPass::~StencilPass(){
	m_shaderProg.deleteProgram();
	m_shader[0].deleteShader();
	m_shader[1].deleteShader();
}

void StencilPass::initialize(){
	bool vsLoad = m_shader[0].loadShader("binaries/shaders/deferred/stencil.vs.glsl", GL_VERTEX_SHADER);
	bool fsLoad = m_shader[1].loadShader("binaries/shaders/deferred/stencil.fs.glsl", GL_FRAGMENT_SHADER);

	if (!vsLoad || !fsLoad) m_pLogger->log(FATAL, "Could not load stencil shader/s.");

	m_shaderProg.createProgram();
	m_shaderProg.addShaderToProgram(&m_shader[0]);
	m_shaderProg.addShaderToProgram(&m_shader[1]);
	m_shaderProg.linkProgram();


	m_MVPLocation = glGetUniformLocation(m_shaderProg.getProgramID(), "MVP");

	if (m_MVPLocation == 0xFFFFFFFF ) {    
			m_pLogger->log(FATAL, "Stencil shader could not be correctly Initialised.");
	}
}

void StencilPass::startPass(CGraphics* it, PointLight* Light) {
	m_shaderProg.useProgram();

	// Disable color/depth write and enable stencil
	glEnable(GL_DEPTH_TEST);

	glDisable(GL_CULL_FACE);

	glClear(GL_STENCIL_BUFFER_BIT);
	// We need the stencil test to be enabled but we want it
	// to succeed always. Only the depth test matters.
	glStencilFunc(GL_ALWAYS, 0, 0);

	glStencilOpSeparate(GL_BACK, GL_KEEP, GL_INCR_WRAP, GL_KEEP);
	glStencilOpSeparate(GL_FRONT, GL_KEEP, GL_DECR_WRAP, GL_KEEP);

	Pipeline::position(it->getOwner()->GetTransform()->getPosition().x, it->getOwner()->GetTransform()->getPosition().y, it->getOwner()->GetTransform()->getPosition().z);
	float BSphereScale = CalcPointLightBSphere(Light);
	Pipeline::scale(BSphereScale, BSphereScale, BSphereScale);	

	glUniformMatrix4fv(m_MVPLocation, 1, GL_FALSE, &Pipeline::getTransformationMatrix()[0][0]);
}

void StencilPass::endPass(){
}

float StencilPass::CalcPointLightBSphere(PointLight* Light)
{
	float MaxChannel = fmax(fmax(Light->getColor().x, Light->getColor().y), Light->getColor().z);

	float ret = (-Light->getAttenuationLinear() + sqrtf(Light->getAttenuationLinear() * Light->getAttenuationLinear() - 4 * Light->getAttenuationExp() * (Light->getAttenuationExp() - 256 * MaxChannel * Light->getDiffuse()))) 
		/
		2 * Light->getAttenuationExp();

	return ret;
}

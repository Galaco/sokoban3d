#include "PointLightPass.h"

PointLightPass::PointLightPass(){
}

PointLightPass::~PointLightPass(){
	m_shaderProg.deleteProgram();
	m_shader[0].deleteShader();
	m_shader[1].deleteShader();
}

void PointLightPass::initialize(){
	bool vsLoad = m_shader[0].loadShader("binaries/shaders/deferred/point_light_pass.vs.glsl", GL_VERTEX_SHADER);
	bool fsLoad = m_shader[1].loadShader("binaries/shaders/deferred/point_light_pass.fs.glsl", GL_FRAGMENT_SHADER);

	if (!vsLoad || !fsLoad) m_pLogger->log(FATAL, "Could not load point light shader/s.");

	m_shaderProg.createProgram();
	m_shaderProg.addShaderToProgram(&m_shader[0]);
	m_shaderProg.addShaderToProgram(&m_shader[1]);
	m_shaderProg.linkProgram();

	m_MVPLocation = glGetUniformLocation(m_shaderProg.getProgramID(), "MVP");
	m_posTextureUnitLocation = glGetUniformLocation(m_shaderProg.getProgramID(), "gPositionMap");
	m_colorTextureUnitLocation = glGetUniformLocation(m_shaderProg.getProgramID(), "gColorMap");
	m_normalTextureUnitLocation = glGetUniformLocation(m_shaderProg.getProgramID(), "gNormalMap");
	m_eyeWorldPosLocation = glGetUniformLocation(m_shaderProg.getProgramID(), "gEyeWorldPos");
	m_matSpecularIntensityLocation = glGetUniformLocation(m_shaderProg.getProgramID(), "gMatSpecularIntensity");
	m_matSpecularPowerLocation = glGetUniformLocation(m_shaderProg.getProgramID(), "gSpecularPower");
	m_screenSizeLocation = glGetUniformLocation(m_shaderProg.getProgramID(), "gScreenSize");

	Color = glGetUniformLocation(m_shaderProg.getProgramID(), "gPointLight.Base.Color");
	AmbientIntensity = glGetUniformLocation(m_shaderProg.getProgramID(), "gPointLight.Base.AmbientIntensity");
	Position = glGetUniformLocation(m_shaderProg.getProgramID(), "gPointLight.Position");
	DiffuseIntensity = glGetUniformLocation(m_shaderProg.getProgramID(), "gPointLight.Base.DiffuseIntensity");
	Atten.Constant = glGetUniformLocation(m_shaderProg.getProgramID(), "gPointLight.Atten.Constant");
	Atten.Linear = glGetUniformLocation(m_shaderProg.getProgramID(), "gPointLight.Atten.Linear");
	Atten.Exp = glGetUniformLocation(m_shaderProg.getProgramID(), "gPointLight.Atten.Exp");	

	if (m_MVPLocation == 0xFFFFFFFF ||
		m_posTextureUnitLocation == 0xFFFFFFFF ||
		m_colorTextureUnitLocation == 0xFFFFFFFF ||
		m_normalTextureUnitLocation == 0xFFFFFFFF ||
		m_eyeWorldPosLocation == 0xFFFFFFFF ||
		m_matSpecularIntensityLocation == 0xFFFFFFFF ||
		m_matSpecularPowerLocation == 0xFFFFFFFF ||
		m_screenSizeLocation == 0xFFFFFFFF ||
		Color == 0xFFFFFFFF ||
		AmbientIntensity == 0xFFFFFFFF ||
		Position == 0xFFFFFFFF ||
		DiffuseIntensity == 0xFFFFFFFF ||
		Atten.Constant == 0xFFFFFFFF ||
		Atten.Linear == 0xFFFFFFFF ||
		Atten.Exp == 0xFFFFFFFF) {    
			m_pLogger->log(FATAL, "Point Light shader could not be correctly Initialised.");
	}

	m_shaderProg.useProgram();
	glUniform1i(m_posTextureUnitLocation, 0);
	glUniform1i(m_colorTextureUnitLocation, 1);
	glUniform1i(m_normalTextureUnitLocation, 2);
	glUniform2f(m_screenSizeLocation, (float)Config::_WINDOWWIDTH, (float)Config::_WINDOWHEIGHT);
}

void PointLightPass::startPass(CGraphics* it, PointLight* Light) {
	m_shaderProg.useProgram();
	glUniform3f(m_eyeWorldPosLocation, Pipeline::Eye.x, Pipeline::Eye.y, Pipeline::Eye.z);   

	glStencilFunc(GL_EQUAL,1, 0xFF);

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_ONE, GL_ONE);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);

	Pipeline::position(it->getOwner()->GetTransform()->getPosition().x, it->getOwner()->GetTransform()->getPosition().y, it->getOwner()->GetTransform()->getPosition().z);
	float BSphereScale = CalcPointLightBSphere(Light);
	Pipeline::scale(BSphereScale, BSphereScale, BSphereScale);
	glUniformMatrix4fv(m_MVPLocation, 1, GL_FALSE, &Pipeline::getTransformationMatrix()[0][0]);

	glUniform3f(Color, Light->getColor().x, Light->getColor().y, Light->getColor().z);
	glUniform1f(AmbientIntensity, Light->getAmbience());
	glUniform1f(DiffuseIntensity, Light->getDiffuse());
	glUniform3f(Position, it->getOwner()->GetTransform()->getPosition().x, it->getOwner()->GetTransform()->getPosition().y, it->getOwner()->GetTransform()->getPosition().z);
	glUniform1f(Atten.Constant, Light->getAttenuationConstant());
	glUniform1f(Atten.Linear, Light->getAttenuationLinear());
	glUniform1f(Atten.Exp, Light->getAttenuationExp());	
}

void PointLightPass::endPass(){
	glCullFace(GL_BACK);

	glDisable(GL_BLEND);
}



float PointLightPass::CalcPointLightBSphere(PointLight* Light)
{
	float MaxChannel = fmax(fmax(Light->getColor().x, Light->getColor().y), Light->getColor().z);

	float ret = (-Light->getAttenuationLinear() + sqrtf(Light->getAttenuationLinear() * Light->getAttenuationLinear() - 4 * Light->getAttenuationExp() * (Light->getAttenuationExp() - 256 * MaxChannel * Light->getDiffuse()))) 
		/
		2 * Light->getAttenuationExp();

	return ret;
}

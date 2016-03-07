#include "DirectionalLightPass.h"

DirectionalLightPass::DirectionalLightPass(){
	Light = new DirectionalLight;
}

DirectionalLightPass::~DirectionalLightPass(){
	m_shaderProg.deleteProgram();
	m_shader[0].deleteShader();
	m_shader[1].deleteShader();
}

void DirectionalLightPass::initialize(){
	bool vsLoad = m_shader[0].loadShader("binaries/shaders/deferred/directional_light_pass.vs.glsl", GL_VERTEX_SHADER);
	bool fsLoad = m_shader[1].loadShader("binaries/shaders/deferred/directional_light_pass.fs.glsl", GL_FRAGMENT_SHADER);

	if (!vsLoad || !fsLoad) m_pLogger->log(FATAL, "Could not load directional light shader/s.");

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

	Color = glGetUniformLocation(m_shaderProg.getProgramID(), "gDirectionalLight.Base.Color");
	AmbientIntensity = glGetUniformLocation(m_shaderProg.getProgramID(), "gDirectionalLight.Base.AmbientIntensity");
	Direction = glGetUniformLocation(m_shaderProg.getProgramID(), "gDirectionalLight.Direction");
	DiffuseIntensity = glGetUniformLocation(m_shaderProg.getProgramID(), "gDirectionalLight.Base.DiffuseIntensity");

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
		Direction == 0xFFFFFFFF ||
		DiffuseIntensity == 0xFFFFFFFF) {    
			m_pLogger->log(FATAL, "Directional Light shader could not be correctly Initialised.");
	}

	m_shaderProg.useProgram();
	glUniform1i(m_posTextureUnitLocation, 0);
	glUniform1i(m_colorTextureUnitLocation, 1);
	glUniform1i(m_normalTextureUnitLocation, 2);
	glUniform2f(m_screenSizeLocation, (float)Config::_WINDOWWIDTH, (float)Config::_WINDOWHEIGHT);
}

void DirectionalLightPass::startPass(DirectionalLight* light) {
	m_shaderProg.useProgram();
	glUniform3f(m_eyeWorldPosLocation, Pipeline::Eye.x, Pipeline::Eye.y, Pipeline::Eye.z);
	glUniformMatrix4fv(m_MVPLocation, 1, GL_TRUE, &glm::mat4(1.0)[0][0]);

	glUniform3f(Color, light->Color.x, light->Color.y, light->Color.z);
	glUniform1f(AmbientIntensity, light->AmbientIntensity);
	glm::vec3 dir = glm::normalize(light->Direction);
	glUniform3f(Direction, dir.x, dir.y, dir.z);
	glUniform1f(DiffuseIntensity, light->DiffuseIntensity);

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_ONE, GL_ONE);	
}

void DirectionalLightPass::endPass(){
	glDisable(GL_BLEND);
}
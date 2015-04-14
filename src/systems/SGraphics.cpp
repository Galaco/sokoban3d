#include "SGraphics.h"


//Initialize statics. Note these aren't required to be static, but for clarity are
std::vector<CGraphics*> SGraphics::CGraphicsCache;

CShaderProgram	SGraphics::m_shaderProg;
CShader SGraphics::m_shader[3];
GLuint SGraphics::shadowFBO;
GLuint SGraphics::pass1Index;
GLuint SGraphics::pass2Index;

SGraphics::SGraphics(){
	m_PreviousState = nullptr;
}

SGraphics::~SGraphics(){
}

void SGraphics::initialize(){
	//Initialize the renderer
	bool vsLoad = m_shader[0].loadShader("binaries/shaders/shader.vert", GL_VERTEX_SHADER);
	bool fsLoad = m_shader[1].loadShader("binaries/shaders/shader.frag", GL_FRAGMENT_SHADER);
	bool gsLoad = m_shader[2].loadShader("binaries/shaders/shader.geom", GL_GEOMETRY_SHADER);

	if (!vsLoad || !fsLoad || !gsLoad)
		Logger::log(FATAL, "Could not load core shader/s.");

	m_shaderProg.createProgram();
	m_shaderProg.addShaderToProgram(&m_shader[0]);
	m_shaderProg.addShaderToProgram(&m_shader[1]);
	//m_shaderProg.addShaderToProgram(&m_shader[2]);
	m_shaderProg.linkProgram();


	pass1Index = glGetSubroutineIndex(m_shaderProg.getProgramID(), GL_FRAGMENT_SHADER, "recordDepth");
	pass2Index = glGetSubroutineIndex(m_shaderProg.getProgramID(), GL_FRAGMENT_SHADER, "finalPass");
	generateShadowBuffer();


	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LEQUAL);
	glCullFace(GL_FRONT);
	glEnable(GL_DEPTH_TEST);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	Pipeline::m_ShadowVP = glm::mat4(
		glm::vec4(0.5f, 0.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, 0.5f, 0.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 0.5f, 0.0f),
		glm::vec4(0.5f, 0.5f, 0.5f, 1.0f)
		)
		* Pipeline::m_projection
		* glm::lookAt(glm::vec3(100, 100, 100), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
}

void SGraphics::generateShadowBuffer()
{

	// The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
	GLuint FramebufferName = 0;
	glGenFramebuffers(1, &FramebufferName);
	glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);

	// Depth texture. Slower than a depth buffer, but you can sample it later in your shader
	GLuint depthTexture;
	glGenTextures(1, &depthTexture);
	glBindTexture(GL_TEXTURE_2D, depthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, 1024, 1024, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTexture, 0);

	glDrawBuffer(GL_NONE); // No color buffer is drawn to.

	// Always check that our framebuffer is ok
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		Logger::log(FATAL, "Renderer: Failed to successfully generate Framebuffer");

	m_shaderProg.setUniform("ShadowMap", 0);
}
	
void SGraphics::update(){
	if ((m_CurrentState != m_PreviousState) || Scene::ForceRecache)
	{
		rebuildCache();
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	
	m_shaderProg.useProgram();
	m_shaderProg.setUniform("EyePosition", Pipeline::Eye);
	m_shaderProg.setUniform("SpecularExponent", 32.f);
	m_shaderProg.setUniform("parallaxScaleBias", glm::vec2(0.04, 0.02));

	//Temp
	DirectionalLight light = m_CurrentState->getDirectionalLight();
	m_shaderProg.setUniform("LightPosition", glm::vec3(0.0f, 100.0f, 0.0f));
	m_shaderProg.setUniform("Light.AmbientColor", light.Color);
	m_shaderProg.setUniform("Light.AmbientIntensity", light.AmbientIntensity);
	m_shaderProg.setUniform("Light.DiffuseIntensity", glm::vec3(0.8f, 0.8f, 0.8f));
	m_shaderProg.setUniform("Light.Position", glm::vec4(0.0f, 10.0f, 0.0f, 1.0));
	m_shaderProg.setUniform("Light.SpecularColor", 1.0, 1.0, 1.0);
	m_shaderProg.setUniform("Light.Ls", glm::vec3(0.9f, 0.9f, 0.9f));

	
	/*glCullFace(GL_FRONT);
	glBindFramebuffer(GL_FRAMEBUFFER, shadowFBO);
	glClear(GL_DEPTH_BUFFER_BIT);
	//glViewport(0, 0, Config::_WINDOWHEIGHT, Config::_WINDOWHEIGHT);
	glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &pass1Index);
	glm::mat4 camView = Pipeline::m_view;
	Pipeline::setViewMatrix(glm::lookAt(glm::vec3(0, 10, 0), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)));
	//Render components
	auto it = CGraphicsCache.begin();
	while (it != CGraphicsCache.end())
	{
		if ((*it)->getText())
		{
			drawText((*it));
		}
		else {
			drawEntity((*it));
		}
		++it;
	}

	Pipeline::setViewMatrix(camView);

	glFlush();
	glFinish();


	glCullFace(GL_BACK);*/
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glViewport(0, 0, Config::_WINDOWHEIGHT, Config::_WINDOWHEIGHT);
	glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &pass2Index);
	auto it = CGraphicsCache.begin();
	while (it != CGraphicsCache.end())
	{
		if ((*it)->getText())
		{
			drawText((*it));
		}
		else {
			drawEntity((*it));
		}
		++it;
	}
	drawSkybox();
}

void SGraphics::drawEntity(CGraphics* it)
{
	if (!it->getModel() || !it->getOwner())
		return;

	Pipeline::position(it->getOwner()->GetTransform()->getPosition().x, it->getOwner()->GetTransform()->getPosition().y, it->getOwner()->GetTransform()->getPosition().z);
	Pipeline::rotate(it->getOwner()->GetTransform()->getOrientation().x, it->getOwner()->GetTransform()->getOrientation().y, it->getOwner()->GetTransform()->getOrientation().z);
	Pipeline::scale(it->getOwner()->GetTransform()->getScale().x, it->getOwner()->GetTransform()->getScale().y, it->getOwner()->GetTransform()->getScale().z);

	switch(it->getRenderMode())
	{
	case RENDER_MODE_2D:
		m_shaderProg.setUniform("MVP", Pipeline::getTransformationMatrix2D());
		m_shaderProg.setUniform("V", glm::mat4(1.0));
		m_shaderProg.setUniform("P", glm::mat4(1.0));
		m_shaderProg.setUniform("FullBright", 1);
		break;
	case RENDER_MODE_3D:
		m_shaderProg.setUniform("MVP", Pipeline::getTransformationMatrix());
		m_shaderProg.setUniform("V", Pipeline::m_view);
		m_shaderProg.setUniform("P", Pipeline::m_projection);
		m_shaderProg.setUniform("FullBright", 0);
		break;
	}

	m_shaderProg.setUniform("ModelViewMatrix", Pipeline::m_view * Pipeline::m_model);
	m_shaderProg.setUniform("NormalMatrix", glm::mat3(glm::transpose(glm::inverse(Pipeline::m_model))));
	m_shaderProg.setUniform("M", Pipeline::m_model);
	m_shaderProg.setUniform("Translucent", 0);

	m_shaderProg.setUniform("ShadowMatrix", Pipeline::m_ShadowVP * Pipeline::m_model);

	// Render the meshes
	std::vector<Mesh>& m = it->getModel()->getMeshes();
	glBindVertexArray(m[0].m_VAO);

	Material* mat = it->getOverrideMaterial(0);
	if (mat)
	{
		//DIFFUSE Texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mat->texId(Material::TextureType::DIFFUSE));
		m_shaderProg.setUniform("textureDiffuse", 0);

		//NORMAL Texture
		GLuint t = mat->texId(Material::TextureType::NORMAL);
		if (t != 0)
		{
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, t);
			m_shaderProg.setUniform("textureNormal", 1);
		}

		m_shaderProg.setUniform("FullBright", mat->fullbright);
		m_shaderProg.setUniform("Translucent", mat->translucent);
		if (mat->translucent)
		{
			glEnable(GL_BLEND);
		}
	}
	else {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, *m[0].m_texID);
		m_shaderProg.setUniform("textureDiffuse", 0);
		m_shaderProg.setUniform("textureNormal", 1);
	}
	for (unsigned int i = 0; i < m[i].m_Entries.size(); i++)
	{
		glDrawElementsBaseVertex(GL_TRIANGLES,
			m.at(i).m_Entries.at(i).NumIndices,
			GL_UNSIGNED_INT,
			(void*)(sizeof(unsigned int) * m.at(i).m_Entries.at(i).BaseIndex),
			m.at(i).m_Entries.at(i).BaseVertex);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	
	glBindVertexArray(0);
	if (mat)
	{
		if (mat->translucent)
		{
			glDisable(GL_BLEND);
		}
	}
}

void SGraphics::drawSkybox()
{
	if (!m_CurrentState || !m_CurrentState->getCurrentCamera()) {
		return;
	}
	Skybox sky = m_CurrentState->getCurrentCamera()->getSkybox();
	if (sky.getVao() == -1) return;
	sky.useProgram();

	glBindVertexArray(sky.getVao()); 

	glEnable(GL_TEXTURE_2D);

	glActiveTexture(GL_TEXTURE0);
	sky.bindTexture();
	glDrawArrays(GL_TRIANGLES, 0, 36);

	glBindVertexArray(0);
}

void SGraphics::drawText(CGraphics* it)
{
	Text* t = it->getText();
	if (!t) 
		return;

	Pipeline::position(it->getOwner()->GetTransform()->getPosition().x, it->getOwner()->GetTransform()->getPosition().y, it->getOwner()->GetTransform()->getPosition().z);
	Pipeline::rotate(it->getOwner()->GetTransform()->getOrientation().x, it->getOwner()->GetTransform()->getOrientation().y, it->getOwner()->GetTransform()->getOrientation().z);

	switch (it->getRenderMode())
	{
	case RENDER_MODE_2D:
		Pipeline::scale(it->getOwner()->GetTransform()->getScale().x, it->getOwner()->GetTransform()->getScale().y, it->getOwner()->GetTransform()->getScale().z);
		m_shaderProg.setUniform("MVP", Pipeline::getTransformationMatrix2D());
		m_shaderProg.setUniform("V", glm::mat4(1.0));
		m_shaderProg.setUniform("P", glm::mat4(1.0));
		m_shaderProg.setUniform("FullBright", 1);
		break;
	case RENDER_MODE_3D:
		Pipeline::scale(it->getOwner()->GetTransform()->getScale().x, it->getOwner()->GetTransform()->getScale().y, it->getOwner()->GetTransform()->getScale().z);
		m_shaderProg.setUniform("MVP", Pipeline::getTransformationMatrix());

		m_shaderProg.setUniform("V", Pipeline::m_view);
		m_shaderProg.setUniform("P", Pipeline::m_projection);
		m_shaderProg.setUniform("FullBright", 0);
		break;
	}

	m_shaderProg.setUniform("ModelViewMatrix", Pipeline::m_view * Pipeline::m_model);
	m_shaderProg.setUniform("NormalMatrix", glm::mat3(glm::transpose(glm::inverse(Pipeline::m_model))));
	m_shaderProg.setUniform("M", Pipeline::m_model);
	m_shaderProg.setUniform("textureNormal", 0);
	m_shaderProg.setUniform("Translucent", 1);

	// Render the meshes
	std::vector<Mesh>& m = it->getModel()->getMeshes();
	for (unsigned int i = 0; i < m.size(); ++i)
	{
		glBindVertexArray(m[i].m_VAO);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, t->texture->getTexId());
		m_shaderProg.setUniform("textureDiffuse", 0);

		glDrawArrays(GL_TRIANGLES, 0, m[i].m_Entries[0].NumIndices);
		glBindTexture(GL_TEXTURE_2D, 0);

		glBindVertexArray(0);
	}
}


void SGraphics::rebuildCache()
{
	CGraphicsCache.clear();
	std::map<std::string, Entity*> entityList = m_CurrentState->getEntities();
	auto it = entityList.begin();
	while (it != entityList.end())
	{
		std::vector<Component*> cList = (*it).second->getComponentsByType("Graphics");
		auto CIterator = cList.begin();
		while (CIterator != cList.end())
		{
			CGraphicsCache.push_back(static_cast<CGraphics*>(*CIterator));
			++CIterator;
		}
		++it;
	}
}
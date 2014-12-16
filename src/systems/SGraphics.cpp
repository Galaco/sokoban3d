#include "SGraphics.h"

//Initialize statics. Note these aren't required to be static, but for clarity are
DeferredRenderer SGraphics::m_deferredRenderer;
GeometryPass SGraphics::m_geometryPass;
PointLightPass SGraphics::m_pointLightPass;
DirectionalLightPass SGraphics::m_directionalLightPass;
StencilPass	SGraphics::m_stencilPass;
TransparencyPass SGraphics::m_transparencyPass;
ResourceManager SGraphics::m_Resources;
Model* SGraphics::m_directionalQuad;
Model* SGraphics::m_pointSphere;

SGraphics::SGraphics(){
}

SGraphics::~SGraphics(){
}

void SGraphics::initialize(){
	//Initialize the renderer
	m_deferredRenderer.initialize();
	m_geometryPass.initialize();
	m_geometryPass.setFbo(m_deferredRenderer.getFbo());
	m_pointLightPass.initialize();
	m_pointLightPass.setFbo(m_deferredRenderer.getFbo());
	m_directionalLightPass.initialize();
	m_directionalLightPass.setFbo(m_deferredRenderer.getFbo());
	m_stencilPass.initialize();
	m_stencilPass.setFbo(m_deferredRenderer.getFbo());
	m_transparencyPass.initialize();

	m_directionalQuad = m_Resources.add<Model>("shapes/quad.obj");
	m_pointSphere = m_Resources.add<Model>("shapes/sphere.obj");

	//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	glEnable(GL_CULL_FACE);
}
	
void SGraphics::update(){
	std::map<std::string, Entity*> entityList = m_CurrentState->getEntities();
	
	//Begin frame
	m_deferredRenderer.startFrame();

	//Render geometry
	m_geometryPass.startPass();
	auto it = entityList.begin();
	while(it != entityList.end()) 
	{
		std::vector<Component*> cList = (*it).second->getComponentsByType("Graphics");
		auto CIterator = cList.begin();
		while(CIterator != cList.end())
		{
			drawEntity(static_cast<CGraphics*>((*CIterator)));
			++CIterator;
		}
		++it;
	}
	//draw
	drawSkybox();
	m_geometryPass.endPass();

	//Render point lights
	glEnable(GL_STENCIL_TEST);
	it = entityList.begin();
	while(it != entityList.end()) 
	{
		std::vector<Component*> cList = (*it).second->getComponentsByType("Graphics");
		auto CIterator = cList.begin();
		while(CIterator != cList.end())
		{
			drawLight(static_cast<CGraphics*>((*CIterator)));
			++CIterator;
		}
		++it;
	}
	glDisable(GL_STENCIL_TEST);

	//Render directional/ambient light
	drawDirectionalLight();

	//Complete and write out the frame
	m_deferredRenderer.endFrame();


	m_transparencyPass.startPass();
	it = entityList.begin();
	while (it != entityList.end())
	{
		std::vector<Component*> cList = (*it).second->getComponentsByType("Graphics");
		auto CIterator = cList.begin();
		while (CIterator != cList.end())
		{
			CGraphics* g = static_cast<CGraphics*>((*CIterator));
			if (g->getText())
			{
				drawText(g);
			}
			++CIterator;
		}
		++it;
	}
	m_transparencyPass.endPass();

}

void SGraphics::drawEntity(CGraphics* it)
{
	if (!it->getModel())
		return;

	Pipeline::position(it->getOwner()->GetTransform()->getPosition().x, it->getOwner()->GetTransform()->getPosition().y, it->getOwner()->GetTransform()->getPosition().z);
	Pipeline::rotate(it->getOwner()->GetTransform()->getOrientation().x, it->getOwner()->GetTransform()->getOrientation().y, it->getOwner()->GetTransform()->getOrientation().z);
	Pipeline::scale(it->getOwner()->GetTransform()->getScale().x, it->getOwner()->GetTransform()->getScale().y, it->getOwner()->GetTransform()->getScale().z);

	switch(it->getRenderMode())
	{
	case RENDER_MODE_2D:
		glUniformMatrix4fv(Pipeline::m_MVPMatrix, 1, GL_FALSE, &Pipeline::getTransformationMatrix2D()[0][0]);
		glUniformMatrix4fv(Pipeline::m_VPMatrix, 1, GL_TRUE, &glm::mat4(1.0)[0][0]);
		break;
	case RENDER_MODE_3D:
		glUniformMatrix4fv(Pipeline::m_MVPMatrix, 1, GL_FALSE, &Pipeline::getTransformationMatrix()[0][0]);
		glUniformMatrix4fv(Pipeline::m_VPMatrix, 1, GL_TRUE, &Pipeline::getWorldMatrix()[0][0]);
		break;
	}

	// Render the meshes
	MeshList& m = it->getModel()->getMeshes();
	for (unsigned int i = 0; i < m.size(); ++i)
	{
		glBindVertexArray(m[i].uiVAO);

		glActiveTexture(GL_TEXTURE0);
		if (it->getOverrideMaterial(i)){
			glBindTexture(GL_TEXTURE_2D, it->getOverrideMaterial(i)->texId());
		}
		else {
			glBindTexture(GL_TEXTURE_2D, m[i].m_TexID);
		}
		glDrawElements(GL_TRIANGLES, m[i].m_IndexBuffer.size(), GL_UNSIGNED_SHORT, (void*)0);
		glBindTexture(GL_TEXTURE_2D, 0);

		glBindVertexArray(0);
	}
}

void SGraphics::drawLight(CGraphics* it)
{
	PointLight* Light = it->getPointLight();
	if (Light != nullptr){
		if (m_pointSphere->getMeshes().size() < 1){
			return;
		}
		Mesh* lightMesh = &m_pointSphere->getMeshes()[0];
		/**************************************************************/
		// Begin Stencil pass for light
		/**************************************************************/
		//bind for stencil pass
		glDrawBuffer(GL_NONE);

		m_stencilPass.startPass(it, Light);	
		glBindVertexArray(lightMesh->uiVAO); 
		glDrawElements(GL_TRIANGLES, lightMesh->m_IndexBuffer.size(), GL_UNSIGNED_SHORT,	(void*)0 );

		m_stencilPass.endPass();

		/**************************************************************/
		// Begin Render pass for light
		/**************************************************************/ 
		//Bind for light pass
		glDrawBuffer(GL_COLOR_ATTACHMENT4);
		m_deferredRenderer.bindBufferTextures();	

		m_pointLightPass.startPass(it, Light);
		glDrawElements(GL_TRIANGLES, lightMesh->m_IndexBuffer.size(), GL_UNSIGNED_SHORT,	(void*)0 );
		glBindVertexArray(0); 

		m_pointLightPass.endPass();
	}
}

void SGraphics::drawSkybox()
{
	if (m_CurrentState == nullptr || m_CurrentState->getCurrentCamera() == nullptr) {
		return;
	}
	Skybox* sky = m_CurrentState->getCurrentCamera()->getSkybox();
	if (sky == nullptr) return;
	Pipeline::position(Pipeline::Eye);

	glUniformMatrix4fv(Pipeline::m_MVPMatrix, 1, GL_FALSE, &Pipeline::getTransformationMatrix()[0][0]);

	glBindVertexArray(sky->getVao()); 

	glEnable(GL_TEXTURE_2D);
	for(int i=0; i<6; ++i) { 
		glActiveTexture(GL_TEXTURE0);
		sky->bindTexture(i);
		sky->bindSampler(i);
		glDrawArrays(GL_TRIANGLE_STRIP, i*4, 4); 
	}
	glBindVertexArray(0); 
}

void SGraphics::drawDirectionalLight()
{
	if (m_CurrentState == nullptr || m_CurrentState->getDirectionalLight() == nullptr) {
		return;
	}
	//Begin pass
	glDrawBuffer(GL_COLOR_ATTACHMENT4);
	m_deferredRenderer.bindBufferTextures();	
	m_directionalLightPass.startPass(m_CurrentState->getDirectionalLight());

	Mesh& m = m_directionalQuad->getMeshes()[0];
	glBindVertexArray(m.uiVAO); 

	glDrawElements(GL_TRIANGLES, m.m_IndexBuffer.size(), GL_UNSIGNED_SHORT, (void*)0);

	glBindVertexArray(0); 

	//End pass
	m_directionalLightPass.endPass();
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
		Pipeline::scale(it->getOwner()->GetTransform()->getScale().x / 120, it->getOwner()->GetTransform()->getScale().y / 120, it->getOwner()->GetTransform()->getScale().z);
		m_transparencyPass.setTransformation(Pipeline::getTransformationMatrix2D());
		break;
	case RENDER_MODE_3D:
		Pipeline::scale(it->getOwner()->GetTransform()->getScale().x, it->getOwner()->GetTransform()->getScale().y, it->getOwner()->GetTransform()->getScale().z);
		m_transparencyPass.setTransformation(Pipeline::getTransformationMatrix());
		break;
	}

	// Render the meshes
	MeshList& m = t->getModel().getMeshes();
	for (unsigned int i = 0; i < m.size(); ++i)
	{
		glBindVertexArray(m[i].uiVAO);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, t->texture->getTexId());

		glDrawArrays(GL_TRIANGLES, 0, m[i].m_vertexCount);
		glBindTexture(GL_TEXTURE_2D, 0);

		glBindVertexArray(0);
	}
}
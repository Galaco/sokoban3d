#include "SAnimation.h"

std::map<CAnimation*, CGraphics*> SAnimation::CGraphicsCAnimationCache;


SAnimation::SAnimation(){
}

SAnimation::~SAnimation(){
}

void SAnimation::initialize(){
}
	
void SAnimation::update(float dt){
	if ((m_CurrentState != m_PreviousState) || Scene::ForceRecache)
	{
		rebuildCache();
	}

	auto it = CGraphicsCAnimationCache.begin();
	while (it != CGraphicsCAnimationCache.end()) 
	{
		updateAnimation((*it).first, (*it).second, dt);
		++it;
	}
}
	

void SAnimation::updateAnimation(CAnimation* anim, CGraphics* model, float dt){
	MD5Animation* c = static_cast<MD5Animation*>(anim->getAnimation());
	Entity* e = anim->getOwner();
	if (model->getModel() != nullptr){
		c->update(dt);
		const MD5Animation::FrameSkeleton& skeleton = c->getSkeleton();
		updateMesh(model->getModel(), skeleton);
	}
}

void SAnimation::updateMesh(Model* model, const MD5Animation::FrameSkeleton& skel){
    /*std::vector<Mesh>& meshes = model->getMeshes();
    for ( unsigned int h = 0; h < meshes.size(); ++h ){
		for ( unsigned int i = 0; i < meshes[h].m_Verts.size(); ++i )
		{
			const Vertex& vert = meshes[h].m_Verts[i];
			glm::vec3& pos = meshes[h].m_PositionBuffer[i];
			glm::vec3& normal = meshes[h].m_NormalBuffer[i];

			pos = glm::vec3(0);
			normal = glm::vec3(0);

			// calculate position+normal via weights
			for ( int j = 0; j < vert.m_WeightCount; ++j )
			{
			const Weight& weight = meshes[h].m_Weights[vert.m_StartWeight + j];
			const MD5Animation::SkeletonJoint& joint = skel.m_Joints[weight.m_JointID];

			glm::vec3 rotPos = joint.m_Orient * weight.m_Pos;
			pos += ( joint.m_Pos + rotPos ) * weight.m_Bias;

			normal += ( joint.m_Orient * vert.m_Normal ) * weight.m_Bias;
			}
		}

		// maybe can be deleted?
		glBindVertexArray(meshes[h].uiVAO); 

		glBindBuffer(GL_ARRAY_BUFFER, meshes[h].uiBuffer);
		glBufferData(GL_ARRAY_BUFFER, meshes[h].m_PositionBuffer.size() * sizeof(glm::vec3), &meshes[h].m_PositionBuffer[0] , GL_STREAM_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, meshes[h].normalBuffer);
		glBufferData(GL_ARRAY_BUFFER, meshes[h].m_NormalBuffer.size() * sizeof(glm::vec3), &meshes[h].m_NormalBuffer[0] , GL_STREAM_DRAW);

		glBindVertexArray(0); 
    }*/
}

void SAnimation::rebuildCache()
{
	CGraphicsCAnimationCache.clear();	//Empty cache
	std::map<std::string, Entity*> entityList = m_CurrentState->getEntities();
	auto it = entityList.begin();
	while (it != entityList.end())
	{
		std::vector<Component*> cList = (*it).second->getComponentsByType("Animation");
		auto CIterator = cList.begin();
		while (CIterator != cList.end())
		{
			CGraphicsCAnimationCache[static_cast<CAnimation*>(*CIterator)] = static_cast<CGraphics*>((*CIterator)->getOwner()->getComponent("Graphics"));	//Add graphics to animation cache
			++CIterator;
		}
		++it;
	}
}
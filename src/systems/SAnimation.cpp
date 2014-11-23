#include "SAnimation.h"

SAnimation::SAnimation(){
}

SAnimation::~SAnimation(){
}

void SAnimation::initialize(){
}
	
void SAnimation::update(float dt){
	std::map<std::string, Entity*> entityList = m_CurrentState->getEntities();
	auto it = entityList.begin();
	while(it != entityList.end()) {
		std::vector<Component*> cList = (*it).second->getComponentsByType("Animation");
		auto CIterator = cList.begin();
		while(CIterator != cList.end())
		{
			CAnimation* pAnim = static_cast<CAnimation*>(*CIterator);
			updateAnimation(pAnim, dt);
			++CIterator;
		}
		++it;
	}
}
	

void SAnimation::updateAnimation(CAnimation* anim, float dt){
	MD5Animation* c = static_cast<MD5Animation*>(anim->getAnimation());
	Entity* e = anim->getOwner();
	CGraphics* grap = static_cast<CGraphics*>(e->getComponent("Graphics"));
	if (grap->getModel() != nullptr){
		c->update(dt);
		const MD5Animation::FrameSkeleton& skeleton = c->getSkeleton();
		updateMesh(grap->getModel(), skeleton);
	}
}

void SAnimation::updateMesh(Model* model, const MD5Animation::FrameSkeleton& skel){
    std::vector<Mesh>& meshes = model->getMeshes();
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
    }
}
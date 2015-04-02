#include "Model.h"

Model::Model()
: m_LocalToWorldMatrix(1)
, m_jointCount(0)
, m_meshCount(0) { 
}
	
Model::~Model(){
	//Cleanup
	auto it = m_meshList.begin();
	while (it != m_meshList.end()){
		glDeleteVertexArrays(1, &(*it).m_VAO);
		glDeleteVertexArrays(1, &(*it).m_Buffers[INDEX_BUFFER]);
		glDeleteVertexArrays(1, &(*it).m_Buffers[POS_VB]);
		glDeleteVertexArrays(1, &(*it).m_Buffers[NORMAL_VB]);
		glDeleteVertexArrays(1, &(*it).m_Buffers[TEXCOORD_VB]);
		glDeleteVertexArrays(1, &(*it).m_Buffers[BONE_VB]);
		glDeleteVertexArrays(1, &(*it).m_Buffers[NUM_VBs]);
		++it;
	}
}
      
void Model::setFormat(std::string f){ 
    m_format = f;
}
        
std::string Model::getFormat(){ 
    return m_format;
}

void Model::addMesh(Mesh& mesh){
	if (m_textureList.find("Default") != m_textureList.end() &&
		mesh.m_texID[mesh.numTextures] == 99999){
		mesh.m_texID[mesh.numTextures] = m_textureList["Default"].getTexId();
		mesh.numTextures++;
	}
	m_meshList.push_back(mesh);
}
std::vector<Mesh>& Model::getMeshes(){
	return m_meshList;
}

void Model::addTexture(std::string id, Texture* tex){
	m_textureList[id] = *tex;
	if (m_meshList.size() == 1 && m_meshList[0].m_texID[0] == 99999) 
	{
		m_meshList[0].m_texID[0] = m_textureList[id].getTexId();
	}
	else 
	{
		for (unsigned short i = 0; i < m_meshList.size(); ++i){
			if (m_meshList[i].m_texID[0] == 99999) {
				m_meshList[i].m_texID[0] = m_textureList[id].getTexId();
			}
		}
	}
}
std::map<std::string, Texture>& Model::getTextures(){
	return m_textureList;
}
Texture* Model::getTexture(std::string id){
	return &m_textureList[id];
}

std::string& Model::getFileFormatVersion(){
	return m_FileFormatVersion;
}

void Model::setFileFormatVersion(std::string version){
	m_FileFormatVersion = version;
}

int& Model::getMeshCount(){
	return m_meshCount;
}
int& Model::getJointCount(){
	return m_jointCount;
}
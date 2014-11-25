#include "Model.h"

Model::Model()
: m_LocalToWorldMatrix(1)
, m_jointCount(0)
, m_meshCount(0) { 
	m_textureList["Default"] = nullptr;
}
	
Model::~Model(){
	//Cleanup
	auto it = m_meshList.begin();
	while (it != m_meshList.end()){
		glDeleteVertexArrays(1, &(*it).uiVAO);
		glDeleteVertexArrays(1, &(*it).indexBuffer);
		glDeleteVertexArrays(1, &(*it).normalBuffer);
		glDeleteVertexArrays(1, &(*it).uiBuffer);
		glDeleteVertexArrays(1, &(*it).uvBuffer);
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
		m_textureList["Default"] != nullptr &&
		mesh.m_TexID == 99999){
			mesh.m_TexID = m_textureList["Default"]->getTexId();
	}
	m_meshList.push_back(mesh);
}
std::vector<Mesh>& Model::getMeshes(){
	return m_meshList;
}
std::vector<Joint>& Model::getJoints(){
	return m_JointList;
}

void Model::addTexture(std::string id, Texture* tex){
	m_textureList[id] = tex;
	if (m_meshList.size() == 1 && m_meshList[0].m_TexID == 99999) 
	{
		m_meshList[0].m_TexID = m_textureList[id]->getTexId();
	}
	else 
	{
		for (unsigned short i = 0; i < m_meshList.size(); ++i){
			if (m_meshList[i].m_TexID == 99999) {
				m_meshList[i].m_TexID = m_textureList[id]->getTexId();
			}
		}
	}
}
std::map<std::string, Texture*>& Model::getTextures(){
	return m_textureList;
}
Texture* Model::getTexture(std::string id){
	return m_textureList[id];
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
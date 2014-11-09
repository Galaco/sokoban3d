#include "ResourceManager.h"

std::map<std::string, CShaderProgram*> ResourceManager::m_shaderList;
std::map<std::string, Texture*> ResourceManager::m_textureList;
std::map<std::string, Model*> ResourceManager::m_modelList;

ModelLoader ResourceManager::m_modelLoader;
TextureLoader ResourceManager::m_textureLoader;

ResourceManager::ResourceManager(){

}

ResourceManager::~ResourceManager(){
    
}

Model* ResourceManager::getModel(std::string id){
        if(m_modelList.find(id) == m_modelList.end()) {
		return nullptr; 
	} else { 
		return m_modelList[id];
	}
}

Texture* ResourceManager::getTexture(std::string id){
        if(m_textureList.find(id) == m_textureList.end()) { 
		return nullptr; 
	} else { 
		return m_textureList[id];
	}
}

CShaderProgram* ResourceManager::getShader(std::string id)
{
	if(m_shaderList.find(id) == m_shaderList.end()) { 
		return nullptr; 
	} else {
		 return m_shaderList[id];
	}
}
	
bool ResourceManager::remove(resourceType r, std::string id)
{
	switch(r){
	case SHADER:
		delete m_shaderList[id];
		m_shaderList.erase(id);
		break;
	case TEXTURE:
		delete m_textureList[id];
		m_textureList.erase(id);
		break;
	case MESH:
		delete m_modelList[id];
		m_modelList.erase(id);
		break;
	}
	return true;
}

bool ResourceManager::empty(resourceType r)
{
	return true;
}

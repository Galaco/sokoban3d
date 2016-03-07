#include "ResourceManager.h"

std::map<std::string, Texture> ResourceManager::m_textureList;
std::map<std::string, BaseAnimation> ResourceManager::m_animationList;
std::map<std::string, Model> ResourceManager::m_modelList;

ModelLoader ResourceManager::m_modelLoader;
TextureLoader ResourceManager::m_textureLoader;
AnimationLoader ResourceManager::m_animationLoader;

ResourceManager::ResourceManager(){

}

ResourceManager::~ResourceManager(){
    
}

Model* ResourceManager::getModel(std::string id){
        if(m_modelList.find(id) == m_modelList.end()) {
		return nullptr; 
	} else { 
		return &m_modelList[id];
	}
}

Texture* ResourceManager::getTexture(std::string id){
        if(m_textureList.find(id) == m_textureList.end()) { 
		return nullptr; 
	} else { 
		return &m_textureList[id];
	}
}

BaseAnimation* ResourceManager::getAnimation(std::string id){
	if(m_animationList.find(id) == m_animationList.end()) { 
		return nullptr; 
	} else { 
		return &m_animationList[id];
	}
}
	
bool ResourceManager::remove(resourceType r, std::string id){
	switch(r){
	case TEXTURE:
		//delete m_textureList[id];
		m_textureList.erase(id);
		break;
	case MESH:
		//delete m_modelList[id];
		m_modelList.erase(id);
		break;
	}
	return true;
}

void ResourceManager::empty(){

}

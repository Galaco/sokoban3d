/*********************************************************************
Project: Dissertation
Author: Josh Martin

Name: Resource Manager
Description: The store for all loaded models, animations, textures,
			 shaders(unecessary). Responsible for calling loaders to 
			 add data to the store. Checks that objects are not loaded
			 multiple times.
*********************************************************************/
#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <string>
#include <map>
#include <memory>
#include <core/Logger.h>

#include <core/ModelLoader.h>
#include <core/TextureLoader.h>
#include <core/AnimationLoader.h>

#include <core/resources/BaseAnimation.h>
#include <core/Resource.h>
#include <core/resources/Texture.h>
#include <core/resources/Model.h>
#include <core/resources/Shader.h>

enum resourceType {
	ALL = 0,
	SHADER,
	TEXTURE,
	MESH
};

class ResourceManager {
public:
	ResourceManager();

	~ResourceManager();

	void empty();

    template <class Resource>
    static Resource* add(std::string);	//Add a resource to storage
        
    static Model* getModel(std::string);	//Get a model from storage
	static Texture* getTexture(std::string);	//Get a texture from storage
	static BaseAnimation* getAnimation(std::string);	//Get an animation from storage
        

	static bool remove(resourceType r, std::string id);	//Erase an object from storage
private:
	static std::map<std::string, Texture> m_textureList;
	static std::map<std::string, BaseAnimation> m_animationList;
	static std::map<std::string, Model> m_modelList;
        
	static ModelLoader m_modelLoader;
	static TextureLoader m_textureLoader;
	static AnimationLoader m_animationLoader;
};

template <> 
inline Model* ResourceManager::add<Model>(std::string path)
{
	if(m_modelList.find(path) != m_modelList.end()) { 
		return &m_modelList[path];
	}
	Model* m = m_modelLoader.load(path);
    m_modelList[path] = *m;
	return &m_modelList[path];
}

template <>
inline Texture* ResourceManager::add<Texture>(std::string path)
{
	if(m_textureList.find(path) != m_textureList.end()) { 
		return &m_textureList[path];
	}
	Texture* t = m_textureLoader.load(path);
	m_textureList[path] = *t;
	return &m_textureList[path];
}

template <>
inline BaseAnimation* ResourceManager::add<BaseAnimation>(std::string path)
{
	if(m_animationList.find(path) != m_animationList.end()) { 
		return &m_animationList[path];
	}
	BaseAnimation* t = m_animationLoader.load(path);
	m_animationList[path] = *t;
	return &m_animationList[path];
}

#endif

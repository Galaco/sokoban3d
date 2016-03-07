/*********************************************************************
Project: Dissertation
Author: Josh Martin

Name: Material
Description: Loads and stores a texture from a file. 
*********************************************************************/
#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>
#include <core/Logger.h>
#include <core/ResourceManager.h>
#include <core/resources/Texture.h>

#include <json/json.h>



class Material
{
public:
	enum TextureType{
		DIFFUSE = 0,
		NORMAL,
		SPECULAR,
		HEIGHT
	};

	Material();
	Material(const char*);
	~Material();

	bool load(const char*);

	GLuint texId(TextureType t = TextureType::DIFFUSE);


	bool translucent;
	bool fullbright;

private:
	void prepareDefaults();


	Texture* m_diffuse, *m_normal, *m_specular;
};
#endif
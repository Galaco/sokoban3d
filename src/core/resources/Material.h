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
	Material();
	Material(const char*);
	~Material();

	bool load(const char*);

	GLuint texId();


	bool translucent;

private:
	void prepareDefaults();


	Texture* m_texture;
};
#endif
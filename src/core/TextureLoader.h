/*********************************************************************
Project: Dissertation
Author: Josh Martin

Name: Texture Loader
Description: Responsible for loading textures (via SFML Graphics)
*********************************************************************/
#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <string>
#include <map>
#include <memory>
#include <core/Logger.h>

#include <core/resources/Texture.h>


class TextureLoader {
public:
	TextureLoader();
	~TextureLoader();
        
    Texture* load(std::string);	//Load a texture (with name checks)

    Texture* createTexture(std::string);	//Create a texture (doesn't check name)
private:
};
#endif

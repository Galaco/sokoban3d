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
        
    Texture* load(std::string);

    Texture* createTexture(std::string);
private:
};
#endif

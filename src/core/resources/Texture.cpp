#include "Texture.h"

Texture::Texture(){
	diffuse = 0;
}

Texture::Texture(const char* path){
	diffuse = 0;
	this->load(path);
}

Texture::~Texture(){
	unload();
}

GLuint& Texture::load(const char* path){
	sf::Image image;
	if(!image.loadFromFile( path ) )
	{
		return diffuse;
	}
	int width = image.getSize().x;
	int height = image.getSize().y;

	glGenTextures( 1 , &diffuse );
	glBindTexture( GL_TEXTURE_2D , diffuse );
	
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA8, width , height, 0, GL_RGBA
		, GL_UNSIGNED_BYTE, image.getPixelsPtr() );

	glGenerateMipmap(GL_TEXTURE_2D);

	glTexEnvi( GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , GL_MODULATE );

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	return diffuse;
}

void Texture::unload(){
	glDeleteTextures(1, &diffuse);
};

GLuint& Texture::getTexId(){ 
	return diffuse; 
}
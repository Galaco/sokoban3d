#include "TextureLoader.h"

TextureLoader::TextureLoader(){

}

TextureLoader::~TextureLoader(){
    
}

Texture* TextureLoader::load(std::string path){
	unsigned found = path.find_last_of(".");
	std::string filetype = path.substr(found+1, path.length()-found);
	if (filetype == "jpg" ||
		filetype == "png" ||
		filetype == "raw" ||
		filetype == "tga" ) {
		return createTexture(path);
	}


	return nullptr;    
}

Texture* TextureLoader::createTexture(std::string path){
	sf::Image image;
	Texture* t = new Texture;
	if(!image.loadFromFile( path ) ){
		return nullptr;
	}
	int width = image.getSize().x;
	int height = image.getSize().y;

	glGenTextures( 1 , &t->getTexId() );
	glBindTexture( GL_TEXTURE_2D , t->getTexId() );


	// build our texture MIP maps
	//gluBuild2DMipmaps( GL_TEXTURE_2D , 3 , width , height, GL_RGBA16, GL_UNSIGNED_BYTE, image.GetPixelsPtr() );
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA8, width , height, 0, GL_RGBA
		, GL_UNSIGNED_BYTE, image.getPixelsPtr() );
	glTexEnvi( GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , GL_MODULATE );

	glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MIN_FILTER , GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MAG_FILTER , GL_LINEAR);

	return t;
}
#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <GL\glew.h>
#include <SFML/Graphics.hpp>
#include <GLFW/glfw3.h>

#include <core/Resource.h>

class Texture : public Resource
{
public:
	Texture();
	Texture(const char* path);
	~Texture();

	GLuint&		load(const char* path);
	void		unload();
	GLuint&		getTexId();

private:
	GLuint			diffuse;
};
#endif
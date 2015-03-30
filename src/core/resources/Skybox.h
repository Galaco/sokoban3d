/*********************************************************************
Project: Dissertation
Author: Josh Martin

Name: Skybox
Description: Represents a skybox in the world. Is self contained due
			 custom texture requirements
*********************************************************************/
#ifndef SKYBOX_H
#define SKYBOX_H

#include <string>

#include <glm/glm.hpp>

#include <core/Logger.h>

#include <GL\glew.h>
#include <GLFW/glfw3.h>
#include <SFML/Graphics.hpp>

#include "Shader.h"
#include <core/helpers/Pipeline.h>

class Skybox {
public:
	Skybox();
	Skybox(std::string file);
	~Skybox();

	void load(std::string);

	void loadTexture(const char*, GLenum);
	void createCube();

	void setzFar(float dist);
	GLuint& getVbo();
	GLuint& getVao();
	GLuint& getTexture();
	void bindTexture();

	void useProgram();

private:
	void createShader();

	float zFar;


	GLuint vao;
	GLuint vbo;
	GLuint m_texture;

	CShaderProgram	m_shaderProg;
	CShader m_shader[2];
	static bool shaderReady;

	GLuint m_VPLocation;
};
#endif

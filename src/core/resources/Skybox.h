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

class Skybox {
public:
	Skybox();
	~Skybox();

	void load(std::string);

	void loadTexture(const char*, int);
	void createCube();

	void setzFar(float dist);
	GLuint& getVbo();
	GLuint& getVao();
	GLuint& getTexture();
	void bindTexture(int i);
	void bindSampler(int i);

	glm::vec2 rotation;
private:

	GLuint m_vbo, m_vao, mTexture[6], sampler_state[6];
	GLuint vertexBuffer, uvBuffer, normalBuffer;
	std::vector<glm::vec3> vertices, normals;
	std::vector<glm::vec2> uvs;
	float zFar;
};
#endif

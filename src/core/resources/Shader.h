/*********************************************************************
Project: Dissertation
Author: Josh Martin

Name: Shader
Description: Contains data about 1 loaded shader
*********************************************************************/
#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <vector>

#include <core/Logger.h>

#include <gl/glew.h>
#include <GLFW/glfw3.h>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <core/Resource.h>


using namespace std;

class CShader
{
public:
	bool loadShader(string sFile, int a_iType);
	bool loadFromString(const char** rawShader, int lines, int a_iType);
	void deleteShader();

	bool isLoaded();
	GLuint getShaderID();

	CShader();

private:
	GLuint uiShader; // ID of shader
	int iType; // GL_VERTEX_SHADER, GL_FRAGMENT_SHADER...
	bool bLoaded; // Whether shader was loaded and compiled
};
#endif;


/*********************************************************************
Project: Dissertation
Author: Josh Martin

Name: Shader Program
Description: Stores info about a complete compiled shader
*********************************************************************/
#ifndef CSHADERPROGRAM_H
#define CSHADERPROGRAM_H

#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class CShaderProgram : public Resource
{
public:
	void createProgram();
	void deleteProgram();

	bool addShaderToProgram(CShader* shShader);
	bool linkProgram();

	void useProgram();

	GLuint getProgramID();

	CShaderProgram();



	void   setUniform(const char *name, float x, float y, float z);
	void   setUniform(const char *name, const glm::vec2 & v);
	void   setUniform(const char *name, const glm::vec3 & v);
	void   setUniform(const char *name, const glm::vec4 & v);
	void   setUniform(const char *name, const glm::mat4 & m);
	void   setUniform(const char *name, const glm::mat3 & m);
	void   setUniform(const char *name, float val);
	void   setUniform(const char *name, int val);
	void   setUniform(const char *name, bool val);
	void   setUniform(const char *name, GLuint val);

private:
	GLuint uiProgram; // ID of program
	bool bLinked; // Whether program was linked and is ready to use
};
#endif;

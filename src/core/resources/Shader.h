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


#include <gl/glew.h>
#include <GLFW/glfw3.h>

#include <core/Logger.h>

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

private:
	GLuint uiProgram; // ID of program
	bool bLinked; // Whether program was linked and is ready to use
};
#endif;

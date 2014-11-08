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
	void deleteShader();

	bool isLoaded();
	GLuint getShaderID();

	CShader();

private:
	GLuint uiShader; // ID of shader
	int iType; // GL_VERTEX_SHADER, GL_FRAGMENT_SHADER...
	bool bLoaded; // Whether shader was loaded and compiled
	Logger* m_logger;
};
#endif;


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


	// Setting vectors
	void setUniform(string sName, glm::vec2* vVectors, int iCount = 1);
	void setUniform(string sName, const glm::vec2 vVector);
	void setUniform(string sName, glm::vec3* vVectors, int iCount = 1);
	void setUniform(string sName, const glm::vec3 vVector);
	void setUniform(string sName, glm::vec4* vVectors, int iCount = 1);
	void setUniform(string sName, const glm::vec4 vVector);

	// Setting floats
	void setUniform(string sName, float* fValues, int iCount = 1);
	void setUniform(string sName, const float fValue);

	// Setting 3x3 matrices
	void setUniform(string sName, glm::mat3* mMatrices, int iCount = 1);
	void setUniform(string sName, const glm::mat3 mMatrix);

	// Setting 4x4 matrices
	void setUniform(string sName, glm::mat4* mMatrices, int iCount = 1);
	void setUniform(string sName, const glm::mat4 mMatrix);

	// Setting integers
	void setUniform(string sName, int* iValues, int iCount = 1);
	void setUniform(string sName, const int iValue);

	CShaderProgram();

private:
	GLuint uiProgram; // ID of program
	bool bLinked; // Whether program was linked and is ready to use
};
#endif;

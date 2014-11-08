#include "Shader.h"

#include <glm/gtc/type_ptr.hpp>

CShader::CShader()
{
	bLoaded = false;
}

/*-----------------------------------------------

Name:	loadShader

Params:	sFile - path to a file
		a_iType - type of shader (fragment, vertex, geometry)

Result:	Loads and compiles shader.

/*---------------------------------------------*/

bool CShader::loadShader(string sFile, int a_iType)
{
	FILE* fp = fopen(sFile.c_str(), "rt");
	if(!fp){
		m_logger->log(_ERROR, ("Shader: Could not open: "+sFile).c_str());
		return false;
	}

	// Get all lines from a file

	vector<string> sLines;
	char sLine[255];
	while(fgets(sLine, 255, fp))sLines.push_back(sLine);
	fclose(fp);

	const char** sProgram = new const char*[(int)sLines.size()];
	for(int i =0; i<(int)sLines.size(); i++){
		sProgram[i] = sLines[i].c_str();
	}
	
	uiShader = glCreateShader(a_iType);

	glShaderSource(uiShader, (int)sLines.size(), sProgram, NULL);
	glCompileShader(uiShader);

	delete[] sProgram;

	int iCompilationStatus;
	glGetShaderiv(uiShader, GL_COMPILE_STATUS, &iCompilationStatus);

	if(iCompilationStatus == GL_FALSE){
		GLint maxLength = 0;
		glGetShaderiv(uiShader, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<char> errorLog(maxLength);
		glGetShaderInfoLog(uiShader, maxLength, &maxLength, &errorLog[0]);
		m_logger->log(_ERROR, ("Shader: Failed to compile: "+sFile).c_str());
		std::string str(errorLog.data(), errorLog.size());
		m_logger->log(_ERROR, ("Shader: Error: "+str).c_str());
		return false;
	}
	iType = a_iType;
	bLoaded = true;

	m_logger->log(_INFO, ("Shader: Loaded successfully: "+sFile).c_str());
	return 1;
}

bool CShader::isLoaded() {
	return bLoaded;
}


GLuint CShader::getShaderID() {
	return uiShader;
}

void CShader::deleteShader() {
	if(!isLoaded())return;
	bLoaded = false;
	glDeleteShader(uiShader);
}

CShaderProgram::CShaderProgram() {
	bLinked = false;
}

void CShaderProgram::createProgram() {
	uiProgram = glCreateProgram();
}

bool CShaderProgram::addShaderToProgram(CShader* shShader) {
	if(!shShader->isLoaded())return false;

	glAttachShader(uiProgram, shShader->getShaderID());

	return true;
}

bool CShaderProgram::linkProgram() {
	glLinkProgram(uiProgram);
	int iLinkStatus;
	glGetProgramiv(uiProgram, GL_LINK_STATUS, &iLinkStatus);
	bLinked = iLinkStatus == GL_TRUE;
	return bLinked;
}

void CShaderProgram::deleteProgram() {
	if(!bLinked)return;
	bLinked = false;
	glDeleteProgram(uiProgram);
}

void CShaderProgram::useProgram() {
	if(bLinked)glUseProgram(uiProgram);
}

GLuint CShaderProgram::getProgramID() {
	return uiProgram;
}

// Setting floats

void CShaderProgram::setUniform(string sName, float* fValues, int iCount) {
	int iLoc = glGetUniformLocation(uiProgram, sName.c_str());
	glUniform1fv(iLoc, iCount, fValues);
}

void CShaderProgram::setUniform(string sName, const float fValue) {
	int iLoc = glGetUniformLocation(uiProgram, sName.c_str());
	glUniform1fv(iLoc, 1, &fValue);
}

// Setting vectors

void CShaderProgram::setUniform(string sName, glm::vec2* vVectors, int iCount) {
	int iLoc = glGetUniformLocation(uiProgram, sName.c_str());
	glUniform2fv(iLoc, iCount, (GLfloat*)vVectors);
}

void CShaderProgram::setUniform(string sName, const glm::vec2 vVector) {
	int iLoc = glGetUniformLocation(uiProgram, sName.c_str());
	glUniform2fv(iLoc, 1, (GLfloat*)&vVector);
}

void CShaderProgram::setUniform(string sName, glm::vec3* vVectors, int iCount) {
	int iLoc = glGetUniformLocation(uiProgram, sName.c_str());
	glUniform3fv(iLoc, iCount, (GLfloat*)vVectors);
}

void CShaderProgram::setUniform(string sName, const glm::vec3 vVector) {
	int iLoc = glGetUniformLocation(uiProgram, sName.c_str());
	glUniform3fv(iLoc, 1, (GLfloat*)&vVector);
}

void CShaderProgram::setUniform(string sName, glm::vec4* vVectors, int iCount) {
	int iLoc = glGetUniformLocation(uiProgram, sName.c_str());
	glUniform4fv(iLoc, iCount, (GLfloat*)vVectors);
}

void CShaderProgram::setUniform(string sName, const glm::vec4 vVector) {
	int iLoc = glGetUniformLocation(uiProgram, sName.c_str());
	glUniform4fv(iLoc, 1, (GLfloat*)&vVector);
}

// Setting 3x3 matrices

void CShaderProgram::setUniform(string sName, glm::mat3* mMatrices, int iCount) {
	int iLoc = glGetUniformLocation(uiProgram, sName.c_str());
	glUniformMatrix3fv(iLoc, iCount, false, (GLfloat*)mMatrices);
}

void CShaderProgram::setUniform(string sName, const glm::mat3 mMatrix) {
	int iLoc = glGetUniformLocation(uiProgram, sName.c_str());
	glUniformMatrix3fv(iLoc, 1, false, (GLfloat*)&mMatrix);
}

// Setting 4x4 matrices

void CShaderProgram::setUniform(string sName, glm::mat4* mMatrices, int iCount) {
	int iLoc = glGetUniformLocation(uiProgram, sName.c_str());
	glUniformMatrix4fv(iLoc, iCount, false, (GLfloat*)mMatrices);
}

void CShaderProgram::setUniform(string sName, const glm::mat4 mMatrix) {
	int iLoc = glGetUniformLocation(uiProgram, sName.c_str());
	glUniformMatrix4fv(iLoc, 1, false, (GLfloat*)&mMatrix);
}

// Setting integers

void CShaderProgram::setUniform(string sName, int* iValues, int iCount) {
	int iLoc = glGetUniformLocation(uiProgram, sName.c_str());
	glUniform1iv(iLoc, iCount, iValues);
}

void CShaderProgram::setUniform(string sName, const int iValue) {
	int iLoc = glGetUniformLocation(uiProgram, sName.c_str());
	glUniform1i(iLoc, iValue);
}

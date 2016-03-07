#include "Shader.h"

#include <glm/gtc/type_ptr.hpp>

CShader::CShader()
{
	bLoaded = false;
}

//Loads and compiles a shader
bool CShader::loadShader(string sFile, int a_iType)
{
	FILE* fp = fopen(sFile.c_str(), "rt");
	if(!fp){
		Logger::log(ERROR_, ("Shader: Could not open: " + sFile).c_str());
		return false;
	}

	//Read in a file
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

		//Output compile error message
		std::vector<char> errorLog(maxLength);
		glGetShaderInfoLog(uiShader, maxLength, &maxLength, &errorLog[0]);
		Logger::log(ERROR_, ("Shader: Failed to compile: " + sFile).c_str());
		std::string str(errorLog.data(), errorLog.size());
		Logger::log(ERROR_, ("Shader: Error: " + str).c_str());
		return false;
	}
	iType = a_iType;
	bLoaded = true;

	Logger::log(SUCCESS, ("Shader: Loaded successfully: " + sFile).c_str());
	return 1;
}

bool CShader::loadFromString(const char** rawShader, int lines, int a_iType)
{
	uiShader = glCreateShader(a_iType);


	for (int i = 0; i < 20; ++i)
		Logger::log(WARNING, rawShader[i]);

	glShaderSource(uiShader, lines, rawShader, NULL);
	glCompileShader(uiShader);

	int iCompilationStatus;
	glGetShaderiv(uiShader, GL_COMPILE_STATUS, &iCompilationStatus);
	if(iCompilationStatus == GL_FALSE){
		GLint maxLength = 0;
		glGetShaderiv(uiShader, GL_INFO_LOG_LENGTH, &maxLength);

		//Output compile error message
		std::vector<char> errorLog(maxLength);
		glGetShaderInfoLog(uiShader, maxLength, &maxLength, &errorLog[0]);
		std::string str(errorLog.data(), errorLog.size());
		Logger::log(ERROR_, ("Shader: Error: " + str).c_str());
		return false;
	}

	Logger::log(SUCCESS, "Shader: Loaded successfully");
	return true;
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



void CShaderProgram::setUniform(const char *name, float x, float y, float z)
{
	GLint loc = glGetUniformLocation(uiProgram, name);
	glUniform3f(loc, x, y, z);
}

void CShaderProgram::setUniform(const char *name, const glm::vec3 & v)
{
	this->setUniform(name, v.x, v.y, v.z);
}

void CShaderProgram::setUniform(const char *name, const glm::vec4 & v)
{
	GLint loc = glGetUniformLocation(uiProgram, name);
	glUniform4f(loc, v.x, v.y, v.z, v.w);
}

void CShaderProgram::setUniform(const char *name, const glm::vec2 & v)
{
	GLint loc = glGetUniformLocation(uiProgram, name);
	glUniform2f(loc, v.x, v.y);
}

void CShaderProgram::setUniform(const char *name, const glm::mat4 & m)
{
	GLint loc = glGetUniformLocation(uiProgram, name);
	glUniformMatrix4fv(loc, 1, FALSE, &m[0][0]);
}

void CShaderProgram::setUniform(const char *name, const glm::mat3 & m)
{
	GLint loc = glGetUniformLocation(uiProgram, name);
	glUniformMatrix3fv(loc, 1, FALSE, &m[0][0]);
}

void CShaderProgram::setUniform(const char *name, float val)
{
	GLint loc = glGetUniformLocation(uiProgram, name);
	glUniform1f(loc, val);
}

void CShaderProgram::setUniform(const char *name, int val)
{
	GLint loc = glGetUniformLocation(uiProgram, name);
	glUniform1i(loc, val);
}

void CShaderProgram::setUniform(const char *name, GLuint val)
{
	GLint loc = glGetUniformLocation(uiProgram, name);
	glUniform1ui(loc, val);
}

void CShaderProgram::setUniform(const char *name, bool val)
{
	int loc = glGetUniformLocation(uiProgram, name);
	glUniform1i(loc, val);
}
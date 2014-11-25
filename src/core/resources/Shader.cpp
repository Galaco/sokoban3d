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
		m_logger->log(ERROR_, ("Shader: Could not open: "+sFile).c_str());
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
		m_logger->log(ERROR_, ("Shader: Failed to compile: "+sFile).c_str());
		std::string str(errorLog.data(), errorLog.size());
		m_logger->log(ERROR_, ("Shader: Error: "+str).c_str());
		return false;
	}
	iType = a_iType;
	bLoaded = true;

	m_logger->log(SUCCESS, ("Shader: Loaded successfully: "+sFile).c_str());
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
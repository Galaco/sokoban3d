/*********************************************************************
Project: Dissertation
Author: Josh Martin

Name: Model
Description: Contains a list of meshes, textures and joints. 
			 An instance represents 1 complete exported model.
*********************************************************************/
#ifndef MODEL_H
#define MODEL_H

#include <string>

#include <core/Logger.h>

#include <core/Resource.h>
#include "Texture.h"

#include <core/resources/Mesh.h>

class Model : public Resource
{
public:
	Model();
	~Model();

    void setFormat(std::string f);
    std::string getFormat();

	void addMesh(Mesh&);
	std::vector<Mesh>& getMeshes();
	std::vector<Joint>& getJoints();

	void addTexture(std::string, Texture*);
	std::map<std::string, Texture>& getTextures();
	Texture* getTexture(std::string);

	std::string& getFileFormatVersion();
	void setFileFormatVersion(std::string);
	int& getMeshCount();
	int& getJointCount();

protected:
	MeshList m_meshList;
	JointList m_JointList;
	std::map<std::string, Texture> m_textureList;

	std::string m_format;

	std::string m_FileFormatVersion;
	int m_meshCount, m_jointCount;

	glm::mat4x4         m_LocalToWorldMatrix;
};
#endif

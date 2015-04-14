/*********************************************************************
Project: Dissertation
Author: Josh Martin
Name: Wavefront Obj Format Loader
Description: Loads .obj format files. May have issues with normals
generation
*********************************************************************/
#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <string>
#include <map>
#include <memory>
#include <fstream>
#include <sstream>
#include <core/Logger.h>

#include <core/loaders/FileTypeLoader.h>

#include <core/resources/Model.h>


class ObjLoader : public FileTypeLoader {
public:
	ObjLoader();
	~ObjLoader();

	Model* load(std::string);


private:
	void InitMesh(GLuint MeshIndex,
		const aiMesh* paiMesh,
		std::vector<glm::vec3>& Positions,
		std::vector<glm::vec3>& Normals,
		std::vector<glm::vec2>& TexCoords,
		std::vector<glm::vec4>& Tangents,
		std::vector<VertexBoneData>& Bones,
		std::vector<GLuint>& Indices, Mesh& mesh);

	void LoadBones(unsigned int MeshIndex, const aiMesh* pMesh, std::vector<VertexBoneData>& Bones, Mesh& mesh);
};
#endif
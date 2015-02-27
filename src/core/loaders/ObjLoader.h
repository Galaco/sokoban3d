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
	void buildMesh(Mesh& mesh, Model* m);



	void generateTangents(
		const std::vector<glm::vec3> & points,
		const std::vector<glm::vec3> & normals,
		const std::vector<int> & faces,
		const std::vector<glm::vec2> & texCoords,
		std::vector<glm::vec4> & tangents);
	void trimString(std::string & str);
	void generateAveragedNormals(
		const std::vector<glm::vec3> & points,
		std::vector<glm::vec3> & normals,
		const std::vector<int> & faces);
};
#endif

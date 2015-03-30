/*********************************************************************
Project: Dissertation
Author: Josh Martin
Name: Collada Dae Format Loader
Description: Loads .dae format files. May have issues with normals
generation
*********************************************************************/
#ifndef DAELOADER_H
#define DAELOADER_H

#include <string>
#include <map>
#include <memory>
#include <fstream>
#include <sstream>
#include <core/Logger.h>

#include <core/loaders/FileTypeLoader.h>

#include <core/resources/Model.h>




class DaeLoader : public FileTypeLoader {
public:
	DaeLoader();
	~DaeLoader();

	Model* load(std::string);


private:
	void buildMesh(Mesh& mesh, Model* m);

};
#endif
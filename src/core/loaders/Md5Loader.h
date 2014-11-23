/*********************************************************************
Project: Dissertation
Author: Josh Martin

Name: MD5 Format Loader
Description: Loads Doom .md5 meshes only.
*********************************************************************/
#ifndef MD5LOADER_H
#define MD5LOADER_H

#include <string>
#include <map>
#include <memory>
#include <fstream>

#include <core/Logger.h>
#include <core/loaders/FileTypeLoader.h>

#include <core/resources/Mesh.h>
#include <core/resources/Model.h>


class Md5Loader : public FileTypeLoader {
public:
	Md5Loader();
	~Md5Loader();
        
    Model* load(std::string);

        
private:
	bool prepareMesh( Mesh&, Model* );
	bool prepareNormals( Mesh&, Model* );

	Logger* m_Logger;
};
#endif

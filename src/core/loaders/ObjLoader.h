#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <string>
#include <map>
#include <memory>
#include <fstream>
#include <core/Logger.h>

#include <core/loaders/FileTypeLoader.h>

#include <core/resources/Model.h>


class ObjLoader : public FileTypeLoader {
public:
	ObjLoader();
	~ObjLoader();
        
    Model* load(std::string);

        
private:
	bool prepareMesh( Mesh&, Model* );
	bool prepareNormals( Mesh&, Model* );
};
#endif

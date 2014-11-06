#ifndef FILETYPELOADER_H
#define FILETYPELOADER_H

#include <string>

#include <core/resources/Model.h>


class FileTypeLoader {
public:
	FileTypeLoader();
	~FileTypeLoader();
        
    virtual Model* load(std::string);

        
protected:
	virtual bool prepareMesh( Mesh&, Model* );
	virtual bool prepareNormals( Mesh&, Model* );
};
#endif

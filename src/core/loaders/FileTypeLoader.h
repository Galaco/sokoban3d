/*********************************************************************
Project: Dissertation
Author: Josh Martin

Name: File Type Loader
Description: Base class that all model format loaders inherit from.
*********************************************************************/
#ifndef FILETYPELOADER_H
#define FILETYPELOADER_H

#include <string>

#include <core/Logger.h>

#include <core/resources/Model.h>


class FileTypeLoader {
public:
	FileTypeLoader();
	~FileTypeLoader();
        
    virtual Model* load(std::string);

        
protected:
	virtual bool prepareMesh( Mesh&, Model* );
	virtual bool prepareNormals( Mesh&, Model* );
	Logger m_logger;
};
#endif

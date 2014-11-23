/*********************************************************************
Project: Dissertation
Author: Josh Martin

Name: Model Loader
Description: Responsible for determining filetype, and passing the 
			 loading to the correct filetype loader
*********************************************************************/
#ifndef MODELLOADER_H
#define MODELLOADER_H

#include <string>
#include <map>
#include <memory>
#include <core/Logger.h>

#include <core/loaders/ObjLoader.h>
#include <core/loaders/Md5Loader.h>

#include <core/resources/Model.h>


class ModelLoader {
public:
	ModelLoader();
	~ModelLoader();
        
    Model* load(std::string);

        
private:
	static ObjLoader	m_Obj;
	static Md5Loader	m_Md5;
};
#endif

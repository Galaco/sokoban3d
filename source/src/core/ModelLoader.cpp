#include "ModelLoader.h"

ObjLoader	ModelLoader::m_Obj;
Md5Loader	ModelLoader::m_Md5;

ModelLoader::ModelLoader(){

}

ModelLoader::~ModelLoader(){
    
}

Model* ModelLoader::load(std::string path){
	path = "assets/models/" + path;
	unsigned found = path.find_last_of(".");
	std::string filetype = path.substr(found+1, path.length()-found);

	std::transform(path.begin(), path.end(), path.begin(), ::tolower);
	return m_Obj.load(path);
}
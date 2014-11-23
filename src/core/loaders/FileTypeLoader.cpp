#include "FileTypeLoader.h"

FileTypeLoader::FileTypeLoader(){

}

FileTypeLoader::~FileTypeLoader(){
    
}

Model* FileTypeLoader::load(std::string path){
	Model* m = new Model;

	return m;
}


bool FileTypeLoader::prepareMesh( Mesh& mesh, Model* m ){
	return true;
}


bool FileTypeLoader::prepareNormals( Mesh& mesh, Model* m ){
	return true;
}
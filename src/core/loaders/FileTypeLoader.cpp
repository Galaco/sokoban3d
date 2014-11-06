#include "FileTypeLoader.h"

FileTypeLoader::FileTypeLoader(){

}

FileTypeLoader::~FileTypeLoader(){
    
}

Model* FileTypeLoader::load(std::string path){
	Model* m = new Model;

	return m;
}

// Compute the position of the vertices in object local space
// in the skeleton's bind pose
bool FileTypeLoader::prepareMesh( Mesh& mesh, Model* m ){
	return true;
}


// Compute the vertex normals in the Mesh's bind pose
bool FileTypeLoader::prepareNormals( Mesh& mesh, Model* m ){
	return true;
}
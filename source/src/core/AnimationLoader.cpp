#include "AnimationLoader.h"

AnimationLoader::AnimationLoader(){

}

AnimationLoader::~AnimationLoader(){
    
}

BaseAnimation* AnimationLoader::load(std::string path){
	path = "assets/models/" + path;
	unsigned found = path.find_last_of(".");
	std::string filetype = path.substr(found+1, path.length()-found);
	if (filetype == "md5anim") {
			MD5Animation* anim = new MD5Animation;
			anim->loadAnimation(path);

			return anim;
	}


	return nullptr;    
}
#ifndef ANIMATIONLOADER_H
#define ANIMATIONLOADER_H

#include <string>
#include <map>
#include <memory>
#include <core/Logger.h>

#include <core/resources/BaseAnimation.h>

#include <core/resources/MD5Animation.h>


class AnimationLoader {
public:
	AnimationLoader();
	~AnimationLoader();
        
    BaseAnimation* load(std::string);
private:
};
#endif

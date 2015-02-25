/*********************************************************************
Project: Dissertation
Author: Josh Martin

Name: Animation System
Description: System that updates animations on objects each frame.
*********************************************************************/
#ifndef SANIMATION_H
#define SANIMATION_H

#include <map>
#include <vector>



#include <core/System.h>

#include <core/resources/Mesh.h>
#include <core/resources/MD5Animation.h>

#include "../components/CAnimation.h"
#include "../components/CGraphics.h"


class SAnimation: public System {
public:
	SAnimation();
	~SAnimation();

	void initialize();
	
	void update(float);

private:
        void updateAnimation(CAnimation*, CGraphics*, float);
        void updateMesh(Model*, const MD5Animation::FrameSkeleton&);


		void rebuildCache();
		static std::map<CAnimation*, CGraphics*> CGraphicsCAnimationCache;
};
#endif

#include "CAnimation.h"

CAnimation::CAnimation(){
	m_type="Animation";
}


CAnimation::CAnimation(BaseAnimation* animation) {
	m_pAnimation = animation;
}

CAnimation::~CAnimation(){
	
}

void CAnimation::setAnimation(BaseAnimation* animation) {
	m_pAnimation = animation;
}

BaseAnimation* CAnimation::getAnimation() {
	return m_pAnimation;
}

void CAnimation::addAnimation(const char* path) {
	m_pAnimation = m_Resources.add<BaseAnimation>(path);
}
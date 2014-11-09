#include "SplashState.h"

SplashState::SplashState()
{
	priority = 100;

	Entity* e = new Entity("splashLogo");
	CGraphics* c = new CGraphics();
	c->addModel("data/resource/model/shapes/quad.obj");
	c->setRenderMode(RENDER_MODE_2D);
	c->addTexture("data/resource/materials/core/splash.jpg");
	e->addComponent(c, "Graphics");

	e->GetTransform()->setScale(glm::vec3(0.5, 0.5, 0.5));


	addEntity(e);
}

void SplashState::update(float dt = 0)
{
	m_runningTime += dt;
	if (m_runningTime >= 5){
		canDeprioritise() = true;
	}
}
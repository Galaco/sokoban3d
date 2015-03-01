#include "SplashState.h"

SplashState::SplashState()
{
	priority = 100;

	splash = new Entity("splashLogo");
	CGraphics* c = new CGraphics();
	c->addModel("shapes/quad.obj");
	c->setRenderMode(RENDER_MODE_2D);
	c->addMaterial("vgui/backgrounds/splash.mat");
	splash->addComponent(c, "Graphics");

	splash->GetTransform()->setScale(glm::vec3(0.2f / ((float)Config::_WINDOWWIDTH / (float)Config::_WINDOWHEIGHT), 0.2f, 1.f));
	splash->GetTransform()->setOrientation(glm::vec3(0.f, -90.f, 0.f));
	addEntity(splash);

	m_directionalLight = new DirectionalLight();
	m_directionalLight->AmbientIntensity = 0.f;
	m_directionalLight->Color = glm::vec3(1.f, 1.f, 1.f);
	m_directionalLight->DiffuseIntensity = 1.f;
	m_directionalLight->Direction = glm::vec3(1.0f, 0.0f, 0.0f);
}

void SplashState::update(float dt = 0)
{
	m_runningTime += dt;
	if (m_runningTime < 2.f && m_runningTime > 1.f)
	{
		splash->GetTransform()->getOrientation().y += (90* dt);
	}

	if (m_runningTime >= 4)
	{
		canDeprioritise() = true;
	}
}
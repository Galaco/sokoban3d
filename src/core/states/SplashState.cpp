#include "SplashState.h"

SplashState::SplashState()
{
	priority = 100;

	Entity* e = new Entity("splashLogo");
	CGraphics* c = new CGraphics();
	c->addModel("shapes/quad.obj");
	c->setRenderMode(RENDER_MODE_2D);
	c->addMaterial("vgui/backgrounds/splash.mat");
	e->addComponent(c, "Graphics");

	e->GetTransform()->setScale(glm::vec3(0.2f / ((float)Config::_WINDOWWIDTH / (float)Config::_WINDOWHEIGHT), 0.2f, 1.f));
	addEntity(e);

	m_directionalLight = new DirectionalLight();
	m_directionalLight->AmbientIntensity = 0.f;
	m_directionalLight->Color = glm::vec3(1.f, 1.f, 1.f);
	m_directionalLight->DiffuseIntensity = 1.f;
	m_directionalLight->Direction = glm::vec3(1.0f, 0.0f, 0.0f);
}

void SplashState::update(float dt = 0)
{
	m_runningTime += dt;
	if (m_runningTime < 1.5f && m_directionalLight->AmbientIntensity < 1.f)
	{
		m_directionalLight->AmbientIntensity += 1 * dt;
		if (m_directionalLight->AmbientIntensity > 1.f)
		{
			m_directionalLight->AmbientIntensity = 1.f;
		}
	}
	if (m_runningTime > 2.5f &&  m_directionalLight->AmbientIntensity > 0.f)
	{
		m_directionalLight->AmbientIntensity -= 1*dt;
		if (m_directionalLight->AmbientIntensity < 0.f)
		{
			m_directionalLight->AmbientIntensity = 0.f;
		}
	}

	if (m_runningTime >= 4)
	{
		canDeprioritise() = true;
	}
}
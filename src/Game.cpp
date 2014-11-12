#include "Game.h"

float Game::FRAMELENGTH = 16.667f;
StateManager Game::STATEMANAGER;

Game::Game(Engine& engine) : m_engine(engine)
{
	m_engine = engine;
	m_isRunning = true;

	m_Animation.initialize();
	m_Graphics.initialize();
	STATEMANAGER.initialize();

	SplashState * s = new SplashState;
	STATEMANAGER.addState(s, "Splash Screen");
}

Game::~Game()
{

}

void Game::update()
{
	m_frameTime = m_clock.getElapsedTime().asMilliseconds()/1000.f;
	if (FRAMELENGTH <= m_frameTime*1000) 
	{
		m_clock.restart();

		m_engine.update();
		STATEMANAGER.update(m_frameTime);
		handleInputs();
	}
	m_Graphics.update();
	glfwSwapBuffers(m_engine.getCurrentContext());
}

void Game::handleInputs()
{
	if (Keyboard::KEY_ESC) 
	{
		m_isRunning = false;
	}
}

bool Game::running()
{ 
    return m_isRunning; 
}
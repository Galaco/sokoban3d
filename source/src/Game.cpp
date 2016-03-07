#include "Game.h"

#define FRAMETIME 12 //works better than 0.01667?


bool Game::m_isRunning;
SceneManager Game::m_sceneManager;

Game::Game(Engine& engine) : m_engine(engine){
	m_engine = engine;
	m_elapsedTime = 0.f;
	m_isRunning = true;

	//Initialize Systems for Component/System architecture
	m_sGraphics.initialize();
	m_sAnimation.initialize();
	m_sScript.initialize();
	m_sCollision.initialize();
	m_sceneManager.initialize();

	
	SplashState* s = new SplashState;
	m_sceneManager.addState(s, "Splash");//Push splash to state manager

	//Run initialize script to create a game
	LuaScript* l = m_sScript.createScript();
	l->runFile("init.lua");	
	m_sScript.deleteScript(l);	//script no longer needed. Delete
}

Game::~Game(){
	m_sCollision.terminate();
	m_sScript.terminate();
	m_sAnimation.terminate();
	m_sGraphics.terminate();
}

void Game::update(){
	m_frameTime = (double)m_clock.getElapsedTime().asMilliseconds();
	if (m_frameTime > FRAMETIME)	//Keeps framerate at/below threshold
	{	
		m_frameTime /= 1000;		//frametime in milliseconds
		m_clock.restart();			//reset frametime


		m_engine.update();			//update core engine elements

		m_sceneManager.update((float)m_frameTime); //Update scenes
		m_sScript.update((float)m_frameTime);
		m_sAnimation.update((float)m_frameTime);
		m_sCollision.update((float)m_frameTime);
		m_sGraphics.update();

		handleInputs();
		System::FixedUpdate();

		glfwSwapBuffers(m_engine.getCurrentContext()); // swap buffers for render
	}
}

void Game::handleInputs()
{
	if (Keyboard::KEY_ESC) 
	{	//Force a quit out of the engine
		m_isRunning = false;
	}
}

bool Game::running()
{ 
    return m_isRunning; 
}

void Game::close()
{
	m_isRunning = false;
}
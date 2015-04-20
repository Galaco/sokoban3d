#include "Game.h"

#define FRAMETIME 12 //works better than 0.01667?


bool Game::m_isRunning;
SceneManager Game::m_sceneManager;

Game::Game(Engine& engine) : m_engine(engine){
	m_engine = engine;
	m_elapsedTime = 0.f;
	m_isRunning = true;

	//Initialize core systems
	m_sGraphics.initialize();
	m_sAnimation.initialize();
	m_sScript.initialize();
	m_sCollision.initialize();
	m_sceneManager.initialize();

	//Push splash to state manager
	SplashState* s = new SplashState;
	m_sceneManager.addState(s, "Splash");

	//Run 
	LuaScript* l = m_sScript.createScript();
	l->runFile("init.lua");	
	m_sScript.deleteScript(l);
}

Game::~Game(){
	m_sCollision.terminate();
	m_sScript.terminate();
	m_sAnimation.terminate();
	m_sGraphics.terminate();
}

void Game::update(){
	m_frameTime = (double)m_clock.getElapsedTime().asMilliseconds();
	if (m_frameTime > FRAMETIME) {
		m_frameTime /= 1000;
		m_clock.restart();


		m_engine.update();

		m_sceneManager.update((float)m_frameTime);
		// update systems
		m_sScript.update((float)m_frameTime);
		m_sAnimation.update((float)m_frameTime);
		m_sCollision.update((float)m_frameTime);

		// render
		m_sGraphics.update();
		// swap buffers for render

		handleInputs();
		System::FixedUpdate();

		glfwSwapBuffers(m_engine.getCurrentContext());
	}

	
}

void Game::handleInputs(){
	if (Keyboard::KEY_ESC) {	//Force a quit out of the engine
		m_isRunning = false;
	}
}

bool Game::running(){ 
    return m_isRunning; 
}

void Game::close(){
	m_isRunning = false;
}
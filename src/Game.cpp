#include "Game.h"

float Game::m_FRAMELENGTH = 16.667f;
StateManager Game::m_stateManager;

Game::Game(Engine& engine) : m_engine(engine){
	m_engine = engine;
	m_elapsedTime = 0.f;
	m_isRunning = true;

	//Initialize core systems
	m_sGraphics.initialize();
	m_sAnimation.initialize();
	m_sLuaScript.initialize();
	m_stateManager.initialize();

	//Push splash to state manager
	SplashState* s = new SplashState;
	m_stateManager.addState(s, "Splash");

	//Run 
	LuaScript* l = m_sLuaScript.createScript();
	l->runFile("init.lua");	
	m_sLuaScript.deleteScript(l);
}

Game::~Game(){
	m_sLuaScript.terminate();
	m_sAnimation.terminate();
	m_sGraphics.terminate();
}

void Game::update(){
	m_frameTime = m_clock.getElapsedTime().asMilliseconds()/1000.f;
	if (m_frameTime*1000 >= m_FRAMELENGTH) {
		m_clock.restart();

		m_engine.update();
		m_stateManager.update(m_frameTime);
		handleInputs();

		// update systems
		m_sAnimation.update(m_frameTime);
		m_sLuaScript.update(m_frameTime);
	}

	// render
	m_sGraphics.update();
	// swap buffers for render
	glfwSwapBuffers(m_engine.getCurrentContext());
}

void Game::handleInputs(){
	if (Keyboard::KEY_ESC) {	//Force a quit out of the engine
		m_isRunning = false;
	}
}

bool Game::running(){ 
    return m_isRunning; 
}
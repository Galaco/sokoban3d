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


	fps_count = 0;
	fps_timer = 0;
}

Game::~Game(){
	m_sLuaScript.terminate();
	m_sAnimation.terminate();
	m_sGraphics.terminate();
}

void Game::update(){
	m_frameTime = m_clock.getElapsedTime().asMilliseconds()/1000.f;
	//if (m_frameTime*1000 >= m_FRAMELENGTH) {
		m_clock.restart();


		m_engine.update();

		// update systems
		m_sAnimation.update(m_frameTime);
		m_sLuaScript.update(m_frameTime);

		m_stateManager.update(m_frameTime);

		handleInputs();
	//}

	// render
	m_sGraphics.update();
	// swap buffers for render
	glfwSwapBuffers(m_engine.getCurrentContext()); 
	
	fps_timer += m_frameTime;
	fps_count++;
	if (fps_timer >= 1.f){
		std::cout << "Average frame time: " << (fps_timer/fps_count)*1000 << "ms" << std::endl;
		std::cout << "Frames per second: " << fps_count << std::endl;
		fps_count = 0;
		fps_timer = 0;
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
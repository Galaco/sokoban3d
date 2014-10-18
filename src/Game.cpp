#include "Game.h"

float Game::FRAMELENGTH = 16.667f;

Game::Game(Engine& engine) : m_engine(engine){
	m_engine = engine;
	m_isRunning = true;
}

Game::~Game(){
}

void Game::update(){
	m_frameTime = m_clock.getElapsedTime().asMilliseconds()/1000.f;
	if (FRAMELENGTH <= m_frameTime*1000) {
		m_clock.restart();

		m_engine.update();
		handleInputs();
	}
	glfwSwapBuffers(m_engine.getCurrentContext());
}

void Game::handleInputs(){
	if (Keyboard::KEY_ESC) {
		m_isRunning = false;
	}
}

bool Game::running(){ 
    return m_isRunning; 
}
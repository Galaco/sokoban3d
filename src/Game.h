#ifndef GAME_H
#define GAME_H

#include <map>

#include <core/Engine.h>
#include <GLFW/glfw3.h>

#include <SFML/System.hpp>
#include "systems/SAnimation.h"
#include "systems/SGraphics.h"


#include <core/StateManager.h>
#include <core/states/SplashState.h>


class Game {
public:
	Game(Engine&);
	~Game();

	bool running();

	void update();


private:
	void handleInputs();
               
	bool m_isRunning;
    float m_elapsedTime, m_frameTime;
	static float FRAMELENGTH;


	Engine& m_engine;
    sf::Clock m_clock;


	SAnimation		m_Animation;
	SGraphics		m_Graphics;
	static StateManager STATEMANAGER;
};
#endif

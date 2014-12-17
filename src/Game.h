/*********************************************************************
Project: Dissertation
Author: Josh Martin

Name: Game
Description: Contains the main game loop. Responsible for System & 
			 script initialisations.
*********************************************************************/
#ifndef GAME_H
#define GAME_H

#include <map>

#include <core/Engine.h>
#include <GLFW/glfw3.h>

#include <SFML/System.hpp>

#include <core/StateManager.h>
#include <core/states/SplashState.h>

#include "systems/SGraphics.h"
#include "systems/SAnimation.h"
#include "systems/SLuaScript.h"

#include <core/resources/LuaScript.h>


class Game {
public:
	Game(Engine&);
	~Game();

	bool running();

	void update();

	static void close();

private:
	void handleInputs();
        
        
	static bool m_isRunning;
    double m_elapsedTime, m_frameTime;

	Engine& m_engine;
    sf::Clock m_clock;
        
	//Systems
	SGraphics		m_sGraphics;
	SAnimation      m_sAnimation;
    SLuaScript      m_sLuaScript;

    static double m_FRAMELENGTH;
	static StateManager m_stateManager;
};
#endif

#ifndef GAME_H
#define GAME_H

#include <map>

#include <core/Engine.h>
#include <GLFW/glfw3.h>

#include <SFML/System.hpp>


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

	Engine& m_engine;
    sf::Clock m_clock;

    static float FRAMELENGTH;
};
#endif

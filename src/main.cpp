#include <core/Engine.h>
#include "Game.h"


int main()
{
	Engine engine;
	engine.initialize();

	Game game(engine);

	while(game.running()){
		game.update();
	}
	

	glfwTerminate();

    return EXIT_SUCCESS;
}

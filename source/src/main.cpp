#ifdef SFML_STATIC	//Allow SFML 2.1 to link statically on VS2013
#pragma comment(lib, "freetype.lib")
#pragma comment(lib, "jpeg.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "gdi32.lib")  
#endif

#include <core/Engine.h>
#include "Game.h"


int main()
{
	//Initialize engine
	Engine engine;
	engine.initialize();

	//Create game for game loop
	Game game(engine);

	// The main loop
	while(game.running())
	{
		game.update();
	}
	

	//Exit
	glfwTerminate();

    return EXIT_SUCCESS;
}

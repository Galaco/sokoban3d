#ifdef SFML_STATIC	//Allows SFML 2.1 to link statically on VS2013
#pragma comment(lib, "freetype.lib")
#pragma comment(lib, "jpeg.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "gdi32.lib")  
#endif


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

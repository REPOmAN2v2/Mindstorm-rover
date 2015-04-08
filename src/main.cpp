#include "map.hpp"
#include "robot.hpp"
#ifdef SDL_SUPPORT
	#include "sdl.hpp"
#endif
#include <iostream>

int main (int argc, char *argv[])
{
	Map map(25,10);
	Robot robot(map);

	#ifdef SDL_SUPPORT

	try {
		SDL::init();
		SDL::Window window(250,100,"Rover");
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				std::cout << "Escape event received" << std::endl;
				break;
			}
		}
	} catch (...) {
		SDL::exit();
		return -1;
	}

	#else

	map.displayDebug();
	robot.explore(map);

	std::cin.get();

	#endif

	return 0;
}
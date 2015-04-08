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
		while (1) {
			SDL_Event event;
			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_QUIT) {
					std::cout << "Quit event received" << std::endl;
					return 0;
				}
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
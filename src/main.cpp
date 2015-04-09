#include "map.hpp"
#include "robot.hpp"
#include "display.hpp"
#ifdef SDL_SUPPORT
	#include "sdl.hpp"
#endif
#include <iostream>

/**
 * Note: argc and argv seemed to be needed for proper compilation with SDL
 * We don't use them, so simply removing the variable names eliminates
 * -Wunused-parameter warnings during compilation.
 */
int main(int, char **)
{
	Map map(25,10);
	Robot robot(map);

	#ifdef SDL_SUPPORT

	try {
		SDL::init();
		SDL::Window window(25*Cell::h, 10*Cell::w, "Rover");
		drawDebug(map, window);

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

	drawDebug(map);
	robot.explore(map);

	std::cin.get();

	#endif

	return 0;
}
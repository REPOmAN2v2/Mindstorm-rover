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
		SDL::Keyboard keyboard;

		// show the full map once
		drawDebug(map, window);
		keyboard.waitFor(SDL_KEYDOWN);

		// show the unexplored map
		draw(map, window);
		keyboard.waitFor(SDL_KEYDOWN);

		// explore and show the explored map
		robot.explore(map);
		draw(map, window);
		keyboard.waitFor(SDL_QUIT);
	} catch (...) {
		SDL::exit();
		return -1;
	}

	#else

	drawDebug(map);
	robot.explore(map);
	draw(map);

	std::cin.get();

	#endif

	return 0;
}
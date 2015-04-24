#include "map.hpp"
#include "robot.hpp"
#include "display.hpp"
#ifdef SDL_SUPPORT
	#include "sdl.hpp"
#else
	#include <iostream>
#endif

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
		Display display(window);

		robot.explore(map);
		//robot.goTo(map, map.getDest());

		while (!map.history.empty()) {
			display.draw(map, map.history.front());
			map.history.pop();
			keyboard.waitFor(SDL_KEYDOWN);
		}

		keyboard.waitFor(SDL_QUIT);

	} catch (...) {
		SDL::exit();
		return -1;
	}

	#else

	Display display;

	robot.explore(map);

	while (!map.history.empty()) {
		display.draw(map, map.history.front());
		map.history.pop();
		std::cin.get();
	}

	std::cin.get();

	#endif

	return 0;
}
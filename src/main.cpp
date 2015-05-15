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
	Map map(25,10); // Generates a map (width, height)
	Robot robot(map);

	// SDL
	#ifdef SDL_SUPPORT

	try {
		SDL::init();
		SDL::Window window(25*Cell::h, 10*Cell::w, "Rover");
		SDL::Keyboard keyboard;
		Display display(window);

		/**
		 * Finds the shortest path between the robot and a destination.
		 * map.getDest() generates a random, valid (ie not an obstacle)
		 * destination.
		*/
		robot.goTo(map, map.getDest());

		/**
		 * While exploring the map, every time the robot moves, we save the
		 * state of the map in a vector. This lets us generate the path first
		 * then display it progressively in our own time.
		 */
		while (!map.history.empty()) {
			display.draw(map, map.history.front());
			map.history.pop();
			keyboard.waitFor(SDL_KEYDOWN);
		}

		keyboard.waitFor(SDL_QUIT);

	} catch (...) {
		// Catch any exception we may throw during SDL initialisation.
		SDL::exit();
		return -1;
	}

	// CLI program
	#else

	Display display;

	//robot.explore(map);
	robot.goTo(map, map.getDest());

	while (!map.history.empty()) {
		display.draw(map, map.history.front());
		map.history.pop();
		std::cin.get();
	}

	std::cin.get();

	#endif

	return 0;
}
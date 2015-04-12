#ifndef DISPLAY_HPP_INCLUDED
#define DISPLAY_HPP_INCLUDED

#include "map.hpp"

#ifdef SDL_SUPPORT
#include "sdl.hpp"
#endif

/*void draw(Map map, SDL::Window &window);
void drawDebug(Map map, SDL::Window &window);*/



class Display {
public:
	void draw(Map map, std::vector< std::vector< Cell > > &cells);
	void drawDebug(Map map, std::vector< std::vector< Cell > > &cells);

#ifdef SDL_SUPPORT
	Display(SDL::Window &window) : window(window) {};
private:
	SDL::Window &window;
#endif
};

#endif
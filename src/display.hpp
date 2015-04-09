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
	void draw(Map map);
	void drawDebug(Map map);

#ifdef SDL_SUPPORT
	Display(SDL::Window &window) : window(window) {};
private:
	SDL::Window &window;
#endif
};

#endif
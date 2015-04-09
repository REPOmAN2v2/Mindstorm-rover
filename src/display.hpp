#ifndef DISPLAY_HPP_INCLUDED
#define DISPLAY_HPP_INCLUDED

#include "map.hpp"

#ifdef SDL_SUPPORT
#include "sdl.hpp"

void draw(Map map, SDL::Window &window);
void drawDebug(Map map, SDL::Window &window);

#else

void draw(Map map);
void drawDebug(Map map);

#endif

#endif
#include <iostream>
#include "display.hpp"

#ifdef SDL_SUPPORT

using namespace SDL;

/**
 * Draws the map using SDL.
 *
 * Takes a map object and a reference to the 2D vector of cells inside the
 * map (could be improved). Returns void.
 *
 * This simply iterates over the vector of cells and, depending on the type
 * of the cell, draws a rectangle of a certain colour.
 */
void Display::draw(Map map, std::vector< std::vector< Cell > > &cells)
{
	Color red(255,0,0);
	Color black(0,0,0);
	Color white(255,255,255);
	Color grey(130,130,130);
	Color green(0,255,0);

	window.clear();

	for (size_t y = 0; y < map.height(); ++y) {
		for (size_t x = 0; x < map.width(); ++x) {
			SDL_Rect rect = {.x=Cell::w*x, .y=Cell::h*y,
						.w=Cell::w, .h=Cell::h};

			if (cells[y][x].robot) {
				window.drawRect(rect, red);
			} else if (cells[y][x].dest) {
				window.drawRect(rect, green);
			} else if (!cells[y][x].visible) {
				window.drawRect(rect, black);
			} else {
				if (!cells[y][x].obstacle) {
					window.drawRect(rect, white);
				} else {
					window.drawRect(rect, grey);
				}
			}
		}
	}

	window.refresh();
}

void Display::drawDebug(Map map, std::vector< std::vector< Cell > > &cells)
{
	Color red(255,0,0);
	Color white(255,255,255);
	Color grey(130,130,130);
	Color green(0,255,0);

	window.clear();

	for (size_t y = 0; y < map.height(); ++y) {
		for (size_t x = 0; x < map.width(); ++x) {
			SDL_Rect rect = {.x=Cell::w*x, .y=Cell::h*y,
						.w=Cell::w, .h=Cell::h};

			if (cells[y][x].robot) {
				window.drawRect(rect, red);
			} else if (cells[y][x].dest) {
				window.drawRect(rect, green);
			} else if (!cells[y][x].obstacle) {
				window.drawRect(rect, white);
			} else {
				window.drawRect(rect, grey);
			}
		}
	}

	window.refresh();
}

#else

/**
 * Draws the map to the terminal.
 *
 * Takes a map object and a reference to the 2D vector of cells inside the
 * map (could be improved). Returns void.
 *
 * This simply iterates over the vector of cells and, depending on the type
 * of the cell, prints a specific character.
 */
void Display::draw(Map map, std::vector< std::vector< Cell > > &cells)
{
	for (size_t y = 0; y < map.height(); ++y) {
		for (size_t x = 0; x < map.width(); ++x) {

			if (cells[y][x].robot) {
				std::cout << 'O';
			} else if (cells[y][x].dest) {
				std::cout << 'X';
			} else if (!cells[y][x].visible) {
				std::cout << '?';
			} else {
				if (!cells[y][x].obstacle) {
					std::cout << '.';
				} else {
					std::cout << '#';
				}
			}
		}

		std::cout << std::endl;
	}

	std::cout << std::endl;
}

void Display::drawDebug(Map map, std::vector< std::vector< Cell > > &cells)
{
	for (size_t y = 0; y < map.height(); ++y) {
		for (size_t x = 0; x < map.width(); ++x) {

			if (!cells[y][x].obstacle) {
				std::cout << '.';
			} else {
				std::cout << '#';
			}
		}

		std::cout << std::endl;
	}

	std::cout << std::endl;
}

#endif
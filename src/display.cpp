#include <iostream>
#include "display.hpp"

#ifdef SDL_SUPPORT

using namespace SDL;

void draw(Map map, Window &window)
{
	Color red(255,0,0);
	Color black(0,0,0);
	Color white(255,255,255);
	Color grey(130,130,130);

	window.clear();

	for (size_t y = 0; y < map.height(); ++y) {
		for (size_t x = 0; x < map.width(); ++x) {
			Cell cell = map.getCell(y,x);
			SDL_Rect rect = {.x=Cell::w*x, .y=Cell::h*y,
						.w=Cell::w, .h=Cell::h};

			if (cell.robot) {
				window.drawRect(rect, red);
			} else if (!cell.visible) {
				window.drawRect(rect, black);
			} else {
				if (!cell.obstacle) {
					window.drawRect(rect, white);
				} else {
					window.drawRect(rect, grey);
				}
			}
		}
	}

	window.refresh();
}

void drawDebug(Map map, Window &window)
{
	Color white(255,255,255);
	Color grey(130,130,130);

	window.clear();

	for (size_t y = 0; y < map.height(); ++y) {
		for (size_t x = 0; x < map.width(); ++x) {
			Cell cell = map.getCell(y,x);
			SDL_Rect rect = {.x=Cell::w*x, .y=Cell::h*y,
						.w=Cell::w, .h=Cell::h};

			if (!cell.obstacle) {
				window.drawRect(rect, white);
			} else {
				window.drawRect(rect, grey);
			}
		}
	}

	window.refresh();
}

#else

void draw(Map map)
{
	for (size_t y = 0; y < map.height(); ++y) {
		for (size_t x = 0; x < map.width(); ++x) {
			Cell cell = map.getCell(y,x);

			if (cell.robot) {
				std::cout << 'O';
			} else if (!cell.visible) {
				std::cout << '?';
			} else {
				if (!cell.obstacle) {
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

void drawDebug(Map map)
{
	for (size_t y = 0; y < map.height(); ++y) {
		for (size_t x = 0; x < map.width(); ++x) {
			Cell cell = map.getCell(y,x);

			if (!cell.obstacle) {
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
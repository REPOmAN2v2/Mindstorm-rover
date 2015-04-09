#ifndef CELL_HPP_INCLUDED
#define CELL_HPP_INCLUDED

#include <cstddef>

class Cell {
public:
	bool visible;
	bool obstacle;
	bool robot;
	static size_t const h = 10, w = 10;
	Cell();
private:
	int x, y;
};

#endif
#ifndef CELL_HPP_INCLUDED
#define CELL_HPP_INCLUDED

#include <cstddef>

class Cell {
public:
	bool visible;
	bool obstacle;
	bool robot;
	Cell();
private:
	int x, y;
	static size_t const h = 5, w = 5;
};

#endif
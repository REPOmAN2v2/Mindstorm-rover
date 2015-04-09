#ifndef CELL_HPP_INCLUDED
#define CELL_HPP_INCLUDED

#include <cstddef>

class Cell {
public:
	bool visible;
	bool obstacle;
	bool robot;
	static unsigned int const h = 10, w = 10;
	Cell();
private:
	int x, y;
};

#endif
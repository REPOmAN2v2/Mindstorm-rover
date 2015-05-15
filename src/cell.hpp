#ifndef CELL_HPP_INCLUDED
#define CELL_HPP_INCLUDED

#include <cstddef>
#include <vector>

class Cell {
public:
	bool visible;
	bool obstacle;
	bool robot;
	bool dest;
	// Size of the individual cells (useful for drawing the map graphically)
	static unsigned int const h = 10, w = 10;
	Cell();
private:
};

#endif
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
	static unsigned int const h = 10, w = 10;
	Cell();
private:
};

#endif
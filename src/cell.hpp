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
	int prev, x, y, distEstimate;
	static unsigned int const h = 10, w = 10;
	Cell();
	bool invalid(std::vector < Cell* > check, size_t h, size_t w);
	void setDistances(std::pair <int, int> dest);
private:
};

#endif
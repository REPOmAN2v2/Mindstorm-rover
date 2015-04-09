#ifndef MAP_HPP_INCLUDED
#define MAP_HPP_INCLUDED

#include <vector>
#include <utility>
#include "cell.hpp"

class Map {
public:
	std::vector< std::vector< Cell > > cells;
	Map();
	explicit Map(int);
	explicit Map(int, int);
	Cell getCell(size_t y, size_t x);
	void updateRobotPos(std::pair<int,int> oldPos, std::pair<int,int> newPos);
	size_t height() {return vCells;};
	size_t width() {return hCells;};
private:
	size_t hCells, vCells;
	void generateMaze();
};

#endif
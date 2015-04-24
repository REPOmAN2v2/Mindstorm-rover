#ifndef MAP_HPP_INCLUDED
#define MAP_HPP_INCLUDED

#include <vector>
#include <utility>
#include <queue>
#include "cell.hpp"

class Map {
public:
	std::vector< std::vector< Cell > > cells;
	std::queue< std::vector< std::vector< Cell > > > history;
	Map();
	explicit Map(int);
	explicit Map(int, int);
	Cell getCell(size_t y, size_t x);
	void updateRobotPos(std::pair<int,int> oldPos, std::pair<int,int> newPos);
	bool validCoord(int y, int x) {return !(y < 0 || x < 0 || y >= vCells || x >= hCells);};
	std::pair<int,int> getDest();
	size_t height() {return vCells;};
	size_t width() {return hCells;};
private:
	size_t hCells, vCells;
	void generateMaze();
};

#endif

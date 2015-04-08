#ifndef MAP_HPP_INCLUDED
#define MAP_HPP_INCLUDED

#include <vector>
#include <utility>
#include "cell.hpp"

class Map {
public:
	const size_t hCells, vCells;
	std::vector< std::vector< Cell > > cells;
	Map();
	void display() const;
	void displayDebug() const;
	void updateRobotPos(std::pair<int,int> oldPos, std::pair<int,int> newPos);
private:
};

#endif
#ifndef ROBOT_HPP_INCLUDED
#define ROBOT_HPP_INCLUDED

#include <vector>
#include "map.hpp"

enum Directions {WEST, NORTH, EAST, SOUTH};

class Robot  {
public:
	explicit Robot(Map &map);
	void explore(Map &map);
	void goTo(Map &map, std::pair<int, int> dest);
	void step(Map &map, std::pair<int, int> dest);
	void astarFindNeighbours(Map &map, Cell cell);
	//bool compareCells(const Cell *a, const Cell *b);
	void checkNeighbour(Map map, Cell *cell, int prev);
private:
	int x, y;
	Directions direction;
	std::vector < Cell* > open, visited, path;
	void findNeighbours(std::vector < std::pair <int, int> > &neighbours) const;
	void move(std::pair <int, int> coord, Map &map);
};

#endif
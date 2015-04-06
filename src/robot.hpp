#ifndef ROBOT_HPP_INCLUDED
#define ROBOT_HPP_INCLUDED

#include <vector>
#include <list>
#include "map.hpp"

enum Directions {WEST, NORTH, EAST, SOUTH};

class Robot  {
public:
	int x, y;
	Robot(int h, int w, std::vector <std::vector <Cell> > &cells);
	void explore(Map &map);
private:
	Directions direction;
	void findNeighbours(std::vector < std::pair <int, int> > &neighbours);
	void exploreRoutine(Map &map, std::list < std::pair < int, int> > &visited);
	void move(std::pair <int, int> coord, Map &map);
};

#endif
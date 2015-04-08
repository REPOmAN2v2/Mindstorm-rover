#ifndef ROBOT_HPP_INCLUDED
#define ROBOT_HPP_INCLUDED

#include <vector>
#include "map.hpp"

enum Directions {WEST, NORTH, EAST, SOUTH};

class Robot  {
public:
	explicit Robot(Map &map);
	void explore(Map &map);
private:
	int x, y;
	Directions direction;
	void findNeighbours(std::vector < std::pair <int, int> > &neighbours) const;
	void exploreRoutine(Map &map, std::vector < std::pair < int, int> > &visited);
	void move(std::pair <int, int> coord, Map &map);
};

#endif
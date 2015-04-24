#ifndef ROBOT_HPP_INCLUDED
#define ROBOT_HPP_INCLUDED

#include <vector>
#include <array>
#include <map>
#include "map.hpp"

typedef std::pair<int,int> Coords;
static const std::array<Coords, 4> dirs = {Coords{0, 1}, Coords{-1, 0},Coords{0, -1}, Coords{1, 0}};


class Robot  {
public:
	explicit Robot(Map &map);
	void explore(Map &map);
	void goTo(Map &map, Coords dest);
private:
	int _x, _y;
	std::map<Coords, bool> visited;
	std::vector<Coords > getNeighbours(Map &map, std::pair<int, int> current, std::map<Coords, bool> visited);
	void move(Coords coord, Map &map);
	float heuristic(Coords current, Coords goal);
	void constructPath(Map &map, Coords start, Coords goal, std::map<Coords, Coords> came_from);
};

#endif
#ifndef ROBOT_HPP_INCLUDED
#define ROBOT_HPP_INCLUDED

#include <vector>
#include <array>
#include <map>
#include "map.hpp"

typedef std::pair<int,int> Coords;
// The four directions we can move to, stored as deltas
static const std::array<Coords, 4> dirs = {Coords{0, 1}, Coords{-1, 0},Coords{0, -1}, Coords{1, 0}};


class Robot  {
public:
	explicit Robot(Map &map);
	void explore(Map &map);
	void goTo(Map &map, Coords dest);
private:
	int _x, _y; // internal position of the robot
	std::vector<Coords > getNeighbours(Map &map, std::pair<int, int> current, std::map<Coords, bool> visited);
	void DFS(Map &map, std::map<Coords, bool> &visited);
	void move(Coords coord, Map &map);
	int heuristic(Coords current, Coords goal);
	void constructPath(Map &map, Coords start, Coords goal, std::map<Coords, Coords> came_from);
};

#endif

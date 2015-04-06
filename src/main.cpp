#include "map.hpp"
#include "robot.hpp"
#include <iostream>

int main ()
{
	Map map;
	Robot robot(map.vCells, map.hCells, map.cells);

	map.displayDebug();
	robot.explore(map);

	std::cin.get();
}
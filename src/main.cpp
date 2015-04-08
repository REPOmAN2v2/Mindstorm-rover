#include "map.hpp"
#include "robot.hpp"
#include <iostream>

int main ()
{
	Map map(25,10);
	Robot robot(map);

	map.displayDebug();
	robot.explore(map);

	std::cin.get();
}
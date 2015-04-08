#include "robot.hpp"
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <stdexcept>

/**
 * Robot Constructor.
 *
 * Takes the value of the height and width of the map as well as a reference
 * to the vector of cells inside the map object.
 *
 * It generates a random start point for the robot on a valid (free of
 * obstacles) cell.
 */

Robot::Robot(int h, int w, std::vector <std::vector <Cell> > &cells)
{
	srand(time(NULL));

	do {
		y = rand()%h;
		x = rand()%w;
	} while (cells[y][x].obstacle == true);

	cells[y][x].robot = true;
}

/**
 * Call for the exploration routine of the robot.
 *
 * Takes a reference to the map. Returns void.
 *
 * This method creates the vector of visited coordinates then calls the real
 * exploration routine.
 */

void Robot::explore(Map &map)
{
	std::vector < std::pair < int, int> > visited;
	exploreRoutine(map, visited);
}

/**
 * Exploration routine.
 *
 * Takes a reference to the map as well as to the vector of visited cells.
 * Returns void.
 *
 * This method uses a basic Depth-First Search. It adds the current position
 * to the visited vector then finds the four immediate neighbours. It then
 * looks at each neighbour one after the other, marking them as visible as it
 * goes. If the neighbour is an obstacle, it is skipped, else we check if it
 * has already been visited. If it hasn't, we move on the neighbour and call
 * this routine recursively with this new position.
 * When the routine returns, we move back to the original position and explore
 * the remaining (if any) neighbours, until every branch has been explored.
 */

void Robot::exploreRoutine(Map &map, std::vector < std::pair < int, int> > &visited)
{
	std::vector < std::pair <int, int> > neighbours;
	std::pair <int,int> orig(y, x);

	visited.push_back(std::make_pair(y, x));
	findNeighbours(neighbours);

	for (size_t i = 0; i < 4; ++i) {
		try {
			map.cells.at(neighbours[i].first).at(neighbours[i].second).visible = true;
		} catch (const std::out_of_range& e) {
			continue; // neighbour is out of range, we can just move on
		}

		if (map.cells[neighbours[i].first][neighbours[i].second].obstacle) {
			continue;
		}

		std::vector<std::pair<int, int> >::iterator iter = std::find(visited.begin(), visited.end(), neighbours[i]);

		if (iter == visited.end()) { // i.e. neighbour not yet visited
			map.display();
			move(neighbours[i], map);
			exploreRoutine(map, visited);
			move(orig, map);
		}
	}
}

/** Find our four immediate neighbours (ignoring diagonals).
 *
 * Takes a reference to a vector of pairs of coordinates, which it then fills.
 * Returns void.
 */

void Robot::findNeighbours(std::vector < std::pair <int, int> > &neighbours) const
{
	neighbours.push_back(std::make_pair(y, x - 1));
	neighbours.push_back(std::make_pair(y + 1, x));
	neighbours.push_back(std::make_pair(y, x + 1));
	neighbours.push_back(std::make_pair(y - 1, x));
}

/** Moves the robot
 *
 * Takes a pair of coordinates to move to and a reference to the map. returns
 * void.
 *
 * This updates the robot's positon on the map then updates the robot's
 * internal coordinates.
 */

void Robot::move(std::pair <int, int> coord, Map &map)
{
	map.updateRobotPos(std::make_pair(y,x), coord);
	y = coord.first;
	x = coord.second;
}
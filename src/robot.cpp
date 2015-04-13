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

Robot::Robot(Map &map)
{
	do {
		y = rand()%map.height();
		x = rand()%map.width();
	} while (map.cells[y][x].obstacle == true);

	map.cells[y][x].robot = true;
	map.history.push(map.cells);
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

/*void Robot::explore(Map &map)
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
			move(neighbours[i], map);
			map.history.push(map.cells);
			explore(map);
			move(orig, map);
			map.history.push(map.cells);
		}
	}
}*/

/**
 * A* implementation
 */

 void Robot::goTo(Map &map, std::pair<int, int> dest)
 {
 	//std::vector<Cell&> open, visited, path;
 	open.clear();
 	visited.clear();

 	map.cells[dest.first][dest.second].prev = 1;
 	map.cells[dest.first][dest.second].dest = true;

 	for (size_t j = 0; j < map.height(); ++j) {
 		for (size_t i = 0; i < map.width(); ++i) {
 			map.cells[j][i].setDistances(dest);
 		}
 	}

 	open.push_back(&map.cells[y][x]);
 	step(map, dest);
 }

 /**
  * Pick best unvisited open node
  */

 void Robot::step(Map &map, std::pair<int, int> dest)
 {
 	Cell *cell;
 	std::pair<int,int> orig(y,x);

 	do {
 		cell = open.back();
 		cell->visible = true;
 		open.pop_back();
 	} while (cell->invalid(visited, map.height(), map.width()));

 	move(std::make_pair(cell->y, cell->x), map);
 	map.history.push(map.cells);

 	if (cell->y == dest.first && cell->x == dest.second) {
 		return;
 	}

 	visited.push_back(cell);
 	astarFindNeighbours(map, *cell);
 	if (open.empty()) {
 		return;
 	}

 	step(map, dest);
}

bool compareCells(const Cell *a, const Cell *b)
{
	if (a->prev + a->distEstimate == b->prev + b->distEstimate) {
		return a->prev < b->prev;
	}

	return a->prev + a->distEstimate > b->prev + b->distEstimate;
}

void Robot::astarFindNeighbours(Map &map, Cell cell)
{
	if (map.validCoord(y, x-1))
		checkNeighbour(map, &map.cells[cell.y][cell.x - 1], cell.prev);
	if (map.validCoord(y+1, x))
		checkNeighbour(map, &map.cells[cell.y + 1][cell.x], cell.prev);
	if (map.validCoord(y, x+1))
		checkNeighbour(map, &map.cells[cell.y][cell.x + 1], cell.prev);
	if (map.validCoord(y-1, x))
		checkNeighbour(map, &map.cells[cell.y - 1][cell.x], cell.prev);
	std::sort(open.begin(), open.end(), compareCells);
}

void Robot::checkNeighbour(Map map, Cell *cell, int prev)
{
	cell->visible = true;
	if (!cell->invalid(visited, map.height(), map.width())) {
		for (size_t i = 0; i < open.size(); ++i) {
			if (cell->y == open[i]->y && cell->x == open[i]->x) {
				return;
			}
		}

		cell->prev = prev + 1;
		open.push_back(cell);
	}
}

/**
 * Find our four immediate neighbours (ignoring diagonals).
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

/**
 * Moves the robot
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
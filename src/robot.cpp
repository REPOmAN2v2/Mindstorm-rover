#include "robot.hpp"
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <utility>

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
		_y = rand()%map.height();
		_x = rand()%map.width();
	} while (map.cells[_y][_x].obstacle == true);

	map.cells[_y][_x].robot = true;
	map.cells[_y][_x].visible = true;
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

void Robot::explore(Map &map)
{
	Coords start(_y, _x);
	visited[start] = true;

	std::vector<Coords > neighbours = getNeighbours(map, start, visited);

	for (std::vector<Coords >::iterator neighbour = neighbours.begin(); neighbour != neighbours.end(); ++neighbour) {

		move(*neighbour, map);
		map.history.push(map.cells);
		explore(map);
		move(start, map);
		map.history.push(map.cells);
	}
}

float Robot::heuristic(Coords current, Coords goal)
{
	int y1 = current.first;
	int x1 = current.second;
	int y2 = goal.first;
	int x2 = goal.second;
	float p = 1/2.50;
	return (abs(x1 - x2) + abs(y1 - y2)) * (1.0 + p);
}


std::vector<Coords > Robot::getNeighbours(Map &map, std::pair<int, int> current, std::map<Coords, bool> visited)
 {
	int x, y, dx, dy;
	y = current.first;
	x = current.second;
	std::vector<Coords > results;

	for (int i = 0; i < 4; ++i) {
		dy = dirs[i].first;
		dx = dirs[i].second;

		Coords next(y + dy, x + dx);
		if (map.validCoord(next.first, next.second)) {
			map.cells[next.first][next.second].visible = true;

			if (!map.cells[next.first][next.second].obstacle && !visited[next]) {
				results.push_back(next);
			}
		}
    }

    if ((x + y) % 2 == 0) {
      // aesthetic improvement on square grids
      std::reverse(results.begin(), results.end());
    }

    return results;
 }

void Robot::constructPath(Map &map, Coords start, Coords goal, std::map<Coords, Coords> came_from)
{
	Coords current = goal;
	map.cells[current.first][current.second].dest = true;
	while (current != start) {
		current = came_from[current];
		map.cells[current.first][current.second].dest = true;
	}
	map.history.push(map.cells);
}


 void Robot::goTo(Map &map, std::pair<int, int> dest)
 {
 	Coords start(_y, _x);

	std::priority_queue<std::pair<float,Coords>, std::vector<std::pair<float,Coords> >, std::greater<std::pair<float,Coords> > > open;
	open.emplace(0, start);

	map.cells[dest.first][dest.second].dest = true;

	std::map<Coords, Coords > came_from;
	std::map<Coords, float> cost;
	visited.clear();

	came_from[start] = start;
	cost[start] = 0;

	while (!open.empty()) {
		Coords current =  open.top().second;
		open.pop();
		visited[current] = true;

		move(current, map);
		std::vector<Coords > neighbours = getNeighbours(map, current, visited);
		map.history.push(map.cells);

		if (current == dest) {
			constructPath(map, start, dest, came_from);
			break;
		}

		for (std::vector<Coords >::iterator neighbour = neighbours.begin(); neighbour != neighbours.end(); ++neighbour) {
			float new_cost = ++cost[current];
			if (!cost[*neighbour] || new_cost < cost[*neighbour]) {
				cost[*neighbour] = new_cost;
				float priority = new_cost + heuristic(*neighbour, dest);
				open.emplace(priority, *neighbour);
				came_from[*neighbour] = current;
			}
		}
	}
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

void Robot::move(Coords coord, Map &map)
{
	map.updateRobotPos(std::make_pair(_y,_x), coord);
	_y = coord.first;
	_x = coord.second;
}
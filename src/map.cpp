#include "map.hpp"
#include <ctime>
#include <cstdlib>
#include <list>
#include <stdexcept>

using namespace std;

/**
 * Map constructor
 *
 * Initialises two public member variables, the number of horizontal (width)
 * and vertical (height) cells on the map with default values or values entered
 * by the user.
 */

Map::Map() : hCells(20), vCells(20) {generateMaze();}
Map::Map(int h) : hCells(h), vCells(20) {generateMaze();}
Map::Map(int h, int v) : hCells(h), vCells(v) {generateMaze();}

/**
 * Maze generator
 *
 * It generates a random simple maze. Good enough for quick testing with
 * unique maps every time.
 */

void Map::generateMaze()
{
	srand(time(NULL));
	list < pair < int, int> > drillers;

	cells.resize(vCells);
	for (size_t y=0; y < vCells; ++y) {
		cells[y].resize(hCells);
	}

	drillers.push_back(make_pair(hCells/2, vCells/2));

	while (drillers.size() > 0) {
		list < pair < int, int> >::iterator m,_m,temp;
		m = drillers.begin();
		_m = drillers.end();
		while (m !=_m) {
			bool remove_driller = false;

			switch(rand()%4) {
				case 0:
					(*m).second-=2;
					if ((*m).second < 0 || !cells[(*m).second][(*m).first].obstacle) {
						remove_driller = true;
						break;
					}
					cells[(*m).second+1][(*m).first].obstacle = false;
				break;

				case 1:
					(*m).second+=2;
					/* Risk of overflow with cast from size_t to int
					   Won't happen unless the user creates a stupidly large
					   map, which would break the code anyway */
					if ((*m).second >= static_cast<int>(vCells) || !cells[(*m).second][(*m).first].obstacle) {
						remove_driller=true;
						break;
					}
					cells[(*m).second-1][(*m).first].obstacle=false;
				break;

				case 2:
					(*m).first-=2;
					if ((*m).first < 0 || !cells[(*m).second][(*m).first].obstacle) {
						remove_driller=true;
						break;
					}
					cells[(*m).second][(*m).first+1].obstacle=false;
				break;
				case 3:
					(*m).first+=2;
					if ((*m).first >= static_cast<int>(hCells) || !cells[(*m).second][(*m).first].obstacle) {
						remove_driller=true;
						break;
					}
					cells[(*m).second][(*m).first-1].obstacle=false;
				break;
			}

			if (remove_driller) {
				m = drillers.erase(m);
			} else {
				drillers.push_back(make_pair((*m).first,(*m).second));

                if (rand()%2) {
					drillers.push_back(make_pair((*m).first,(*m).second));
				}

				cells[(*m).second][(*m).first].obstacle =false;
				++m;
			}
		}
	}
}

/**
 * Updates the robot's position on the map.
 *
 * Takes two pairs of coordinates, the first for the old ones and the second
 * for the new ones. Returns void.
 */

void Map::updateRobotPos(std::pair<int,int> oldPos, std::pair<int,int> newPos)
{
	cells[oldPos.first][oldPos.second].robot = false;
	cells[newPos.first][newPos.second].robot = true;
}

/**
 * Returns the cell at coordinates (y,x).
 *
 * Takes two coordinates of type size_t. Returns a Cell object.
 */

Cell Map::getCell(size_t y, size_t x)
{
	if (y >= cells.size() || x >= cells[0].size()) {
		throw std::out_of_range("Invalid vector access");
	}

	return cells[y][x];
}

std::pair<int,int> Map::getDest()
{
	int x, y;
	do {
		y = rand()%vCells;
		x = rand()%hCells;
	} while (cells[y][x].obstacle == true);

	return make_pair(y,x);
}

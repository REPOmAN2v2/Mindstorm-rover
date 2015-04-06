#include "map.hpp"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <list>

using namespace std;

/**
 * Map constructor
 *
 * Initialises two public member variables, the number of horizontal (hCells)
 * and vertical (vCells) cells on the map.
 *
 * It generates a random simple maze. Good enough for quick testing with
 * unique maps every time.
 */
Map::Map() : hCells(20), vCells(20)
{
	srand(time(NULL));
	list < pair < int, int> > drillers;

	this->cells.resize(this->vCells);
	for (size_t y=0; y < this->vCells; ++y) {
		this->cells[y].resize(this->hCells);
	}

	drillers.push_back(make_pair(this->hCells/2, this->vCells/2));

	while (drillers.size() > 0) {
		list < pair < int, int> >::iterator m,_m,temp;
		m = drillers.begin();
		_m = drillers.end();
		while (m !=_m) {
			bool remove_driller = false;

			switch(rand()%4) {
				case 0:
					(*m).second-=2;
					if ((*m).second < 0 || !this->cells[(*m).second][(*m).first].obstacle) {
						remove_driller = true;
						break;
					}
					this->cells[(*m).second+1][(*m).first].obstacle = false;
				break;

				case 1:
					(*m).second+=2;
					if ((*m).second >= this->vCells || !this->cells[(*m).second][(*m).first].obstacle) {
						remove_driller=true;
						break;
					}
					this->cells[(*m).second-1][(*m).first].obstacle=false;
				break;

				case 2:
					(*m).first-=2;
					if ((*m).first < 0 || !this->cells[(*m).second][(*m).first].obstacle) {
						remove_driller=true;
						break;
					}
					this->cells[(*m).second][(*m).first+1].obstacle=false;
				break;
				case 3:
					(*m).first+=2;
					if ((*m).first >= this->hCells || !this->cells[(*m).second][(*m).first].obstacle) {
						remove_driller=true;
						break;
					}
					this->cells[(*m).second][(*m).first-1].obstacle=false;
				break;
			}

			if (remove_driller) {
				m = drillers.erase(m);
			} else {
				drillers.push_back(make_pair((*m).first,(*m).second));

                if (rand()%2) {
					drillers.push_back(make_pair((*m).first,(*m).second));
				}

				this->cells[(*m).second][(*m).first].obstacle =false;
				++m;
			}
		}
	}
}

/**
 * Displays the map.
 *
 * The robot is displayed using a 'O', unexplored cells with a '?', explored
 * and empty cells with a '.' and explored cells with an obstacle with a '#'.
 */

void Map::display()
{
	for (size_t y = 0; y < this->vCells; ++y) {
		for (size_t x = 0; x < this->hCells; ++x) {
			if (this->cells[y][x].robot == true) {
				cout << 'O';
			} else if (this->cells[y][x].visible == false) {
				cout << '?';
			} else {
				if (this->cells[y][x].obstacle == false) {
					cout << '.';
				} else {
					cout << '#';
				}
			}
		}

		cout << endl;
	}

	cout << endl;
}

/**
 * Displays the map without fog of war
 */

void Map::displayDebug()
{
	for (size_t y = 0; y < this->vCells; ++y) {
		for (size_t x = 0; x < this->hCells; ++x) {
			if (this->cells[y][x].obstacle == false) {
				cout << '.';
			} else {
				cout << '#';
			}
		}

		cout << endl;
	}

	cout << endl;
}

/**
 * Updates the robot's position on the map.
 *
 * Takes two pairs of coordinates, the first for the old ones and the second
 * for the new ones. Returns void.
 */

void Map::updateRobotPos(std::pair<int,int> oldPos, std::pair<int,int> newPos)
{
	this->cells[oldPos.first][oldPos.second].robot = false;
	this->cells[newPos.first][newPos.second].robot = true;
}
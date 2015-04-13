#include "cell.hpp"

/**
 * Cell Constructor.
 *
 * Initialises the visible, obstacle and robot public member variables as well
 * as the cell height and width private member variables.
 */

Cell::Cell() :
	visible(false),
	obstacle(true),
	robot(false),
	dest(false),
	prev(0),
	distEstimate(0) {}

 /**
  * Check if cell is valid
  */

 bool Cell::invalid(std::vector < Cell* > check, size_t h, size_t w)
 {
 	if  (y < 0 || x < 0 || y >= h || x >= w) {
 		return true;
 	}

 	if (obstacle) {
 		return true;
 	}

 	for (size_t i = 0; i < check.size(); ++i) {
 		if (y == check[i]->y && x == check[i]->x) {
 			return true;
 		}
 	}

 	return false;
 }

 void Cell::setDistances(std::pair <int, int> dest)
 {
 	int dx = x - dest.second;
 	int dy = y - dest.first;
 	distEstimate = (dx > 0 ? dx : -dx) + (dy > 0 ? dy : -dy);
 }
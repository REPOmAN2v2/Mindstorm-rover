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
	dest(false) {}
#ifndef _GRID_H
#define _GRID_H

#include "SFML/Graphics.hpp"
#include <iostream>
#include <vector>

using namespace std;

class Grid
{
private:
	int rows, cols, tileSize;

public:
	Grid(int rows, int cols, int tileSize);

	int getTileIndex(int row, int col);
	sf::Vector2f getTilePosition(int row, int col);

	// getter
	int getCols() { return cols; }
	int getTileSize() { return tileSize; }
	int getRows() { return rows; }

};

#endif
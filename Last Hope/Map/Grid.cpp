#include "Grid.h"

Grid::Grid(int rows, int cols, int tileSize)
{
	this->rows = rows;
	this->cols = cols;
	this->tileSize = tileSize;
}

int Grid::getTileIndex(int row, int col)
{
	return row * cols + col;
}

sf::Vector2f Grid::getTilePosition(int row, int col)
{
	float x = col * tileSize + tileSize;
	float y = row * tileSize;
	return sf::Vector2f(x, y);
}
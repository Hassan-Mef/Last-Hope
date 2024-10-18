#include "Grid.h"

Grid::Grid(int rows, int cols, int tileSize)
{
	this->rows = rows;
	this->cols = cols;
	this->tileSize = tileSize;

	tiles.resize(rows *cols);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int index = i * cols + j;  // Convert (i, j) to 1D index

            tiles[index].setSize(sf::Vector2f(tileSize, tileSize));
            tiles[index].setPosition(j * tileSize, i * tileSize);

            
            tiles[index].setOutlineThickness(1);
            tiles[index].setOutlineColor(sf::Color::White);
            tiles[index].setFillColor(sf::Color::Transparent);
        }
    }


}

void Grid::draw(sf::RenderWindow& window)
{
	for (const auto& tile : tiles) {
		window.draw(tile);
	}
}

void Grid::handleClick(const sf::Vector2i& mousePos) {
    // Calculate row and column from mouse position
    int row = mousePos.y / tileSize;
    int col = mousePos.x / tileSize;

    // making sure it is within grid bounds
    if (row >= 0 && row < rows && col >= 0 && col < cols) {
        // Calculate 1D index from (row, col)
        int index = (row * cols) + col;

        std::cout << "Tile clicked: (" << row << ", " << col << ") - Index: " << index << "\n";

        // Change the color of the clicked tile
        tiles[index].setFillColor(sf::Color::Green);  // Highlight tile
    }
}

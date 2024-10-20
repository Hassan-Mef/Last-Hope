#include "Grid.h"

Grid::Grid(int rows, int cols, int tileSize, const std::string& texturePath)
    : rows(rows), cols(cols), tileSize(tileSize) {
    // Load the tileset texture
    if (!tileTexture.loadFromFile(texturePath)) {
        std::cerr << "Error: Could not load texture from " << texturePath << "\n";
        return;
    }

    
    tiles.resize(rows * cols);
  //  tileTypes.resize(rows * cols);  

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            int index = row * cols + col;

            // Initialize the tile shape and position
            tiles[index].setSize(sf::Vector2f(tileSize, tileSize));
            tiles[index].setPosition(col * tileSize, row * tileSize);
            tiles[index].setTexture(&tileTexture);
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

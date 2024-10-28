#include "MapEditor.h"

MapEditor::MapEditor(Grid& grid, Map& map): grid(grid) , map(map) {
	this->selectedTileType = 0;
	this->mapFilePath = "";
}

void MapEditor::handleInput(const sf::Event& event, const sf::RenderWindow& window) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Num1) {
            this->selectedTileType = 1;
            std::cout << "Selected tile type changed to: " << selectedTileType << std::endl;
        }
        else
        {
            this->selectedTileType = 2;
            std::cout << "Selected tile type changed to: " << selectedTileType << std::endl;

        }
    }

    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            // Get mouse position in the window
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            int row = mousePos.y / grid.getTileSize();
            int col = mousePos.x / grid.getTileSize();
            std::cout << "Mouse position: " << mousePos.x << " " << mousePos.y << std::endl;
            std::cout << "Index: " << grid.getTileIndex(row, col) << std::endl;

            // Ensure row and col are within grid bounds
            if (row >= 0 && row < grid.getRows() && col >= 0 && col < grid.getCols()) {
                paintTile(row, col, selectedTileType);  // Paint the tile with the selected type
                std::cout << "Painting tile at (" << row << ", " << col << ") with type " << selectedTileType << std::endl;
            }
        }
    }
}

/*
void MapEditor::paintTile(int row, int col, int tileType)
{
	int index = grid.getTileIndex(row, col);
	int maxIndex = grid.getTileIndex(grid.getRows(), grid.getCols());
	if (index >= 0 && index < maxIndex) {
        map.tiles[index].setType(tileType);
        selectedTileType = tileType;
		
	}
}
*/
void MapEditor::paintTile(int row, int col, int tileType) {
    map.setTileType(row, col, tileType);
    cout << "Tested" << endl;
}


void MapEditor::saveMapToFile(const string& filePath)
{
}

void MapEditor::loadMapFromFile(const string& filePath)
{
}

void MapEditor::setSelectedTileType(int type)
{
	selectedTileType = type;
}

void MapEditor::draw(sf::RenderWindow& window) {
    // Draw the map's tiles
    map.draw(window);

    //Draw a highlight rectangle over the tile at the mouse position
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    int row = mousePos.y / grid.getTileSize();
    int col = mousePos.x / grid.getTileSize();

    if (row >= 0 && row < grid.getRows() && col >= 0 && col < grid.getCols()) {
        sf::RectangleShape highlight(sf::Vector2f(grid.getTileSize(), grid.getTileSize()));
        highlight.setPosition(grid.getTilePosition(row, col));
        highlight.setFillColor(sf::Color(255, 255, 255, 50));  // Semi-transparent highlight
        highlight.setOutlineColor(sf::Color::Yellow);
        highlight.setOutlineThickness(2.0f);
        window.draw(highlight);
    }
}

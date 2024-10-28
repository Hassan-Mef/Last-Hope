#ifndef _MAP_EDITOR_H
#define _MAP_EDITOR_H

          /* Header files */

#include <iostream>
#include <string>
#include "SFML/Graphics.hpp"
#include "../nlohmann/json.hpp"
#include "../Map/Grid.h"
#include "../Map/Map.h"
#include "../Map/Tile.h"

using json = nlohmann::json;
using namespace std;
using namespace sf;


class MapEditor
{
private:
    Grid& grid;  // Reference to the grid for positioning
    Map& map;    // Reference to the map for managing tiles
    int selectedTileType;  // The current tile type selected by the editor for "painting"
    string mapFilePath;  // The file path of the map being edited

public:
    MapEditor(Grid& grid, Map& map);   // Constructor

    // Event handling

    void handleInput(const sf::Event& event, const sf::RenderWindow& window);

    // Map Modification 

    void setSelectedTileType(int type);  // Change the selected tile type
    void paintTile(int row, int col, int tileType);  // Sets a tile at grid position

    // Save/Load map to JSON
    void saveMapToFile(const string& filePath);
    void loadMapFromFile(const string& filePath);

    // Render UI
    void draw(sf::RenderWindow& window);



};

#endif
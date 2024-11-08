// Last Hope.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "SFML/Graphics.hpp"
#include <iostream>
#include "Map/Grid.h"
#include "Map/Map.h"
#include "Editor/MapEditor.h"

int main()
{
    // Window size and grid parameters
    const int tileSize = 64;         // Each tile is now 64x64 pixels
    const int windowWidth = (12 * tileSize) + tileSize + 150;  // Adjusted for 12 columns, base space, and UI editor
    const int windowHeight = (10 * tileSize) +120;  // Adjusted for 10 rows of 64 pixels each

    // Create the SFML window
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Tilemap Grid Example");

    std::map<int, std::string> texturePaths = {
        {0, "textures/bg.png"},
        {1, "textures/grass.png"},
        {2, "textures/rock.png"},
        {3, "textures/foilage.png"}
    };

    // Create the grid with 10 rows, 12 columns, and 64x64 tile size
    Grid grid(10, 12, tileSize);
    Map map(grid, texturePaths);
     MapEditor editor(grid, map);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
               window.close();
            editor.handleInput(event, window);
        }

        window.clear(sf::Color::Black);
        editor.draw(window);
        window.display();
    }

    return 0;
}

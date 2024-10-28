// Last Hope.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "SFML/Graphics.hpp"
#include <iostream>
#include "Map/Grid.h"
#include "Map/Map.h"
#include "Editor/MapEditor.h"

int main()
{
    // Window size and grid parameters
    const int windowWidth = 416;   // 12 columns * 32 tile size
    const int windowHeight = 384;  // 10 rows * 32 tile size
    const int tileSize = 32;       // Each tile is 32x32 pixels

    // Create the SFML window
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Tilemap Grid Example");

    std::map<int, std::string> texturePaths = {
        {0, "textures/bg.png"},
        {1, "textures/grass.png"},
        {2, "textures/rock.png"}
        // Add more textures as needed
    };

    // Create the grid with 10 rows, 12 columns, and 32x32 tile size
    Grid grid(10, 12, tileSize);
    Map map(grid, texturePaths);
    MapEditor editor(grid, map);

    // Game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Handle window close event
            if (event.type == sf::Event::Closed)
                window.close();

            // Handle all inputs through MapEditor
            editor.handleInput(event, window);  // Pass event and window to MapEditor
        }

        // Clear the window with a black background
        window.clear(sf::Color::Black);

        // Draw the map and editor overlay
        editor.draw(window);

        // Display the rendered frame
        window.display();
    }

    return 0;
}

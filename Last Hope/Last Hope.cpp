// Last Hope.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "SFML/Graphics.hpp"
#include <iostream>
#include "Grid.h"

int main()
{
    // Window size and grid parameters
    const int windowWidth = 384;   // 12 columns * 32 tile size
    const int windowHeight = 320;  // 10 rows * 32 tile size
    const int tileSize = 32;       // Each tile is 32*32 pixels

    // Create the SFML window
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Tilemap Grid Example");

    // Create the grid with 10 rows, 12 columns, and 16x16 tile size
    Grid grid(10, 12, tileSize, "textures/grass.png");

    // Game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Handle window close event
            if (event.type == sf::Event::Closed)
                window.close();

            // Handle mouse click event
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);  // Get mouse position relative to the window
                grid.handleClick(mousePos);  // Pass mouse position to the grid
            }
        }

        // Clear the window with a black background
        window.clear(sf::Color::Black);

        // Draw the grid
        grid.draw(window);

        // Display the contents of the window
        window.display();
    }

    return 0;
}



// Last Hope.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "SFML/Graphics.hpp"
#include <iostream>
#include "Map/Grid.h"
#include "Map/Map.h"
#include "Editor/MapEditor.h"
#include "Enemies/Enemy.h"

int main()
{
    // Window size and grid parameters
    const int tileSize = 64;         // Each tile is now 64x64 pixels
    const int windowWidth = (12 * tileSize) + tileSize + 150;  // Adjusted for 12 columns, base space, and UI editor
    const int windowHeight = (10 * tileSize) +120;  // Adjusted for 10 rows of 64 pixels each

    // Create the SFML window
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Last Hope");
	window.setFramerateLimit(20);  // Limit the game to 60 frames per second

    std::map<int, std::string> texturePaths = {
        {0, "assets/textures/bg.png"},
        {1, "assets/textures/grass.png"},
        {2, "assets/textures/rock.png"},
        {3, "assets/textures/foilage.png"}
    };

    // Create the grid with 10 rows, 12 columns, and 64x64 tile size
    Grid grid(10, 12, tileSize);
    Map map(grid, texturePaths);
	map.loadMap("MapData/map_1.json");
    Enemy enemy("assets/Sprite/Attack.png", 100, 10, 12, 20);
	enemy.setPosition(sf::Vector2f(tileSize * 2, tileSize * 2));

     //MapEditor editor(grid, map);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
               window.close();
         //  editor.handleInput(event, window);
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Left) {
                    enemy.move(window);
                }

            }
        }


        window.clear(sf::Color::Black);
        map.draw(window);
        
		enemy.render(window);

        enemy.attack(); // Animation for enemy attacking

		
		

      //  editor.draw(window);
        window.display();
    }

    return 0;
}

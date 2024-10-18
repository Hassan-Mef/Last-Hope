
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
		vector<sf::RectangleShape> tiles;
	public:
		Grid(int rows, int cols, int tileSize);
		void draw(sf::RenderWindow& window);
		void handleClick(const sf::Vector2i& mousePos);


};

#endif


#ifndef _MAP_H
#define _MAP_H

#include "Grid.h"
#include "Tile.h"   
#include <vector>
#include <string>
#include <map>




class Map
{
private:
	Grid& grid;
	
	map<int, sf::Texture> textures;

public:
	std::vector<Tile> tiles;
	Map(Grid& grid, const map<int, string>& texturePaths);
	void setTileType(int row, int col, int type);

	void draw(sf::RenderWindow& window);
	void handleClick(const sf::Vector2i& mousePos);

};


#endif // _MAP_H

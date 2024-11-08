#include "Map.h"

Map::Map(Grid& grid, const map<int,string>& texturePaths ) : grid(grid)
{
	map<int, string> temp;
	


	// Load the tileset image
	for (const auto& temp : texturePaths) {
		sf::Texture texture;
		if (texture.loadFromFile(temp.second)) {
			textures[temp.first] = texture;
		}
		else
		{
			throw runtime_error("Failed to load tileset texture");
			return;
		}
	}
	

	tiles.resize(grid.getRows() * grid.getCols());
	//int randomizer = rand() % grid.getTileIndex(grid.getRows(), grid.getCols());  // getting a random number from 0 to last cell inded=x

	for (int i = 0; i < grid.getRows(); i++)
		for (int j = 0; j < grid.getCols(); j++)
		{
			int index = grid.getTileIndex(i, j);
			tiles[index].setTexture(textures[0]);
			tiles[index].setPosition(grid.getTilePosition(i, j));
			
		}
}
void Map::setTileType(int row, int col, int type) {
	int index = grid.getTileIndex(row, col);
	if (textures.find(type) != textures.end()) {
		tiles[index].setType(type, textures[type]);	
			cout << "Texture set" << endl;
	}
}
void Map::draw(sf::RenderWindow& window)
{
	// Render the base 



	// rendering the tiles
	for (auto& tile : tiles)
		window.draw(tile);
}

void Map::handleClick(const sf::Vector2i& mousePos)
{
	int cellX = mousePos.x / grid.getTileSize();
	int cellY = mousePos.y / grid.getTileSize();
	int tileIndex = grid.getTileIndex(cellY, cellX);

	if (tileIndex >= 0 && tileIndex < tiles.size()) 
	{
		tiles[tileIndex].setColor({ 255, 2, 2 });
	}




}

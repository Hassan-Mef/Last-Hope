#include "Tile.h"

void Tile:: setType(int t, sf::Texture& texture)
{ 
	type = t; 
	setTexture(texture);
	
}

int Tile :: getType() const 
{
	return type; 
}
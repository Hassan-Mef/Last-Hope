#ifndef _TILE_H
#define _TILE_H

// Tile.h
#include "SFML/Graphics.hpp"

class Tile : public sf::Sprite {

private:
    int type;

public:

    Tile() : type(0) {}
    void setType(int t , sf::Texture& texture);
    int getType() const;

};

#endif
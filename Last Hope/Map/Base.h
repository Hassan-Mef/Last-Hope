#ifndef _BASE_H
#define _BASE_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class Base
{
	int health;
	sf::Vector2f position;
	sf::Sprite sprite;
	sf::Texture texture;

	public:

		Base(int health, const std::string& texturePath);

		void takeDamage(int damage);

		void draw(sf::RenderWindow& window);
		




		// helper functions
		void setHealth(int health);
		void setPosition(sf::Vector2f position);

};
#endif // !_BASE_H


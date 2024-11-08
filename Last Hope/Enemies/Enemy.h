#ifndef _EMEMY_H
#define _EMEMY_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class Enemy
{
	protected:
		int health;
		int speed;
		int damage;
		int reward;
		sf::Vector2f position;

		sf::Texture texture;
		sf::Sprite sprite;

	public:
		Enemy(const std::string& texturePath, int health, int speed, int damage, int reward);

		// load textures and setup sprites
		


		//Postioning and rendering 
		void setPosition(sf::Vector2f pos);
		virtual void render(sf::RenderWindow& window);

		// Movement
		virtual void move(sf::RenderWindow &window);

		// Interaction with other game objects
		//virtual void attack(Troop& troop);
		void takeDamage(int amount);
		bool isAlive() const;

		void attack();

		// helper functions 
		void setSpeed(int speed)
		{
			this ->speed = speed;
		}

		int getSpeed()
		{
			return speed;
		}

		sf::Vector2f getPosition()
		{
			return position;
		}
};



#endif
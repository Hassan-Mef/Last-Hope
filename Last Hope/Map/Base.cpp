#include "Base.h"

Base::Base(int health, const std::string& texturePath)
{
	if (!texture.loadFromFile(texturePath)) {
		throw runtime_error("Failed to load texture");
	}
	sprite.setTexture(texture);
	sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	setHealth(health);
}

void Base::takeDamage(int damage)
{
	health -= damage;
	if (health <= 0) {
		//destroy();
	}
}

void Base::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

void Base::setHealth(int health)
{
	this->health = health;

}

void Base::setPosition(sf::Vector2f position)
{
	sprite.setPosition(position);
}

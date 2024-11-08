#include "Enemy.h"
#include <iostream>

Enemy::Enemy(const std::string& texturePath, int health, int speed, int damage, int reward)
    : health(health), speed(speed), damage(damage), reward(reward)
{
    if (!texture.loadFromFile(texturePath)) {
        std::cerr << "Error loading enemy texture!" << std::endl;
    }
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 64, 64)); // Assuming each frame is 64x64
    sprite.setOrigin(32, 32); // Center origin for 64x64 frame
}

void Enemy::setPosition(sf::Vector2f pos) {
    position = pos;
    sprite.setPosition(position);
}

void Enemy::render(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Enemy::move(sf::RenderWindow& window) {
    if (position.x >= window.getSize().x - sprite.getTextureRect().width / 2) {
        speed *= -1;  // Reverse direction when reaching the right edge
    }
    else if (position.x <= sprite.getTextureRect().width / 2) {
        speed *= -1;  // Reverse direction when reaching the left edge
    }
    position.x += speed * 0.1f;
    sprite.setPosition(position);
}

void Enemy::attack() {
    static int frameX = 0; // Track current frame for animation

    // Move to the next frame by updating texture rect
    sprite.setTextureRect(sf::IntRect(frameX * 64, 0, 64, 64)); // Assuming each frame is 64x64
    frameX = (frameX + 1) % (texture.getSize().x / 64); // Loop through frames in spritesheet
}

void Enemy::takeDamage(int amount) {
    health -= amount;
}

bool Enemy::isAlive() const {
    return health > 0;
}

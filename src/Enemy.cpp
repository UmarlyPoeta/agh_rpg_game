#include "Enemy.hpp"
#include <SFML/Graphics.hpp>
#include <iostream> // For debugging

Enemy::Enemy(const sf::Texture &texture) : m_speed(5.0f) {
    m_sprite.setTexture(texture);
    m_sprite.setTextureRect(sf::IntRect(48, 0, 16, 22)); // Set to the correct texture size
    m_sprite.setPosition(16, 164); // Initial position
}

void Enemy::handleMovement() {
    m_velocity = sf::Vector2f(0.f, 0.f);
     
}

void Enemy::update(const sf::VertexArray &map) {
    sf::Vector2f oldPosition = m_sprite.getPosition();
    m_sprite.move(m_velocity * (1.f / 60.f)); // Assume 60 FPS

    if (checkCollision(map)) {
        m_sprite.setPosition(oldPosition); // Revert movement on collision
    }
}

void Enemy::draw(sf::RenderWindow &window) {
    window.draw(m_sprite);
}

bool Enemy::checkCollision(const sf::VertexArray &map) {
    sf::FloatRect enemyBounds = m_sprite.getGlobalBounds();

    for (size_t i = 0; i < map.getVertexCount(); i += 4) {
        sf::FloatRect tileBounds(
            map[i].position.x, 
            map[i].position.y, 
            16, 16 // Tile size
        );

        if (enemyBounds.intersects(tileBounds)) {
            // Assume collision occurs on red tiles
            if (map[i].color == sf::Color(255, 255, 255, 254)) {
                return true;
            }
        }
    }
    return false;
}

sf::FloatRect Enemy::getBounds() const {
    return m_sprite.getGlobalBounds();
}

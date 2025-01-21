#include "Enemy.hpp"
#include <SFML/Graphics.hpp>
#include <iostream> // For debugging

Enemy::Enemy()
{
}

Enemy::Enemy(const sf::Texture &texture) : m_speed(5.0f)
{
    m_sprite.setTexture(texture);
    m_sprite.setTextureRect(sf::IntRect(32, 0, 16, 32)); // Set to the correct texture size
    m_sprite.setPosition(368, 144); // Initial position
    defeated = false;
}

bool Enemy::checkIfPlayerSeesEnemy(sf::Sprite &playerSprite) {
    if (((std::fabs(m_sprite.getPosition().x - playerSprite.getPosition().x) <= 48) && std::fabs(m_sprite.getPosition().y - playerSprite.getPosition().y) <= 48) && (!defeated))
    {
        defeated = true;
        return true;
    }
    return false;
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

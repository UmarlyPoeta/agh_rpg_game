#include "Player.hpp"
#include <SFML/Graphics.hpp>
#include <iostream> // For debugging

Player::Player(const sf::Texture &texture) : m_speed(9.0f) {
    m_sprite.setTexture(texture);
    m_sprite.setTextureRect(sf::IntRect(48, 0, 16, 22)); // Set to the correct texture size
    m_sprite.setPosition(16, 164); // Initial position
}

void Player::setTexture(const sf::Texture &texture) {
    m_sprite.setTexture(texture);
    m_sprite.setTextureRect(sf::IntRect(0, 0, 16, 16)); // Ensure the correct texture size
}

void Player::handleInput() {
    m_velocity = sf::Vector2f(0.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        m_sprite.setTextureRect(sf::IntRect(17, 0, 14, 22));
        m_velocity.y -= m_speed;
    } 
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        m_sprite.setTextureRect(sf::IntRect(49, 0, 14, 22));
        m_velocity.y += m_speed;
    } 
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        m_sprite.setTextureRect(sf::IntRect(33, 0, 14, 22));
        m_velocity.x -= m_speed;
    } 
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        m_sprite.setTextureRect(sf::IntRect(1, 0, 14, 22));
        m_velocity.x += m_speed;
    } 
}

void Player::update(const sf::VertexArray &map) {
    sf::Vector2f oldPosition = m_sprite.getPosition();
    m_sprite.move(m_velocity * (1.f / 60.f)); // Assume 60 FPS

    if (checkCollision(map)) {
        m_sprite.setPosition(oldPosition); // Revert movement on collision
    }
}

void Player::draw(sf::RenderWindow &window) {
    window.draw(m_sprite);
}

sf::Sprite& Player::getSprite()
{
    return m_sprite;
}

bool Player::checkCollision(const sf::VertexArray &map) {
    sf::FloatRect playerBounds = m_sprite.getGlobalBounds();

    for (size_t i = 0; i < map.getVertexCount(); i += 4) {
        sf::FloatRect tileBounds(
            map[i].position.x, 
            map[i].position.y, 
            16, 16 // Tile size
        );

        if (playerBounds.intersects(tileBounds)) {
            // Assume collision occurs on red tiles
            if (map[i].color == sf::Color(255, 255, 255, 254)) {
                return true;
            }
        }
    }
    return false;
}

sf::FloatRect Player::getBounds() const {
    return m_sprite.getGlobalBounds();
}

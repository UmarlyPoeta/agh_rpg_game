#include "Player.hpp"

Player::Player(const sf::Texture &texture) : m_speed(100.0f) {
    m_sprite.setTexture(texture);
    m_sprite.setPosition(64, 64); // Początkowa pozycja gracza
}

void Player::handleInput() {
    m_velocity = sf::Vector2f(0.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) m_velocity.y -= m_speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) m_velocity.y += m_speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) m_velocity.x -= m_speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) m_velocity.x += m_speed;
}

void Player::update(const sf::VertexArray &map) {
    sf::Vector2f oldPosition = m_sprite.getPosition();
    m_sprite.move(m_velocity * (1.f / 60.f)); // Zakładamy 60 FPS

    if (checkCollision(map)) {
        m_sprite.setPosition(oldPosition); // Cofnij ruch w przypadku kolizji
    }
}

void Player::draw(sf::RenderWindow &window) {
    window.draw(m_sprite);
}

bool Player::checkCollision(const sf::VertexArray &map) {
    sf::FloatRect playerBounds = m_sprite.getGlobalBounds();

    for (size_t i = 0; i < map.getVertexCount(); i += 4) {
        sf::FloatRect tileBounds(
            map[i].position.x, 
            map[i].position.y, 
            32, 32 // Rozmiar kafelka
        );

        if (playerBounds.intersects(tileBounds)) {
            // Zakładamy, że kolizja występuje na kafelkach o kolorze czerwonym
            if (map[i].color == sf::Color::Red) {
                return true;
            }
        }
    }
    return false;
}

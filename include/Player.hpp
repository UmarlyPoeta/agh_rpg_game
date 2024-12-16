#pragma once
#include <SFML/Graphics.hpp>

static constexpr int START_POS = 400;


class Player {
public:
    Player(const sf::Texture &texture);
    void handleInput();                // Odczyt wejścia gracza
    void update(const sf::VertexArray &map); // Aktualizacja pozycji i kolizji
    void draw(sf::RenderWindow &window);

private:
    sf::Sprite m_sprite;
    sf::Vector2f m_velocity;
    float m_speed;
    bool checkCollision(const sf::VertexArray &map); // Sprawdzanie kolizji
};

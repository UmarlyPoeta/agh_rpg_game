#pragma once
#include <SFML/Graphics.hpp>

class Enemy {
public:
    Enemy();
    Enemy(const sf::Texture &texture); // Konstruktor akceptujący teksturę
    void handleMovement(); 
    void update(const sf::VertexArray &map); // Aktualizacja pozycji i kolizji
    void draw(sf::RenderWindow &window); // Rysowanie gracza na oknie

    sf::FloatRect getBounds() const; // Pobierz obszar kolizji gracza

private:
    sf::Sprite m_sprite; // Sprite reprezentujący gracza
    sf::Vector2f m_velocity; // Prędkość ruchu gracza
    float m_speed; // Prędkość poruszania się gracza

    bool checkCollision(const sf::VertexArray &map); // Sprawdź kolizje z mapą
};

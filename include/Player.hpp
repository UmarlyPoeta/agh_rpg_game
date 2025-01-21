#pragma once
#include <SFML/Graphics.hpp>

class Player {
public:
    Player();
    Player(const sf::Texture &texture, int whichMap); // Konstruktor akceptujący teksturę
    void setTexture(const sf::Texture &texture); // Ustaw teksturę gracza
    void handleInput(); // Obsługa wejścia z klawiatury
    void update(const sf::VertexArray &map); // Aktualizacja pozycji i kolizji
    void draw(sf::RenderWindow &window); // Rysowanie gracza na oknie
    sf::Sprite& getSprite();

    sf::FloatRect getBounds() const; // Pobierz obszar kolizji gracza

private:
    sf::Sprite m_sprite; // Sprite reprezentujący gracza
    sf::Vector2f m_velocity; // Prędkość ruchu gracza
    float m_speed; // Prędkość poruszania się gracza

    bool checkCollision(const sf::VertexArray &map); // Sprawdź kolizje z mapą
};

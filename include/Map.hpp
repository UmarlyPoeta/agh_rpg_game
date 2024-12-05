#pragma once
#include <SFML/Graphics.hpp>
#include "Player.hpp"

class Map {
public:
    Map(sf::RenderWindow &window);
    bool run(); // Zwraca true, jeśli dochodzi do walki.
private:
    sf::RenderWindow &m_window;
    sf::Texture m_tileset;
    sf::VertexArray m_tilemap;
    Player m_player;
    void loadMap();
};

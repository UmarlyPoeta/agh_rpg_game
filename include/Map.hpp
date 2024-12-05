#pragma once
#include <SFML/Graphics.hpp>

class Map {
public:
    Map(sf::RenderWindow &window);
    bool run(); // true if battle
private:
    sf::RenderWindow &m_window;
    sf::Texture m_tileset;
    sf::VertexArray m_tilemap;
    void loadMap();
};

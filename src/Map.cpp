#include "Map.hpp"

Map::Map(sf::RenderWindow &window) 
    : m_window(window), m_player(m_tileset) {
    m_tileset.loadFromFile("assets/tileset.png");
    loadMap();
}

void Map::loadMap() {
    m_tilemap.setPrimitiveType(sf::Quads);
    m_tilemap.resize(4 * 100);

    for (size_t i = 0; i < 100; ++i) {
        sf::Vertex *quad = &m_tilemap[i * 4];
        quad[0].position = sf::Vector2f(i % 10 * 32, i / 10 * 32);
        quad[1].position = quad[0].position + sf::Vector2f(32, 0);
        quad[2].position = quad[0].position + sf::Vector2f(32, 32);
        quad[3].position = quad[0].position + sf::Vector2f(0, 32);

        // Przykładowa kolizja: tile na pozycji 5 będzie czerwony (kolizyjny)
        if (i == 5) {
            quad[0].color = sf::Color::Red;
            quad[1].color = sf::Color::Red;
            quad[2].color = sf::Color::Red;
            quad[3].color = sf::Color::Red;
        }
    }
}

bool Map::run() {
    m_player.handleInput();
    m_player.update(m_tilemap);
    m_window.draw(m_tilemap);
    m_player.draw(m_window);

    return false; // Na razie brak prowokacji do walki.
}

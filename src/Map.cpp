#include "Map.hpp"

Map::Map(sf::RenderWindow &window) : m_window(window) {
    m_tileset.loadFromFile("assets/tileset.png");
    loadMap();
}

void Map::loadMap() {
    m_tilemap.setPrimitiveType(sf::Quads);
    m_tilemap.resize(4 * 100); // Załóżmy 100 kafelków.

    for (size_t i = 0; i < 100; ++i) {
        sf::Vertex *quad = &m_tilemap[i * 4];
        quad[0].position = sf::Vector2f(i % 10 * 32, i / 10 * 32);
        quad[1].position = quad[0].position + sf::Vector2f(32, 0);
        quad[2].position = quad[0].position + sf::Vector2f(32, 32);
        quad[3].position = quad[0].position + sf::Vector2f(0, 32);
    }
}

bool Map::run() {
    m_window.draw(m_tilemap);
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_window.close();
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::W) {
                // Move player up
            } else if (event.key.code == sf::Keyboard::S) {
                // Move player down
            } else if (event.key.code == sf::Keyboard::A) {
                // Move player left
            } else if (event.key.code == sf::Keyboard::D) {
                // Move player right
            }
        }
    }

    // Example NPC interaction logic
    // Check for collisions or proximity to NPCs
    // if (player.interactsWith(npc)) {
    //     // Handle interaction
    // }

    // Example combat initiation
    // if (player.collidesWith(enemy)) {
    //     return true; // Initiate combat
    // }
    return false; // Zwraca true, jeśli dochodzi do walki.
}

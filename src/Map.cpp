#include "Map.hpp"
#include "Player.hpp"
#include <iostream> // For error logging

Map::Map(sf::RenderWindow &window) 
    : m_window(window), m_player(m_tileset) {
    if (!m_tileset.loadFromFile(ASSET_DIR "/map_agh2.png")) {
        std::cerr << "Error: Failed to load map texture from " << ASSET_DIR << "/map_agh2.png" << std::endl;
    }

    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile(ASSET_DIR "/player.png")) {
        std::cerr << "Error: Failed to load player texture from " << ASSET_DIR << "/player.png" << std::endl;
    } else {
        m_player = Player(playerTexture);
    }

    loadMap();
}

void Map::loadMap() {
    m_tilemap.setPrimitiveType(sf::Quads);
    m_tilemap.resize(4 * 1200); // Adjusted for a 60x20 grid (1200 tiles)

    const int tileSize = 16; // Tile size
    const int tilesPerRow = 60; // Grid width in tiles
    const int textureTilesPerRow = m_tileset.getSize().x / tileSize; // Tiles per row in texture
    const int textureTilesPerColumn = m_tileset.getSize().y / tileSize; // Tiles per column in texture

    for (size_t i = 0; i < 1200; ++i) {
        sf::Vertex *quad = &m_tilemap[i * 4];

        // Calculate tile positions
        quad[0].position = sf::Vector2f((i % tilesPerRow) * tileSize, (i / tilesPerRow) * tileSize);
        quad[1].position = quad[0].position + sf::Vector2f(tileSize, 0);
        quad[2].position = quad[0].position + sf::Vector2f(tileSize, tileSize);
        quad[3].position = quad[0].position + sf::Vector2f(0, tileSize);

        // Calculate texture coordinates to ensure the correct row and column are used
        int textureIndex = i % (textureTilesPerRow * textureTilesPerColumn);
        int tx = (textureIndex % textureTilesPerRow) * tileSize;
        int ty = (textureIndex / textureTilesPerRow) * tileSize;

        quad[0].texCoords = sf::Vector2f(tx, ty);
        quad[1].texCoords = sf::Vector2f(tx + tileSize, ty);
        quad[2].texCoords = sf::Vector2f(tx + tileSize, ty + tileSize);
        quad[3].texCoords = sf::Vector2f(tx, ty + tileSize);

        // Example collision tile (index 300, near the center of the map)
        if (i == 300) {
            quad[0].color = sf::Color::Red;
            quad[1].color = sf::Color::Red;
            quad[2].color = sf::Color::Red;
            quad[3].color = sf::Color::Red;
        }
    }
}

bool Map::run() {
    while (m_window.isOpen()) {
        sf::Event event;
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                m_window.close();
            }
        }

        m_player.handleInput();
        m_player.update(m_tilemap);

        m_window.clear(sf::Color::White); // Background color for map

        // Bind the texture and draw the tilemap
        sf::RenderStates states;
        states.texture = &m_tileset;
        m_window.draw(m_tilemap, states);

        m_player.draw(m_window);
        m_window.display();
    }

    return false;
}

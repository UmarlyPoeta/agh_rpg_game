#pragma once
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Enemy.hpp"

class Map {
public:
    Map(sf::RenderWindow &window);
    bool run(); // Zwraca true, jeśli dochodzi do walki.
private:
    sf::RenderWindow &m_window;
    sf::Texture m_tileset;
    sf::Texture m_playertexture;
    sf::VertexArray m_tilemap;
    Player m_player;
    Enemy m_enemy;
    void loadMap();
};

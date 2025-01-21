#pragma once
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Enemy.hpp"

class Map_2 {
public:
    Map_2(sf::RenderWindow &window);
    bool run(); // Zwraca true, jeśli dochodzi do walki.
private:
    sf::RenderWindow &m_window;
    sf::Texture m_tileset;
    sf::Texture m_playertexture;
    sf::Texture m_enemytexture;
    sf::VertexArray m_tilemap;
    Player m_player;
    Enemy m_enemy;
    void loadMap();
};
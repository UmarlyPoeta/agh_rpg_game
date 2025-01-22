#pragma once
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Enemy.hpp"
#include <cmath>

class Map {
public:
    Map(sf::RenderWindow &window);
    bool run(); // Zwraca true, jeśli dochodzi do walki.
    bool checkIfNextMap(sf::Sprite player_sprite);
    bool getIsNextMap();
    bool next_map;
    sf::Texture tex_to_battle;
    sf::Texture getBattleTexture();
private:
    sf::RenderWindow &m_window;
    sf::Texture m_tileset;
    sf::Texture m_playertexture;
    sf::Texture m_enemytexture;
    sf::Texture m_enemytexture2;
    sf::VertexArray m_tilemap;
    Player m_player;
    Enemy m_enemy;
    Enemy m_enemy2;
    void loadMap();
};

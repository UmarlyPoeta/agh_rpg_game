#pragma once
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Enemy.hpp"

class Map_2 {
public:
    Map_2(sf::RenderWindow &window);
    bool run(); // Zwraca true, jeśli dochodzi do walki.
    bool is_boss;
    sf::Texture tex_to_battle;
    bool getIsBoss();
    sf::Texture getBattleTexture();
private:
    sf::RenderWindow &m_window;
    sf::Texture m_tileset;
    sf::Texture m_playertexture;
    sf::Texture m_enemytexture;
    sf::Texture m_enemytexture2;
    sf::Texture m_enemytexture3;
    sf::Texture m_bosstexture;
    sf::VertexArray m_tilemap;
    Player m_player;
    Enemy m_enemy;
    Enemy m_enemy2;
    Enemy m_enemy3;
    Enemy boss;
    void loadMap();
};
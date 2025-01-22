#pragma once
#include <SFML/Graphics.hpp>



class Battle {
public:
    Battle(sf::RenderWindow &window);

    bool run(sf::Texture enemyBattleTexture); // Zwraca true, jeśli walka zakończyła się.

private:
    sf::RenderWindow &m_window;
    sf::Sprite bar;
    sf::Sprite playerBaner;
    sf::Sprite enemyBaner;
    sf::Sprite background;

    sf::Sprite playerScore;
    sf::Sprite enemyScore;
};

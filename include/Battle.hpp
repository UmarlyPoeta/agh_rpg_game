#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>


class Battle {
public:
    Battle(sf::RenderWindow &window);

    bool run(sf::Texture enemyBattleTexture); // Zwraca true, jeśli walka zakończyła się.
    bool outcome;
    bool isBoss;
    bool getOutcome();
    bool getIsBoss();

private:
    sf::RenderWindow &m_window;
    sf::Sprite borderLeft;
    sf::Sprite borderRight;
    sf::Sprite bar;
    sf::Sprite playerBaner;
    sf::Sprite enemyBaner;
    sf::Sprite background;

    sf::Sprite playerScore;
    sf::Sprite enemyScore;
};

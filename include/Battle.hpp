#pragma once
#include <SFML/Graphics.hpp>

class Battle {
public:
    Battle(sf::RenderWindow &window);
    bool run(); // true if battle ended
private:
    sf::RenderWindow &m_window;
};

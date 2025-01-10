#pragma once
#include <SFML/Graphics.hpp>

class Battle {
public:
    Battle(sf::RenderWindow &window);
    bool run(); // Zwraca true, jeśli walka zakończyła się.

private:
    sf::RenderWindow &m_window;
};

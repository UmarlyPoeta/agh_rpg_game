#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>


class Win {
public:
    Win(sf::RenderWindow &window);

    bool run(); // Zwraca true, jeśli walka zakończyła się.
    
private:
    sf::RenderWindow &m_window;
    sf::Text textshadow;
    sf::Text text1;
    sf::Text text2;
};

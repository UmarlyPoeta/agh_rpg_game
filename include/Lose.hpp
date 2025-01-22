#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>


class Lose {
public:
    Lose(sf::RenderWindow &window);

    bool run(); // Zwraca true, jeśli walka zakończyła się.
    

private:
    sf::RenderWindow &m_window;
    sf::Text text1;
    sf::Text text2; 
};

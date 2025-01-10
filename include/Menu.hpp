#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Menu {
public:
    Menu(sf::RenderWindow &window);
    bool run(); // Zwraca true, jeśli gra się rozpoczyna
private:
    sf::RenderWindow &m_window;
    sf::Font m_font;
    sf::Text m_title;
    sf::Text m_start;
    sf::Text m_exit;
};

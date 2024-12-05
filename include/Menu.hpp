#pragma once
#include <SFML/Graphics.hpp>

class Menu {
public:
    Menu(sf::RenderWindow &window);
    bool run(); // true if game starts
private:
    sf::RenderWindow &m_window;
    sf::Font m_font;
    sf::Text m_title;
    sf::Text m_start;
    sf::Text m_exit;
};

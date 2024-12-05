#include "Menu.hpp"

Menu::Menu(sf::RenderWindow &window) : m_window(window) {
    m_font.loadFromFile("assets/font.ttf");

    m_title.setFont(m_font);
    m_title.setString("AGH RPG");
    m_title.setCharacterSize(50);
    m_title.setPosition(300, 100);

    m_start.setFont(m_font);
    m_start.setString("Start");
    m_start.setCharacterSize(30);
    m_start.setPosition(350, 250);

    m_exit.setFont(m_font);
    m_exit.setString("Exit");
    m_exit.setCharacterSize(30);
    m_exit.setPosition(350, 300);
}

bool Menu::run() {
    m_window.draw(m_title);
    m_window.draw(m_start);
    m_window.draw(m_exit);

    sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (m_start.getGlobalBounds().contains(mousePos.x, mousePos.y)) 
            return true;
        if (m_exit.getGlobalBounds().contains(mousePos.x, mousePos.y)) 
            m_window.close();
    }
    return false;
}

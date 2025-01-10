#include "Menu.hpp"
#include <iostream> // For error logging

Menu::Menu(sf::RenderWindow &window) : m_window(window) {
    if (!m_font.loadFromFile(ASSET_DIR "/font.ttf")) {
        std::cerr << "Error: Failed to load font from " << ASSET_DIR << "/font.ttf" << std::endl;
    }

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
    while (m_window.isOpen()) {
        sf::Event event;
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                m_window.close();
                return false;
            } else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
                sf::FloatRect startBounds = m_start.getGlobalBounds();
                sf::FloatRect exitBounds = m_exit.getGlobalBounds();

                if (startBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    return true; // Start the game
                }
                if (exitBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    m_window.close(); // Exit the game
                }
            }
        }

        m_window.clear(sf::Color::Black); // Clear the screen with a background color
        m_window.draw(m_title);
        m_window.draw(m_start);
        m_window.draw(m_exit);
        m_window.display();
    }
    return false;
}

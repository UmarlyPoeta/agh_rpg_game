#include "Lose.hpp"
#include <iostream> // For debug logging

Lose::Lose(sf::RenderWindow &window) : m_window(window) {

}

bool Lose::run() {
    m_window.setSize(sf::Vector2u(800, 500));
    sf::View view(sf::FloatRect(0, 0, 800, 500));
    m_window.setView(view);

    sf::Texture backgroundTexture;

    if (!backgroundTexture.loadFromFile(ASSET_DIR "/przegrana.png")) {
        std::cerr << "Error: Failed to load player texture from " << ASSET_DIR << "/przegrana.png" << std::endl;
    }

    sf::Sprite background;
    background.setTexture(backgroundTexture);
    background.setTextureRect(sf::IntRect(0, 0, 800, 500));
    background.setPosition(0, 0);
    
    sf::Font font;
    if (!font.loadFromFile(ASSET_DIR "/pixel-font.ttf")) {
        std::cerr << "Error: Failed to load font for battle screen." << std::endl;
        return true; // Exit battle if resources fail to load
    }

    
    text1.setFont(font);
    text1.setCharacterSize(150);
    text1.setPosition(200, 150);
    text1.setString("YOU LOST!");

    text2.setFont(font);
    text2.setCharacterSize(25);
    text2.setPosition(200, 400);
    text2.setString("Press Enter to leave the game, try harder :)");

    while (m_window.isOpen()) {
        sf::Event event;
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                m_window.close();
                return true;
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter) {
                    m_window.close();
                }
            }
        }

        
        m_window.clear(sf::Color::Black); // Background for battle
        m_window.draw(background);
        m_window.draw(text1);
        m_window.draw(text2);
        m_window.display();
    }

    return true;
}

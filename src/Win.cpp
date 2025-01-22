#include "Win.hpp"
#include <iostream> // For debug logging
Win::Win(sf::RenderWindow &window) : m_window(window) {

}

bool Win::run() {
    m_window.setSize(sf::Vector2u(800, 500));
    sf::View view(sf::FloatRect(0, 0, 800, 500));
    m_window.setView(view);

    sf::Texture backgroundTexture;

    if (!backgroundTexture.loadFromFile(ASSET_DIR "/wygrana_piwo_koks.png")) {
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
    text1.setFillColor(sf::Color::Black);
    text1.setCharacterSize(150);
    text1.setPosition(200, 150);
    text1.setString("YOU WON!");

    text2.setFont(font);
    text2.setFillColor(sf::Color::Black);
    text2.setCharacterSize(40);
    text2.setPosition(150, 400);
    text2.setString("Press Enter to leave the game, Thank you for playing :^)");

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


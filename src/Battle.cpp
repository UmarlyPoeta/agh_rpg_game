#include "Battle.hpp"
#include <iostream> // For debug logging

Battle::Battle(sf::RenderWindow &window) : m_window(window) {}

bool Battle::run() {
    // Tymczasowe statystyki
    int playerHealth = 100;
    int enemyHealth = 100;

    sf::Font font;
    if (!font.loadFromFile("assets/font.ttf")) {
        std::cerr << "Error: Failed to load font for battle screen." << std::endl;
        return true; // Exit battle if resources fail to load
    }

    sf::Text playerHealthText;
    playerHealthText.setFont(font);
    playerHealthText.setCharacterSize(20);
    playerHealthText.setPosition(50, 50);

    sf::Text enemyHealthText;
    enemyHealthText.setFont(font);
    enemyHealthText.setCharacterSize(20);
    enemyHealthText.setPosition(600, 50);

    while (m_window.isOpen()) {
        sf::Event event;
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                m_window.close();
                return true;
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::A) {
                    enemyHealth -= 10; // Player attacks enemy
                } else if (event.key.code == sf::Keyboard::D) {
                    playerHealth -= 10; // Enemy attacks player (placeholder logic)
                }
            }
        }

        // Update health texts
        playerHealthText.setString("Player HP: " + std::to_string(playerHealth));
        enemyHealthText.setString("Enemy HP: " + std::to_string(enemyHealth));

        // Check battle end conditions
        if (playerHealth <= 0) {
            std::cout << "Player defeated!" << std::endl;
            return true;
        }
        if (enemyHealth <= 0) {
            std::cout << "Enemy defeated!" << std::endl;
            return true;
        }

        m_window.clear(sf::Color::Blue); // Background for battle
        m_window.draw(playerHealthText);
        m_window.draw(enemyHealthText);
        m_window.display();
    }

    return true;
}

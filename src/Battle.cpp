#include "Battle.hpp"
#include <iostream> // For debug logging
Battle::Battle(sf::RenderWindow &window) : m_window(window) {

}

bool Battle::run(sf::Texture enemyTex) {
    // Tymczasowe statystyki
    m_window.setSize(sf::Vector2u(800, 500));
    sf::View view(sf::FloatRect(0, 0, 800, 500));
    m_window.setView(view);

    int player_score = 10;
    int enemy_score = 10;


    sf::Texture backgroundTex;
    if (!backgroundTex.loadFromFile(ASSET_DIR "/back_battle.png")) {
        std::cerr << "Error: Failed to load bar.png for battle screen." << std::endl;
        return true; // Exit battle if resources fail to load
    }

    sf::Texture bar_tex;
    if (!bar_tex.loadFromFile(ASSET_DIR "/bar.png")) {
        std::cerr << "Error: Failed to load bar.png for battle screen." << std::endl;
        return true; // Exit battle if resources fail to load
    }

    sf::Texture playerTextureBaner;
    if (!playerTextureBaner.loadFromFile(ASSET_DIR "/student_selfie.png")) {
        std::cerr << "Error: Failed to load bar.png for battle screen." << std::endl;
        return true; // Exit battle if resources fail to load
    }

    playerBaner.setTexture(playerTextureBaner);
    playerBaner.setTextureRect(sf::IntRect(0, 0, 300, 400));
    playerBaner.setPosition(0, 0);


    bar.setTexture(bar_tex);
    bar.setTextureRect(sf::IntRect(7, 80, 393, 60));
    bar.setPosition(50, 300);

    background.setTexture(backgroundTex);
    background.setTextureRect(sf::IntRect(0, 0, 800, 500));
    background.setPosition(0, 0);

    enemyBaner.setTexture(enemyTex);
    enemyBaner.setTextureRect(sf::IntRect(0, 0, 300, 400));
    enemyBaner.setPosition(500, 0);

    /*sf::RectangleShape playerBar(sf::Vector2f(200, 20));
    playerBar.setFillColor(sf::Color::Green);
    playerBar.setPosition(50, 350);
    playerBar.setSize(sf::Vector2f(200 * playerFill, 20));

    sf::RectangleShape enemyBar(sf::Vector2f(200, 20));
    enemyBar.setFillColor(sf::Color::Red);
    enemyBar.setPosition(550, 350);
    enemyBar.setSize(sf::Vector2f(200 * enemyFill, 20));
    */

    sf::Font font;
    if (!font.loadFromFile(ASSET_DIR "/pixel-font.ttf")) {
        std::cerr << "Error: Failed to load font for battle screen." << std::endl;
        return true; // Exit battle if resources fail to load
    }

    sf::Text playerHealthText;
    playerHealthText.setFont(font);
    playerHealthText.setCharacterSize(20);
    playerHealthText.setPosition(300, 400);

    sf::Text enemyHealthText;
    enemyHealthText.setFont(font);
    enemyHealthText.setCharacterSize(20);
    enemyHealthText.setPosition(420, 400);

    while (m_window.isOpen()) {
        sf::Event event;
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                m_window.close();
                return true;
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    player_score += 5;
                } else if (event.key.code == sf::Keyboard::Enter) {
                    enemy_score += 5;
                }
            }
        }

        // Update health texts
        playerHealthText.setString("Player Win%: " + std::to_string(player_score));
        enemyHealthText.setString("Enemy Win%: " + std::to_string(enemy_score));

        // Check battle end conditions
        if (player_score >= 100) {
            std::cout << "Player defeated!" << std::endl;
            return true;
        }
        if (enemy_score >= 100) {
            std::cout << "Enemy defeated!" << std::endl;
            return true;
        }

        m_window.clear(sf::Color::Black); // Background for battle
        m_window.draw(playerHealthText);
        m_window.draw(enemyHealthText);
        m_window.draw(background);
        m_window.draw(playerBaner);
        m_window.draw(enemyBaner);
        m_window.draw(bar);
        m_window.display();
    }

    return true;
}

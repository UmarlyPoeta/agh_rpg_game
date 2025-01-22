#include "Battle.hpp"
#include <iostream> // For debug logging
Battle::Battle(sf::RenderWindow &window) : m_window(window) {

}

bool Battle::run(sf::Texture enemyTex) {
    // Tymczasowe statystyki
    m_window.setSize(sf::Vector2u(800, 500));
    sf::View view(sf::FloatRect(0, 0, 800, 500));
    m_window.setView(view);

    int player_score = 70;
    int enemy_score = 70;

    sf::Texture borderTexture;
    if (!borderTexture.loadFromFile(ASSET_DIR "/border.png")) {
        std::cerr << "Error: Failed to load bar.png for battle screen." << std::endl;
        return true; // Exit battle if resources fail to load
    }


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

    borderLeft.setTexture(borderTexture);
    borderLeft.setTextureRect(sf::IntRect(85, 85, 384, 473));
    borderLeft.setPosition(0, 0);

    borderRight.setTexture(borderTexture);
    borderRight.setTextureRect(sf::IntRect(0, 85, 384, 473));
    borderRight.setPosition(416, 0);

    playerBaner.setTexture(playerTextureBaner);
    playerBaner.setTextureRect(sf::IntRect(0, 0, 300, 400));
    playerBaner.setPosition(0, 0);

    background.setTexture(backgroundTex);
    background.setTextureRect(sf::IntRect(0, 0, 800, 500));
    background.setPosition(0, 0);

    enemyBaner.setTexture(enemyTex);
    enemyBaner.setTextureRect(sf::IntRect(0, 0, 300, 400));
    enemyBaner.setPosition(500, 0);

    bar.setTexture(bar_tex);
    bar.setTextureRect(sf::IntRect(0, 0, 800, 200));
    bar.setPosition(0, 350);

    sf::RectangleShape playerBar;
    playerBar.setFillColor(sf::Color::Green);
    playerBar.setPosition(80, 435);
    playerBar.setSize(sf::Vector2f(70, 30));

    sf::RectangleShape enemyBar;
    enemyBar.setFillColor(sf::Color::Red);
    enemyBar.setPosition(720, 435);
    enemyBar.setSize(sf::Vector2f(-70, 30));
    
    sf::RectangleShape winBar;
    winBar.setFillColor(sf::Color::Yellow);
    winBar.setPosition(390, 435);
    winBar.setSize(sf::Vector2f(20, 30));


    sf::Font font;
    if (!font.loadFromFile(ASSET_DIR "/pixel-font.ttf")) {
        std::cerr << "Error: Failed to load font for battle screen." << std::endl;
        return true; // Exit battle if resources fail to load
    }

    sf::Text vsText;
    vsText.setFont(font);
    vsText.setCharacterSize(100);
    vsText.setPosition(365, 200);
    vsText.setString("VS");

    while (m_window.isOpen()) {
        sf::Event event;
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                m_window.close();
                return true;
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    player_score += 7;
                } else if (event.key.code == sf::Keyboard::Enter) {
                    enemy_score += 7;
                }
            }
        }

        playerBar.setSize(sf::Vector2f(player_score, 30));
        enemyBar.setSize(sf::Vector2f(-1 * enemy_score, 30));

        // Check battle end conditions
        if (playerBar.getSize().x >= 320) {
            outcome = true;
            return true;
        }
        if (std::fabs(enemyBar.getSize().x) >= 320) {
            outcome = false;
            return true;
        }

        m_window.clear(sf::Color::Black); // Background for battle
        m_window.draw(background);
        m_window.draw(playerBaner);
        m_window.draw(enemyBaner);
        m_window.draw(borderLeft);
        m_window.draw(borderRight);
        m_window.draw(bar);
        m_window.draw(winBar);
        m_window.draw(playerBar);
        m_window.draw(enemyBar);
        m_window.draw(vsText);
        m_window.display();
    }

    return true;
}

bool Battle::getOutcome()
{
    return outcome;
}

bool Battle::getIsBoss()
{
    return isBoss;
}

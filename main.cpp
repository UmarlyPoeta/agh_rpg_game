#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <string>

const int TILE_SIZE = 16;
const int MAP_WIDTH = 10;
const int MAP_HEIGHT = 10;

// Przykładowa mapa (indeksy tekstur)
int level[MAP_HEIGHT][MAP_WIDTH] = {
    {0, 1, 2, 3, 0, 1, 2, 3, 0, 1},
    {1, 0, 3, 2, 1, 0, 3, 2, 1, 0},
    {2, 3, 0, 1, 2, 3, 0, 1, 2, 3},
    {3, 2, 1, 0, 3, 2, 1, 0, 3, 2},
    {0, 1, 2, 3, 0, 1, 2, 3, 0, 1},
    {1, 0, 3, 2, 1, 0, 3, 2, 1, 0},
    {2, 3, 0, 1, 2, 3, 0, 1, 2, 3},
    {3, 2, 1, 0, 3, 2, 1, 0, 3, 2},
    {0, 1, 2, 3, 0, 1, 2, 3, 0, 1},
    {1, 0, 3, 2, 1, 0, 3, 2, 1, 0}
};

enum GameState { MENU, GAME };

int main() {
    sf::RenderWindow window(sf::VideoMode(400, 300), "Retro RPG - Menu");

    // Ładowanie czcionki
    sf::Font font;
    if (!font.loadFromFile("fonts/arial.ttf")) {
        return -1; // Wyjdź, jeśli nie uda się załadować czcionki
    }

    // Tekst do menu
    sf::Text title("AGH RPG", font, 36);
    title.setPosition(100, 50);
    title.setFillColor(sf::Color::White);

    sf::Text start("1. Start Game", font, 24);
    start.setPosition(100, 150);
    start.setFillColor(sf::Color::White);

    sf::Text exit("2. Exit", font, 24);
    exit.setPosition(100, 200);
    exit.setFillColor(sf::Color::White);

    // Zmienna do śledzenia stanu gry
    GameState state = MENU;

    // Gracz i świat gry
    sf::Texture tileset;
    sf::Texture playerTexture;
    sf::VertexArray tilemap(sf::Quads, MAP_WIDTH * MAP_HEIGHT * 4);
    sf::Sprite player;

    // Główna pętla gry
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (state == MENU && event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Num1) {
                    state = GAME;

                    // Przygotowanie świata gry
                    if (!tileset.loadFromFile("textures/tileset.png") || !playerTexture.loadFromFile("textures/player.png")) {
                        return -1;
                    }

                    // Generowanie tilemapy
                    for (int y = 0; y < MAP_HEIGHT; ++y) {
                        for (int x = 0; x < MAP_WIDTH; ++x) {
                            int tileIndex = level[y][x];
                            int tu = tileIndex % (tileset.getSize().x / TILE_SIZE);
                            int tv = tileIndex / (tileset.getSize().x / TILE_SIZE);

                            sf::Vertex* quad = &tilemap[(x + y * MAP_WIDTH) * 4];
                            quad[0].position = sf::Vector2f(x * TILE_SIZE, y * TILE_SIZE);
                            quad[1].position = sf::Vector2f((x + 1) * TILE_SIZE, y * TILE_SIZE);
                            quad[2].position = sf::Vector2f((x + 1) * TILE_SIZE, (y + 1) * TILE_SIZE);
                            quad[3].position = sf::Vector2f(x * TILE_SIZE, (y + 1) * TILE_SIZE);
                            quad[0].texCoords = sf::Vector2f(tu * TILE_SIZE, tv * TILE_SIZE);
                            quad[1].texCoords = sf::Vector2f((tu + 1) * TILE_SIZE, tv * TILE_SIZE);
                            quad[2].texCoords = sf::Vector2f((tu + 1) * TILE_SIZE, (tv + 1) * TILE_SIZE);
                            quad[3].texCoords = sf::Vector2f(tu * TILE_SIZE, (tv + 1) * TILE_SIZE);
                        }
                    }

                    player.setTexture(playerTexture);
                    player.setPosition(5 * TILE_SIZE, 5 * TILE_SIZE);
                } else if (event.key.code == sf::Keyboard::Num2) {
                    window.close();
                }
            }

            // Ruch gracza
            if (state == GAME && event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::W) player.move(0, -TILE_SIZE);
                if (event.key.code == sf::Keyboard::S) player.move(0, TILE_SIZE);
                if (event.key.code == sf::Keyboard::A) player.move(-TILE_SIZE, 0);
                if (event.key.code == sf::Keyboard::D) player.move(TILE_SIZE, 0);
            }
        }

        window.clear();
        if (state == MENU) {
            window.draw(title);
            window.draw(start);
            window.draw(exit);
        } else if (state == GAME) {
            window.draw(tilemap, &tileset);
            window.draw(player);
        }
        window.display();
    }

    return 0;
}

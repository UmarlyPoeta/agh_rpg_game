#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>

const int TILE_SIZE = 16; // Rozmiar jednego kafelka
const int MAP_WIDTH = 10; // Szerokość mapy w kafelkach
const int MAP_HEIGHT = 10; // Wysokość mapy w kafelkach

// Mapa gry (indeksy kafelków)
int level[MAP_HEIGHT][MAP_WIDTH] = {
    {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
    {10, 11, 12, 13, 14, 15, 16, 17, 18, 19},
    {20, 21, 22, 23, 24, 25, 26, 27, 28, 29},
    {30, 31, 32, 33, 34, 35, 36, 37, 38, 39},
    {40, 41, 42, 43, 44, 45, 46, 47, 48, 49},
    {50, 51, 52, 53, 54, 55, 56, 57, 58, 59},
    {60, 61, 62, 63, 64, 65, 66, 67, 68, 69},
    {70, 71, 72, 73, 74, 75, 76, 77, 78, 79},
    {80, 81, 82, 83, 84, 85, 86, 87, 88, 89},
    {90, 91, 92, 93, 94, 95, 96, 97, 98, 99}
};

enum GameState { MENU, GAME };

int main() {
    sf::RenderWindow window(sf::VideoMode(400, 300), "Retro RPG - Tilemap");

    // Ładowanie tilesetu
    sf::Texture tileset;
    if (!tileset.loadFromFile("textures/tileset.png")) {
        return -1; // Wyjdź, jeśli nie uda się załadować tilesetu
    }

    // Ładowanie tekstury gracza
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("textures/player.png")) {
        return -1; // Wyjdź, jeśli nie uda się załadować tekstury gracza
    }

    // Inicjalizacja gracza
    sf::Sprite player(playerTexture);
    player.setPosition(5 * TILE_SIZE, 5 * TILE_SIZE); // Początkowa pozycja gracza

    // Obliczanie liczby kolumn w tilesecie
    int tilesetCols = tileset.getSize().x / TILE_SIZE;

    // Tworzenie mapy jako sf::VertexArray
    sf::VertexArray tilemap(sf::Quads, MAP_WIDTH * MAP_HEIGHT * 4);

    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            int tileIndex = level[y][x];
            int tu = tileIndex % tilesetCols; // Kolumna kafelka w tilesecie
            int tv = tileIndex / tilesetCols; // Wiersz kafelka w tilesecie

            sf::Vertex* quad = &tilemap[(x + y * MAP_WIDTH) * 4];

            // Ustawienie pozycji kafelka na mapie
            quad[0].position = sf::Vector2f(x * TILE_SIZE, y * TILE_SIZE);
            quad[1].position = sf::Vector2f((x + 1) * TILE_SIZE, y * TILE_SIZE);
            quad[2].position = sf::Vector2f((x + 1) * TILE_SIZE, (y + 1) * TILE_SIZE);
            quad[3].position = sf::Vector2f(x * TILE_SIZE, (y + 1) * TILE_SIZE);

            // Ustawienie współrzędnych tekstury kafelka
            quad[0].texCoords = sf::Vector2f(tu * TILE_SIZE, tv * TILE_SIZE);
            quad[1].texCoords = sf::Vector2f((tu + 1) * TILE_SIZE, tv * TILE_SIZE);
            quad[2].texCoords = sf::Vector2f((tu + 1) * TILE_SIZE, (tv + 1) * TILE_SIZE);
            quad[3].texCoords = sf::Vector2f(tu * TILE_SIZE, (tv + 1) * TILE_SIZE);
        }
    }

    // Główna pętla gry
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Ruch gracza z kolizją
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            if (player.getPosition().y > 0)
                player.move(0, -TILE_SIZE);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            if (player.getPosition().y < (MAP_HEIGHT - 1) * TILE_SIZE)
                player.move(0, TILE_SIZE);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            if (player.getPosition().x > 0)
                player.move(-TILE_SIZE, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            if (player.getPosition().x < (MAP_WIDTH - 1) * TILE_SIZE)
                player.move(TILE_SIZE, 0);
        }

        // Renderowanie mapy i gracza
        window.clear();
        window.draw(tilemap, &tileset);
        window.draw(player);
        window.display();
    }

    return 0;
}

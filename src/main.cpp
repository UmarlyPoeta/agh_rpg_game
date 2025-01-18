#include <SFML/Graphics.hpp>
#include "Menu.hpp"
#include "Map.hpp"
#include "Battle.hpp"

enum GameState { MENU, MAP, BATTLE };

int main() {
    sf::RenderWindow window(sf::VideoMode(800,500), "AGH RPG");

    GameState state = MENU;
    Menu menu(window);
    Map map(window);
    Battle battle(window);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) 
                window.close();
        }

        window.clear();

        switch (state) {
            case MENU:
                if (menu.run()) state = MAP;
                break;
            case MAP:
                if (map.run()) state = BATTLE;
                break;
            case BATTLE:
                if (battle.run()) state = MAP;
                break;
        }

        window.display();
    }

    return 0;
}

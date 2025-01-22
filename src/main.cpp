#include <SFML/Graphics.hpp>
#include "Menu.hpp"
#include "Map.hpp"
#include "Battle.hpp"
#include "Map2.hpp"
#include "GameState.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(800,500), "AGH RPG");

    GameState state = MENU;
    Menu menu(window);
    Map map(window);
    Map_2 map_2(window);
    Battle battle(window);
    sf::Texture battleTexture;

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
                if (map.run())
                {
                    if (map.getIsNextMap())
                    {
                        state = MAP_2;
                    } else {
                        state = BATTLE;
                        battleTexture = map.getBattleTexture();
                    }
                } 
                break;
            case BATTLE:
                if (battle.run(battleTexture))
                {
                    if (map.getIsNextMap())
                    {
                        state = MAP_2;
                    } else {
                        state = MAP;
                    }
                }
                break;
            case MAP_2:
                if (map_2.run())
                {
                    state = BATTLE;
                    battleTexture = map_2.getBattleTexture();
                } 
                break;
        }

        window.display();
    }

    return 0;
}

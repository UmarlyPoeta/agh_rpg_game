#include "Map_2.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include <iostream> // For error logging

Map_2::Map_2(sf::RenderWindow &window) 
    : m_window(window), m_player(m_tileset), m_enemy(m_tileset) {
    if (!m_tileset.loadFromFile(ASSET_DIR "/b5.png")) {
        std::cerr << "Error: Failed to load map texture from " << ASSET_DIR << "/map_agh2.png" << std::endl;
    }

    if (!m_enemytexture.loadFromFile(ASSET_DIR "/student.png")) {
        std::cerr << "Error: Failed to load enemy texture from " << ASSET_DIR << "/enemy.png" << std::endl;
    } else {
        m_enemy = Enemy(m_enemytexture);
    }

    if (!m_playertexture.loadFromFile(ASSET_DIR "/student.png")) {
        std::cerr << "Error: Failed to load player texture from " << ASSET_DIR << "/player.png" << std::endl;
    } else {
        m_player = Player(m_playertexture);
    }

    loadMap();
}

void Map_2::loadMap() {
    m_tilemap.setPrimitiveType(sf::Quads);
    m_tilemap.resize(4 * 648); // Adjusted for a 60x20 grid (648 tiles)

    const int tileSize = 16; // Tile size
    const int tilesPerRow = 36; // Grid width in tiles
    const int textureTilesPerRow = m_tileset.getSize().x / tileSize; // Tiles per row in texture
    const int textureTilesPerColumn = m_tileset.getSize().y / tileSize; // Tiles per column in texture

    for (size_t i = 0; i < 648; ++i) {
        sf::Vertex *quad = &m_tilemap[i * 4];

        // Calculate tile positions
        quad[0].position = sf::Vector2f((i % tilesPerRow) * tileSize, (i / tilesPerRow) * tileSize);
        quad[1].position = quad[0].position + sf::Vector2f(tileSize, 0);
        quad[2].position = quad[0].position + sf::Vector2f(tileSize, tileSize);
        quad[3].position = quad[0].position + sf::Vector2f(0, tileSize);

        // Calculate texture coordinates to ensure the correct row and column are used
        int textureIndex = i % (textureTilesPerRow * textureTilesPerColumn);
        int tx = (textureIndex % textureTilesPerRow) * tileSize;
        int ty = (textureIndex / textureTilesPerRow) * tileSize;

        quad[0].texCoords = sf::Vector2f(tx, ty);
        quad[1].texCoords = sf::Vector2f(tx + tileSize, ty);
        quad[2].texCoords = sf::Vector2f(tx + tileSize, ty + tileSize);
        quad[3].texCoords = sf::Vector2f(tx, ty + tileSize);

        int collisiontile[648] = {
            000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,
            000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,
            000, 73, 74, 75, 76, 77, 78,000, 80, 81,000, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99,100,101,102,103,104,105,106,000,
            000,109,110,111,112,113,114,000,116,117,000,119,120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,000,
            000,145,146,147,148,149,150,000,152,153,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,169,170,000,172,173,000,000,000,000,000,000,
            000,000,000,183,184,000,000,000,188,189,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,205,206,000,208,209,000,000,000,000,000,000,
            000,000,000,219,220,000,000,000,224,225,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,241,242,000,244,245,000,000,000,000,000,000, 
            000,000,000,255,256,000,000,000,260,261,000,263,264,265,266,267,268,269,270,000,272,273,274,275,276,277,278,000,280,281,000,283,284,285,286,000, 
            000,289,290,291,292,293,294,295,296,297,000,299,300,301,302,303,304,305,306,000,308,309,310,311,312,313,314,000,316,317,000,319,320,321,322,000, 
            000,325,326,327,328,329,330,331,332,333,000,335,336,000,000,000,000,341,342,000,000,000,000,000,000,349,350,000,352,353,000,355,356,000,000,000,
            000,361,362,000,000,000,000,000,000,000,000,371,372,000,000,000,000,377,378,000,000,000,000,000,000,385,386,000,388,389,000,391,392,000,000,000, 
            000,397,398,000,000,000,000,000,000,000,000,407,408,000,000,000,000,413,414,000,000,000,000,000,000,421,422,000,424,425,000,427,428,000,000,000, 
            000,433,434,000,000,000,000,000,000,000,000,443,444,000,446,447,000,449,450,451,452,000,454,455,456,457,458,000,460,461,462,463,464,465,466,000,
            000,469,470,000,472,473,000,475,476,477,000,479,480,000,482,483,000,485,486,487,488,000,490,491,492,493,494,000,496,497,498,499,500,501,502,000, 
            000,505,506,000,508,509,000,511,512,513,000,515,516,000,518,519,000,521,522,523,524,000,526,527,000,529,530,000,532,533,534,000,000,537,538,000, 
            000,541,542,543,544,545,546,547,548,549,550,551,552,553,554,555,000,557,558,559,560,561,562,563,000,565,566,567,568,569,570,000,000,573,574,000, 
            000,577,578,579,580,581,582,583,584,585,586,587,588,589,590,591,000,593,594,595,596,597,598,599,000,601,602,603,604,605,606,000,000,609,610,000, 
            000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,
        };

        //Example collision tile (index 300, near the center of the map)
        if (!(i == collisiontile[i])) {
            quad[0].color = sf::Color(255, 255, 255, 254);
            quad[1].color = sf::Color(255, 255, 255, 254);
            quad[2].color = sf::Color(255, 255, 255, 254);
            quad[3].color = sf::Color(255, 255, 255, 254);
        }
        // if (!i == collisiontile[i]) {
        //     quad[0].color = sf::Color::Red;
        //     quad[1].color = sf::Color::Red;
        //     quad[2].color = sf::Color::Red;
        //     quad[3].color = sf::Color::Red;
        // }
        if (i == 111 || i == 112) {
            quad[0].color = sf::Color::Green;
            quad[1].color = sf::Color::Green;
            quad[2].color = sf::Color::Green;
            quad[3].color = sf::Color::Green;
        }
    }
}

bool Map_2::run() {
    m_window.setSize(sf::Vector2u(576, 288));
    sf::View view(sf::FloatRect(0, 0, 576, 288));
    m_window.setView(view);

    while (m_window.isOpen()) {
        sf::Event event;
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                m_window.close();
            }
        }

        m_player.handleInput();
        if (m_enemy.checkIfPlayerSeesEnemy(m_player.getSprite()))
        {
            return true;
        }
        m_player.update(m_tilemap);

        m_window.clear(sf::Color::White); // Background color for map

        // Bind the texture and draw the tilemap
        sf::RenderStates states;
        states.texture = &m_tileset;
        m_window.draw(m_tilemap, states);

        m_player.draw(m_window);
        m_enemy.draw(m_window);
        m_window.display();
    }

    return false;
}
#include "Map.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include <iostream> // For error logging

Map::Map(sf::RenderWindow &window) 
    : m_window(window), m_player(m_tileset) {

    next_map = false;

    if (!m_tileset.loadFromFile(ASSET_DIR "/map_agh2.png")) {
        std::cerr << "Error: Failed to load map texture from " << ASSET_DIR << "/map_agh2.png" << std::endl;
    }

    if (!m_enemytexture2.loadFromFile(ASSET_DIR "/midas.png")) {
        std::cerr << "Error: Failed to load enemy texture from " << ASSET_DIR << "/midas.png" << std::endl;
    } else {
        m_enemy2 = Enemy(m_enemytexture2);
    }

    if (!m_enemytexture.loadFromFile(ASSET_DIR "/enemy.png")) {
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

void Map::loadMap() {
    m_tilemap.setPrimitiveType(sf::Quads);
    m_tilemap.resize(4 * 1200); // Adjusted for a 60x20 grid (1200 tiles)

    const int tileSize = 16; // Tile size
    const int tilesPerRow = 60; // Grid width in tiles
    const int textureTilesPerRow = m_tileset.getSize().x / tileSize; // Tiles per row in texture
    const int textureTilesPerColumn = m_tileset.getSize().y / tileSize; // Tiles per column in texture

    for (size_t i = 0; i < 1200; ++i) {
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

        int collisiontile[1200] = {
            000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,
            000,61,62,63,64,65,66,67,68,69,70,000,72,73,74,75,76,000,78,000,000,000,000,000,000,000,000,000,000,000,000,91,92,93,000,95,96,97,98,99,000,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,
            000,121,122,123,124,125,126,127,128,129,130,000,132,133,134,135,136,000,138,000,140,141,142,143,144,145,146,147,148,149,000,151,152,153,000,155,156,157,158,159,000,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,
            000,181,182,183,184,185,186,187,188,189,190,000,192,193,194,195,196,000,198,000,200,201,202,203,204,205,206,207,208,209,000,211,212,213,000,215,216,217,218,219,000,221,222,223,224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,
            000,241,242,243,244,245,246,247,248,249,250,000,252,253,254,255,256,000,258,000,260,000,000,000,000,000,000,000,000,269,000,271,272,273,000,275,276,277,278,279,000,281,282,283,284,285,286,287,288,289,290,291,292,293,294,295,296,297,298,299,
            000,301,302,303,304,305,306,307,308,309,310,000,312,313,314,315,316,000,318,000,320,000,322,323,324,325,326,327,000,329,000,331,332,333,000,335,336,337,338,339,000,341,342,343,344,345,346,347,348,349,000,000,000,000,000,000,000,357,358,359,
            000,361,362,363,364,365,366,367,368,369,370,000,372,373,374,375,376,000,378,000,380,000,382,383,384,385,386,387,000,389,000,391,392,393,000,395,396,397,398,399,000,401,402,403,404,405,406,407,408,409,410,411,412,413,414,415,000,417,418,419,
            000,421,422,423,424,425,426,427,428,429,430,000,432,433,434,435,436,000,438,000,440,000,442,443,444,445,446,447,000,449,000,451,452,453,000,455,456,457,458,459,000,461,462,463,464,465,466,467,468,469,470,471,472,473,474,475,000,477,478,479,
            000,000,000,000,000,000,000,000,000,000,000,000,492,493,494,495,496,000,000,000,500,000,000,000,000,000,000,000,000,509,000,511,512,513,000,515,516,517,518,519,000,521,522,523,524,525,526,527,528,529,000,000,000,000,000,535,000,537,538,539,
            000,541,542,543,544,545,546,547,548,549,550,551,552,553,554,555,556,557,558,559,560,561,562,563,000,565,566,567,568,569,000,571,572,573,000,575,576,577,578,579,000,581,582,583,584,585,586,587,588,589,590,591,592,593,000,595,000,597,598,599,
            000,601,602,603,604,605,606,607,608,609,610,611,612,613,614,615,616,617,618,619,620,621,622,623,000,625,626,627,628,629,000,631,632,633,000,635,636,637,638,639,000,641,642,643,644,645,646,647,648,649,650,651,652,653,000,655,000,657,658,659,
            000,661,662,663,664,665,666,667,668,669,670,671,672,673,674,675,676,000,000,000,680,000,000,000,000,000,000,000,000,689,000,691,692,693,000,695,696,697,698,699,000,701,702,703,704,705,706,707,708,709,710,711,712,713,000,715,000,717,718,719,
            000,721,722,723,724,725,726,727,728,729,730,731,732,733,734,735,736,000,738,000,740,000,742,743,744,745,746,747,000,749,000,751,752,753,000,755,756,757,758,759,000,761,762,763,764,765,766,767,768,769,770,771,772,773,000,775,000,777,778,779,
            000,781,782,783,784,785,786,787,788,789,790,791,792,793,794,795,796,000,798,000,000,000,802,803,804,805,806,807,000,809,000,811,812,813,000,815,816,817,818,819,000,821,822,823,824,825,826,827,828,829,830,831,832,833,000,835,000,837,838,839,
            000,841,842,843,844,845,846,847,848,849,850,851,852,853,854,855,856,000,858,859,860,861,862,863,864,865,866,867,000,869,000,000,000,000,000,875,876,877,878,879,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,895,000,897,898,899,
            000,901,902,903,904,905,906,907,908,909,910,911,912,913,914,915,916,000,918,919,920,921,922,923,924,925,926,927,000,929,930,931,932,933,934,935,936,937,938,939,940,941,942,943,944,945,946,947,948,949,950,951,952,953,954,955,000,957,958,959,
            000,961,962,963,964,965,966,967,968,969,970,971,972,973,974,975,976,000,978,979,980,981,982,983,984,985,986,987,000,989,990,991,992,993,994,995,996,997,998,999,1000,1001,1002,1003,1004,1005,1006,1007,1008,1009,1010,1011,1012,1013,1014,1015,000,1017,1018,1019,
            000,1021,1022,1023,1024,1025,1026,1027,1028,1029,1030,1031,1032,1033,1034,1035,1036,000,1038,1039,1040,1041,1042,1043,1044,1045,1046,1047,000,000,000,000,000,000,000,1055,1056,1057,1058,1059,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,1077,1078,1079,
            000,1081,1082,1083,1084,1085,1086,1087,1088,1089,1090,1091,1092,1093,1094,1095,1096,000,1098,1099,1100,1101,1102,1103,1104,1105,1106,1107,1108,1109,1110,1111,1112,1113,000,1115,1116,1117,1118,1119,1120,1121,1122,1123,1124,1125,1126,1127,1128,1129,1130,1131,1132,1133,1134,1135,1136,1137,1138,1139,
            000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,
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
        if (i == 470 || i == 410){
            quad[0].color = sf::Color(255, 255, 255, 253);
            quad[1].color = sf::Color(255, 255, 255, 253);
            quad[2].color = sf::Color(255, 255, 255, 253);
            quad[3].color = sf::Color(255, 255, 255, 253);
        }
    }
}

bool Map::run() {
    m_window.setSize(sf::Vector2u(960, 320));
    sf::View view(sf::FloatRect(0, 0, 960, 320));
    m_window.setView(view);
    m_enemy2.setPositionEnemy(400, 160);
    m_enemy2.setTextureRectEnemy(sf::IntRect(0, 0, 16, 16));

    while (m_window.isOpen()) {
        sf::Event event;
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                m_window.close();
            }
        }

        m_player.handleInput();
        m_player.update(m_tilemap);
        if (m_enemy.checkIfPlayerSeesEnemy(m_player.getSprite()))
        {
            return true;
        }
        if (m_enemy2.checkIfPlayerSeesEnemy(m_player.getSprite()))
        {
            return true;
        }
        if (checkIfNextMap(m_player.getSprite()))
        {
            return true;
        }

        m_window.clear(sf::Color::White); // Background color for map

        // Bind the texture and draw the tilemap
        sf::RenderStates states;
        states.texture = &m_tileset;
        m_window.draw(m_tilemap, states);

        m_player.draw(m_window);
        m_enemy.draw(m_window);
        m_enemy2.draw(m_window);
        m_window.display();
    }

    return false;
}

bool Map::checkIfNextMap(sf::Sprite player_sprite)
{
    if ((std::fabs(player_sprite.getPosition().x - 800) < 16) && (std::fabs(player_sprite.getPosition().y - 92) < 16))
    {
        next_map = true;
        return true;
    }
    return false;
}

bool Map::getIsNextMap()
{
    return next_map;
}

//
// Created by Кежик Кызыл-оол on 2019-03-19.
//

#ifndef TANCHIKI_MATCH_HPP
#define TANCHIKI_MATCH_HPP


#include "GraphicsManager.hpp"
#include "PhysicsManager.hpp"
#include "ObjectManager.hpp"

class Match {
private:
    ObjectManager* objectManager;
public:
    ObjectManager *getObjectManager() const;

private:
    sf::RenderWindow& mainWindow;
    GraphicsManager* graphicsManager;
    PhysicsManager* physicsManager;
    std::string mapName;
    int myPlayerId;

    unsigned int amount_of_blocks_x, amount_of_blocks_y;
    block_t* blocks;
    sf::Texture textureMap;
    sf::Sprite spriteMap;
    sf::Image imagesForMap;

    unsigned int amount_of_players;
    std::vector <std::string> players_names;

public:
    Match(sf::RenderWindow &mainWindow, std::string players_info_json, std::string map_json);
    ~Match();

    void drawMatch();
    void updateMatch(float time);
    void processMessage(const std::string& message);
    const std::string &getMapName() const;
    void drawMap(sf::RenderWindow &window);

    block_t * getBlocks();

    unsigned int getAmountBlocksX();
    unsigned int getAmountBlocksY();

    void setBlock(int i, int j, block_t BL);

};


#endif //TANCHIKI_MATCH_HPP

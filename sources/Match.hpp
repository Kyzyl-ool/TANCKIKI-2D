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
    GraphicsManager* graphicsManager;
    PhysicsManager* physicsManager;
    std::string mapName;
    int myPlayerId;
public:
    int getMyPlayerId() const;

public:
    void setMyPlayerId(int myPlayerId);

private:

    unsigned int amount_of_blocks_x, amount_of_blocks_y;
    block_t* blocks;
    float deathTime;
    int deathLine;
    sf::Texture textureMap;
    sf::Sprite spriteMap;
    sf::Image imagesForMap;

    unsigned int amount_of_players;
    std::vector<std::pair <int, int> > playersInitialCoord;
    std::vector <std::string> players_names;
    std::vector <int> killed;

public:
    ObjectManager *getObjectManager() const;

    GraphicsManager *getGraphicsManager() const;

    Match(sf::RenderWindow &mainWindow, std::string players_info_json, std::string map_json, sf::View &view,
          int iMyPlayerId);
    ~Match();

    void drawMatch();
    void updateMatch(float time);
    void processMessage(const std::string &message, int iMyPlayerId);
    const std::string &getMapName() const;
    void drawMap(sf::RenderWindow &window);

    block_t * getBlocks();
    std::vector <int> getKilled();
    void setKilled(std::vector <int> killed_);

    unsigned int getAmountBlocksX();
    unsigned int getAmountBlocksY();

    void setBlock(int i, int j, block_t BL);

    void setPlayerCoordVorView();
    void setDeathTime(float dt);
    float getDeathTime();
    void setDeathLine(int dt);
    int getDeathTLine();
    float getMyPlayerX();
    float getMyPlayerY();
    void viewmap(float time);
    std::map <unsigned short, unsigned long> playerId_tankId;
};


#endif //TANCHIKI_MATCH_HPP

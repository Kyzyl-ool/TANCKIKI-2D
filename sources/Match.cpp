//
// Created by Кежик Кызыл-оол on 2019-03-19.
//

#include <string>
#include <iostream>
#include "Match.hpp"
#include "blocks.hpp"
#include "Tank.hpp"
#include "Ammunition.hpp"
#include "Repair.hpp"
#include "json/json.hpp"
#include "constants/messages.hpp"

using json = nlohmann::json;



Match::Match(sf::RenderWindow &mainWindow, std::string players_info_json, std::string map_json, sf::View &view,
             int iMyPlayerId) {
    deathTime = 0;
    deathLine = 0;
    json map_j = json::parse(map_json);
    mapName = map_j["mapName"];
    amount_of_blocks_x = map_j["amount_of_blocks_x"];
    amount_of_blocks_y = map_j["amount_of_blocks_y"];
    myPlayerId = iMyPlayerId;
    /*
     * {
     * "mapName": "Ugaagga",
     * "amount_of_blocks_x": 30,
     * "amount_of_blocks_y": 30,
     * "blocks": [1,1,1,1,2,2,2,2,2,3,3,3,3,3]
     * }
     */

    blocks = new block_t[amount_of_blocks_x*amount_of_blocks_y];
    std::vector<int> vec = map_j["blocks"].get< std::vector <int> >();
    for(int i=0;i < amount_of_blocks_y; ++i) {
        for(int j=0;j<amount_of_blocks_x;++j) {
            if(vec[amount_of_blocks_x * i + j] == 0)
                blocks[amount_of_blocks_x * i + j] = BL_0;
            if(vec[amount_of_blocks_x * i + j] == 1)
                blocks[amount_of_blocks_x * i + j] = BL_1;
        }
    }


    ///@todo заполнить blocks

    imagesForMap.loadFromFile(IMAGE_FOR_MAP);

    sf::Texture texture0;
    texture0.loadFromImage(imagesForMap,sf::IntRect(64,0,64,64));

    sf::Texture texture1;
    texture1.loadFromImage(imagesForMap,sf::IntRect(0,0,64,64));

    textureMap.create(64*amount_of_blocks_x,64*amount_of_blocks_y);

    for(int i =0;i< amount_of_blocks_y; ++i) {
        for(int j=0;j<amount_of_blocks_x; ++j) {
            if(blocks[amount_of_blocks_x*i+j]==BL_0) {
                textureMap.update(texture0, 64*j, 64*i);
            }
            if(blocks[amount_of_blocks_x*i+j]==BL_1) {
                textureMap.update(texture1, 64*j, 64*i);
            }
        }
    }
    spriteMap.setTexture(textureMap);
    spriteMap.setScale(((float)MAP_WIDTH)/amount_of_blocks_x/64, ((float)MAP_HEIGHT)/amount_of_blocks_y/64);


    objectManager = new ObjectManager(mainWindow);
    graphicsManager = new GraphicsManager(objectManager, blocks, amount_of_blocks_y, amount_of_blocks_x, mainWindow, view);
    physicsManager = new PhysicsManager(objectManager);

    ///@todo распарсить players_info_json

    json players_info_j = json::parse(players_info_json);

    /*
     * {
     * "amount_of_players": 3,
     * "players_names": ["Maxim", "Artem", "Kezhik"]
     * ["players_names"].get< std::vector <std::string> >()
     * }
     */


    amount_of_players = players_info_j["amount_of_players"];
    players_names = players_info_j["players_names"].get< std::vector <std::string> >();
    std::vector<int> vect (players_names.size(), 0);
    killed = vect;
    ///@todo заполнить players_names
    srand(time(NULL));
    ///@todo решить, с какими начальными координатами ставить игроков на карту

    std::vector<int> playersInitialCoordin = players_info_j["playersInitialCoord"].get< std::vector <int> >();
    for(int i = 0; i < amount_of_players; ++i) {
        std::pair <int, int> p;
        p.first = (MAP_WIDTH/amount_of_blocks_x)*playersInitialCoordin[2*i];
        p.second = (MAP_HEIGHT/amount_of_blocks_y)*playersInitialCoordin[2*i+1];
        playersInitialCoord.push_back(p);
    }
    ///@todo заполнить playersInitialCoordinates

    ///@todo создать amount_of_players танков

    for(int i = 0; i < amount_of_players; ++i) {
        Tank *tank = new Tank(1000, players_names[i], "blue1");
        tank->setPosition(playersInitialCoord[i].first, playersInitialCoord[i].second);
        tank->setObjectId(i);
        tank->setTypeBullet(MIDDLESHOT);
        tank->setOwnerId(i);
        objectManager->addGameObject(tank);
    }

    for(int l =0; l < 10; ++l) {
        Ammunition *amm = new Ammunition(2);
        int i = rand() % (amount_of_blocks_x * amount_of_blocks_y);
        while (blocks[i] != BL_1) {
            i = rand() % (amount_of_blocks_x * amount_of_blocks_y);
        }
        amm->setPosition((i % amount_of_blocks_x + 0.5)*MAP_WIDTH/amount_of_blocks_x, (i / amount_of_blocks_x + 0.5)*MAP_HEIGHT/amount_of_blocks_y);
        objectManager->addGameObject(amm);
    }

    for(int l =0; l < 5; ++l) {
        Repair *rep = new Repair(500);
        int i = rand() % (amount_of_blocks_x * amount_of_blocks_y);
        while (blocks[i] != BL_1) {
            i = rand() % (amount_of_blocks_x * amount_of_blocks_y);
        }
        rep->setPosition((i % amount_of_blocks_x + 0.5)*MAP_WIDTH/amount_of_blocks_x, (i / amount_of_blocks_x + 0.5)*MAP_HEIGHT/amount_of_blocks_y);
        objectManager->addGameObject(rep);
    }
}

std::vector <int> Match::getKilled() {
    return  killed;
}

void Match::setKilled(std::vector <int> killed_) {
    killed = killed_;
}


void Match::drawMatch() {
    drawMap(graphicsManager->getWindow());
    graphicsManager->drawGameObjects();
}

void Match::updateMatch(float time) {
    setDeathTime(deathTime+time);
    if(deathTime > DEATH_TIME) {
        setDeathLine(deathLine + 1);
        setDeathTime(deathTime - DEATH_TIME);

        sf::Texture texture1, texture2;
        texture1.loadFromImage(imagesForMap,sf::IntRect(192,0,64,64));
        texture2.loadFromImage(imagesForMap,sf::IntRect(448,0,64,64));
        if(deathLine==1){
            for(int i =0;i< amount_of_blocks_y; ++i) {
                if(blocks[amount_of_blocks_x*i+0]== BL_1)
                    textureMap.update(texture1, 0, 64*i);
                if(blocks[amount_of_blocks_x*i+0]== BL_0)
                    textureMap.update(texture2, 0, 64*i);
                if(blocks[amount_of_blocks_x*i+amount_of_blocks_x-1]== BL_1)
                    textureMap.update(texture1, 64*(amount_of_blocks_x-1), 64*i);
                if(blocks[amount_of_blocks_x*i+amount_of_blocks_x-1]== BL_0)
                    textureMap.update(texture2, 64*(amount_of_blocks_x-1), 64*i);
            }
            for(int j=0;j<amount_of_blocks_x; ++j) {
                if(blocks[0+j]== BL_1)
                    textureMap.update(texture1, 64*j, 0);
                if(blocks[0+j]== BL_0)
                    textureMap.update(texture2, 64*j, 0);
                if(blocks[amount_of_blocks_x*(amount_of_blocks_y-1)+j]== BL_1)
                    textureMap.update(texture1, 64*j, 64*(amount_of_blocks_y-1));
                if(blocks[amount_of_blocks_x*(amount_of_blocks_y-1)+j]== BL_0)
                    textureMap.update(texture2, 64*j, 64*(amount_of_blocks_y-1));
            }
        }
        if(deathLine<amount_of_blocks_y/3) {
            for (int i = 0; i < amount_of_blocks_y; ++i) {
                for (int j = 0; j < amount_of_blocks_x; ++j) {
                    if (i == deathLine || i == amount_of_blocks_y - deathLine-1 || j == deathLine || j == amount_of_blocks_x - deathLine-1) {
                        if (blocks[amount_of_blocks_x * i + j] == BL_1)
                            textureMap.update(texture1, 64 * j, 64 * i);
                        if (blocks[amount_of_blocks_x * i + j] == BL_0)
                            textureMap.update(texture2, 64 * j, 64 * i);
                    }
                }
            }
            spriteMap.setTexture(textureMap);
            spriteMap.setScale(((float) MAP_WIDTH) / amount_of_blocks_x / 64,
                               ((float) MAP_HEIGHT) / amount_of_blocks_y / 64);
        }
    }
    physicsManager->updateGameObjects(this, time);
}

const std::string &Match::getMapName() const {
    return mapName;
}

void Match::processMessage(const std::string &message, int iMyPlayerId = -1) {
    assert(message.size());
//    std::cout << message << std::endl;
    json j = json::parse(message.c_str());
//    std::cout << j["status"] << std::endl;s
//    std::cout << j["from"] << std::endl;
//    std::cout << j["params"] << std::endl;
    unsigned short from = j["from"];
//    auto tankId = (gameObjectMessageId[j["method"]] != GAMEOBJECT_MESSAGE_APPEAR) ? playerId_tankId[from] : -1;
    int tankId = from;

    if (iMyPlayerId != tankId)
    switch (gameObjectMessageId[j["method"]]) {
        case GAMEOBJECT_MESSAGE_NO_ROTATION: {
                objectManager->getTankById(tankId)->stopRotate();
            break;
        }
        case GAMEOBJECT_MESSAGE_MOVE_BRAKE: {
                objectManager->getTankById(tankId)->brake();
            break;
        }
        case GAMEOBJECT_MESSAGE_MOVE_LEFT: {
                objectManager->getTankById(tankId)->rotateLeft();
            break;
        }
        case GAMEOBJECT_MESSAGE_MOVE_RIGHT: {
                objectManager->getTankById(tankId)->rotateRight();
            break;
        }
        case GAMEOBJECT_MESSAGE_MOVE_FORWARD: {
                objectManager->getTankById(tankId)->go();
            break;
        }
        case GAMEOBJECT_MESSAGE_NO_ACTION: {
                objectManager->getTankById(tankId)->stop();
            break;
        }
        case GAMEOBJECT_MESSAGE_SHOOT: {
            GameObject* bullet = objectManager->getGameObjectById(tankId)->shot();
            if(bullet) objectManager->addGameObject(bullet);
            break;
        }
        case GAMEOBJECT_MESSAGE_SYNC: {
                std::vector<float> params = j["params"].get<std::vector<float> >();
                objectManager->getTankById(tankId)->setConfiguration(
                        params[0],
                        params[1],
                        params[2],
                        params[3],
                        params[4],
                        params[5],
                        params[6],
                        (int) params[7],
                        params[8], params[9]);
            break;
        }
        case GAMEOBJECT_MESSAGE_ROTATE_TOWER: {
            auto tmp = j["params"].get <std::vector <float> >();
            objectManager->getTankById(tankId)->setTowerX(tmp[0]);
            objectManager->getTankById(tankId)->setTowerY(tmp[1]);
//            objectManager->getTankById(tankId)->setTow;

            break;
        }
        case GAMEOBJECT_MESSAGE_ROTATE_TOWER_LEFT: {
//            if (myPlayerId != tankId)
                objectManager->getTankById(tankId)->setSpeedTower(TANK_TOWER_SPEED);
            break;
        }
        case GAMEOBJECT_MESSAGE_ROTATE_TOWER_RIGHT: {
//            if (myPlayerId != tankId)
                objectManager->getTankById(tankId)->setSpeedTower(-TANK_TOWER_SPEED);
            break;
        }
        case GAMEOBJECT_MESSAGE_ROTATE_TOWER_STOP: {
//            if (myPlayerId != tankId)
                objectManager->getTankById(tankId)->setSpeedTower(0);
            break;
        }

//        case GAMEOBJECT_MESSAGE_APPEAR: {
//            auto params = j["params"].get <std::vector <unsigned short> >();
//            auto iCoordinates = j["initialCoordinates"].get <std::vector <float> >();
//            Tank *tank = new Tank(50, "ChickenKiller", "green1");
//            tank->setPosition(iCoordinates[0]*WINDOW_WIDTH, iCoordinates[1]*WINDOW_HEIGHT);
//            playerId_tankId[params[0]] = objectManager->addGameObject(tank);
//            break;
//        }
    }
}

void Match::drawMap(sf::RenderWindow &window) {
    window.draw(spriteMap);
}

void Match::setBlock(int i, int j, block_t BL) {
    blocks[30*i+j]=BL;
    sf::Texture texture;
    if(BL==BL_0) {
        texture.loadFromImage(imagesForMap, sf::IntRect(256,16,16,16));
        textureMap.update(imagesForMap, j*((float)MAP_WIDTH)/amount_of_blocks_x,  i*((float)MAP_HEIGHT)/amount_of_blocks_y);
    }
    if(BL==BL_1) {
        texture.loadFromImage(imagesForMap, sf::IntRect(272,32,16,16));
        textureMap.update(imagesForMap, j*((float)MAP_WIDTH)/amount_of_blocks_x,  i*((float)MAP_HEIGHT)/amount_of_blocks_y);
    }
}

block_t * Match::getBlocks() {
    return blocks;
}

unsigned int Match::getAmountBlocksX() {
    return amount_of_blocks_x;
}

unsigned int Match::getAmountBlocksY() {
    return amount_of_blocks_y;
}

ObjectManager *Match::getObjectManager() const {
    return objectManager;
}

void Match::setDeathTime(float dt) {
    deathTime = dt;
}

float Match::getDeathTime() {
    return deathTime;
}

void Match::setDeathLine(int dt) {
    deathLine = dt;
}

int Match::getDeathTLine() {
    return deathLine;
}

Match::~Match() {
    delete(graphicsManager);
    delete(physicsManager);
    delete(objectManager);
    delete(blocks);
}

float Match::getMyPlayerX() {
    return objectManager->getObjects()[myPlayerId]->getX();
}

float Match::getMyPlayerY() {
    return objectManager->getObjects()[myPlayerId]->getY();
}

void Match::setMyPlayerId(int myPlayerId) {
    Match::myPlayerId = myPlayerId;
}

int Match::getMyPlayerId() const {
    return myPlayerId;
}

void Match::setPlayerCoordVorView() {
    float x = getMyPlayerX();
    float y = getMyPlayerY();
    if(x < (float)(WINDOW_WIDTH)/2) x = (float)WINDOW_WIDTH/2;
    if(x > MAP_WIDTH-(float)(WINDOW_WIDTH)/2) x = MAP_WIDTH-(float)(WINDOW_WIDTH)/2;
    if(y < (float)(WINDOW_HEIGHT)/2) y = (float)WINDOW_HEIGHT/2;
    if(y > MAP_HEIGHT-(float)(WINDOW_HEIGHT)/2) y = MAP_HEIGHT-(float)(WINDOW_HEIGHT)/2;
    graphicsManager->getView().setCenter(x, y); //следим за игроком, передавая его координаты.
}

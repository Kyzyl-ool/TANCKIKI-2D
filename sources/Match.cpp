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
    texture0.loadFromImage(imagesForMap,sf::IntRect(256,16,16,16));

    sf::Texture texture1;
    texture1.loadFromImage(imagesForMap,sf::IntRect(272,32,16,16));

    textureMap.create(16*amount_of_blocks_x,16*amount_of_blocks_y);

    for(int i =0;i< amount_of_blocks_y; ++i) {
        for(int j=0;j<amount_of_blocks_x; ++j) {
            if(blocks[amount_of_blocks_x*i+j]==BL_0) {
                textureMap.update(texture0, 16*j, 16*i);
            }
            if(blocks[amount_of_blocks_x*i+j]==BL_1) {
                textureMap.update(texture1, 16*j, 16*i);
            }
        }
    }
    spriteMap.setTexture(textureMap);
    spriteMap.setScale(((float)MAP_WIDTH)/amount_of_blocks_x/16, ((float)MAP_HEIGHT)/amount_of_blocks_y/16);


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
    ///@todo заполнить players_names
    srand(time(NULL));
    ///@todo решить, с какими начальными координатами ставить игроков на карту

    std::vector<int> playersInitialCoordin = players_info_j["playersInitialCoord"].get< std::vector <int> >();
    for(int i = 0; i < amount_of_players; ++i) {
        playersInitialCoord[i].first = playersInitialCoordin[2*i];
        playersInitialCoord[i].second = playersInitialCoordin[2*i+1];
    }
    ///@todo заполнить playersInitialCoordinates

    ///@todo создать amount_of_players танков

    for(int i = 0; i < amount_of_players; ++i) {
        Tank *tank = new Tank(1000, players_names[i], "blue1");
        tank->setPosition(playersInitialCoord[i].first, playersInitialCoord[i].second);
        tank->setObjectId(i);
        tank->setTypeBullet(MIDDLESHOT);
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

    ///@todo передать все эти танки в objectManager, вызывая у него addGameObject

    ///@todo узнать свой player_id (подумать, кто будет назначать player_id)
}

void Match::drawMatch() {
    drawMap(graphicsManager->getWindow());
    graphicsManager->drawGameObjects();
}

void Match::updateMatch(float time) {
    setDeathTime(getDeathTime()+time);
    if(getDeathTime() > DEATH_TIME) {
        setDeathLine(getDeathTLine() + 1);
        setDeathTime(getDeathTime() - DEATH_TIME);

        sf::Texture texture;
        sf::Image image;
        image.create(16,16,sf::Color::Red);
        texture.loadFromImage(image,sf::IntRect(0,0,16,16));
        textureMap.create(16*amount_of_blocks_x,16*amount_of_blocks_y);
        for(int i =0;i< amount_of_blocks_y; ++i) {
            for(int j=0;j<amount_of_blocks_x; ++j) {
                if(i<=deathLine || i >= amount_of_blocks_y - deathLine || j<=deathLine || j >= amount_of_blocks_x - deathLine) {
                    textureMap.update(texture, 16*j, 16*i);
                }
            }
        }
        spriteMap.setTexture(textureMap);
        spriteMap.setScale(((float)MAP_WIDTH)/amount_of_blocks_x/16, ((float)MAP_HEIGHT)/amount_of_blocks_y/16);
    }
    physicsManager->updateGameObjects(this, time);
}

const std::string &Match::getMapName() const {
    return mapName;
}

void Match::processMessage(std::string message) {
    ///@todo распарсить message
    assert(message.size());
    json j = json::parse(message.c_str());
//    std::cout << j["status"] << std::endl;s
//    std::cout << j["from"] << std::endl;
//    std::cout << j["method"] << std::endl;
//    std::cout << j["params"] << std::endl;


    switch (gameObjectMessageId[j["method"]]) {
        case GAMEOBJECT_MESSAGE_NO_ROTATION: {
            objectManager->getGameObjectById(0)->stopRotate();
            break;
        }
        case GAMEOBJECT_MESSAGE_MOVE_BRAKE: {
            objectManager->getGameObjectById(0)->brake();
            break;
        }
        case GAMEOBJECT_MESSAGE_MOVE_LEFT: {
            objectManager->getGameObjectById(0)->rotateLeft();
            break;
        }
        case GAMEOBJECT_MESSAGE_MOVE_RIGHT: {
            objectManager->getGameObjectById(0)->rotateRight();
            break;
        }
        case GAMEOBJECT_MESSAGE_MOVE_FORWARD: {
            objectManager->getGameObjectById(0)->go();
            break;
        }
        case GAMEOBJECT_MESSAGE_NO_ACTION: {
            objectManager->getGameObjectById(0)->stop();
            break;
        }
        case GAMEOBJECT_MESSAGE_SHOOT: {
            GameObject* bullet = objectManager->getGameObjectById(0)->shot();
            if(bullet) objectManager->addGameObject(bullet);
            break;
        }
    }
    ///@todo обработать message
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

void Match::setPlayerCoordVorView() {
    float x = getMyPlayerX();
    float y = getMyPlayerY();
    if(x < (float)(WINDOW_WIDTH)/2) x = (float)WINDOW_WIDTH/2;
    if(x > MAP_WIDTH-(float)(WINDOW_WIDTH)/2) x = MAP_WIDTH-(float)(WINDOW_WIDTH)/2;
    if(y < (float)(WINDOW_HEIGHT)/2) y = (float)WINDOW_HEIGHT/2;
    if(y > MAP_HEIGHT-(float)(WINDOW_HEIGHT)/2) y = MAP_HEIGHT-(float)(WINDOW_HEIGHT)/2;
    graphicsManager->getView().setCenter(x, y); //следим за игроком, передавая его координаты.
}

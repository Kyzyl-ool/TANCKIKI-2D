//
// Created by Кежик Кызыл-оол on 2019-03-19.
//

#include <string>
#include <iostream>
#include "Match.hpp"
#include "blocks.hpp"
#include "Tank.hpp"
#include "json/json.hpp"
#include "constants/messages.hpp"

using json = nlohmann::json;



Match::Match(sf::RenderWindow &mainWindow, std::string players_info_json, std::string map_json) {
    ///@todo распарсить map_json
    mapName = "MAP_NAME";
    amount_of_blocks_x = 30;
    amount_of_blocks_y = 30;;

    blocks = new block_t[amount_of_blocks_x*amount_of_blocks_y];
    for(int i=0;i < amount_of_blocks_y; ++i) {
        for(int j=0;j<amount_of_blocks_x;++j) {
            if((i==0 || i == 29 || j ==0 || j==20 || j==29))
                blocks[amount_of_blocks_x*i+j]=BL_0;
            else  blocks[amount_of_blocks_x*i+j]=BL_1;
        }
        blocks[50]=BL_1; blocks[80]=BL_1; blocks[110]=BL_1; blocks[320]=BL_1; blocks[350]=BL_1;
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
    spriteMap.setScale((float)WINDOW_WIDTH/amount_of_blocks_y/16, (float)WINDOW_HEIGHT/amount_of_blocks_x/16);


    objectManager = new ObjectManager(mainWindow);
    graphicsManager = new GraphicsManager(objectManager, blocks, amount_of_blocks_y, amount_of_blocks_x, mainWindow);
    physicsManager = new PhysicsManager(objectManager);

    ///@todo распарсить players_info_json
    amount_of_players = 3;
    players_names = std::vector <std::string> (amount_of_players);
    ///@todo заполнить players_names

    ///@todo решить, с какими начальными координатами ставить игроков на карту
    std::pair <int, int> playersInitialCoordinates[amount_of_players];
    ///@todo заполнить playersInitialCoordinates

    ///@todo создать amount_of_players танков
    ///@todo передать все эти танки в objectManager, вызывая у него addGameObject

    ///@todo узнать свой player_id (подумать, кто будет назначать player_id)

    Tank *tank2 = new Tank(50);
    tank2->setTexture("images/tanks_16.png");
    tank2->setSprite(96,48,16,16);  //задает вид спрайта на основе уже имеющейся тестуры
    tank2->setPosition(100, 100);
    tank2->setSizeSprite(50,50);
    tank2->setSizeObj(50,50);
    tank2->setAlive(true);
    tank2->setObjectId(1);
    objectManager->addGameObject(tank2);

    for(int p=4; p<5;++p) {
        GameObject *bul = tank2->shot(LOWSHOT);
        bul->setAlive(true);
        bul->setObjectId(p);
        objectManager->addGameObject(bul);
    }

    Tank *tank1 = new Tank(50);
    tank1->setTexture("images/tanks_16.png");
    tank1->setSprite(96,48,16,16);  //задает вид спрайта на основе уже имеющейся тестуры
    tank1->setPosition(300, 100);
    tank1->setSizeSprite(50,50);
    tank1->setSizeObj(50,50);
    tank1->setAlive(true);
    tank1->setObjectId(3);
    objectManager->addGameObject(tank1);
}

void Match::drawMatch() {
    drawMap(graphicsManager->getWindow());
    graphicsManager->drawGameObjects();
}

void Match::updateMatch() {
    physicsManager->updateGameObjects(this);
}

const std::string &Match::getMapName() const {
    return mapName;
}

#define TANK_VELOCITY_X 1
#define TANK_VELOCITY_Y 1
void Match::processMessage(std::string message) {
    ///@todo распарсить message
    assert(message.size());
    json j = json::parse(message.c_str());
//    std::cout << j["status"] << std::endl;s
//    std::cout << j["from"] << std::endl;
//    std::cout << j["method"] << std::endl;
//    std::cout << j["params"] << std::endl;


    switch (gameObjectMessageId[j["method"]]) {
        case GAMEOBJECT_MESSAGE_MOVE_DOWN: {
            objectManager->getGameObjectById(0)->setSpeed(0,TANK_VELOCITY_Y);
            objectManager->getGameObjectById(0)->setRotation(90);
            break;
        }
        case GAMEOBJECT_MESSAGE_MOVE_LEFT: {
            objectManager->getGameObjectById(0)->setSpeed(-TANK_VELOCITY_X,0);
            objectManager->getGameObjectById(0)->setRotation(180);
            break;
        }
        case GAMEOBJECT_MESSAGE_MOVE_RIGHT: {
            objectManager->getGameObjectById(0)->setSpeed(TANK_VELOCITY_X,0);
            objectManager->getGameObjectById(0)->setRotation(0);
            break;
        }
        case GAMEOBJECT_MESSAGE_MOVE_UP: {
            auto t = objectManager->getTanks();
            objectManager->getGameObjectById(0)->setSpeed(0,-TANK_VELOCITY_Y);
            objectManager->getGameObjectById(0)->setRotation(270);
            break;
        }
        case GAMEOBJECT_MESSAGE_STOP: {
            objectManager->getGameObjectById(0)->setSpeed(0,0);
            break;
        }
        case GAMEOBJECT_MESSAGE_SHOOT: {
            objectManager->addGameObject(objectManager->getGameObjectById(0)->shot(LOWSHOT));
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
        textureMap.update(imagesForMap, j*WINDOW_WIDTH/amount_of_blocks_x,  i*WINDOW_HEIGHT/amount_of_blocks_y);
    }
    if(BL==BL_1) {
        texture.loadFromImage(imagesForMap, sf::IntRect(272,32,16,16));
        textureMap.update(imagesForMap, j*WINDOW_WIDTH/amount_of_blocks_x,  i*WINDOW_HEIGHT/amount_of_blocks_y);
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

Match::~Match() {
    delete(blocks);
    delete(graphicsManager);
    delete(physicsManager);
    delete(objectManager);
    for(const auto &object : objectManager->getObjects()) {
        delete(object);
    }
}




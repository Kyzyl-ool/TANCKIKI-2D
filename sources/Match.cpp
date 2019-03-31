//
// Created by Кежик Кызыл-оол on 2019-03-19.
//

#include <string>
#include <iostream>
#include "Match.hpp"
#include "blocks.hpp"
#include "Tank.hpp"
#include "json/json.hpp"
#include "messages.hpp"

using json = nlohmann::json;


Match::Match(sf::RenderWindow *mainWindow, std::string players_info_json, std::string map_json) {
    ///@todo распарсить map_json
    mapName = "MAP_NAME";
    amount_of_blocks_x = 30;
    amount_of_blocks_y = 30;
    blocks = new block_t[amount_of_blocks_x*amount_of_blocks_y];
    ///@todo заполнить blocks


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

    Tank *tank2 = new Tank();
    tank2->setTexture("images/tanks_16.png");
    tank2->setSprite(96,48,16,16);  //задает вид спрайта на основе уже имеющейся тестуры
    tank2->setPosition(100, 100);
    tank2->setSizeSprite(50,50);
    tank2->setSizeObj(50,50);
    tank2->setAlive(true);
    objectManager->addGameObject(tank2);

    Tank *tank1 = new Tank();
    tank1->setTexture("images/tanks_16.png");
    tank1->setSprite(96,48,16,16);  //задает вид спрайта на основе уже имеющейся тестуры
    tank1->setPosition(200, 200);
    tank1->setSizeSprite(50,50);
    tank1->setSizeObj(50,50);
    tank1->setAlive(true);
    objectManager->addGameObject(tank1);
}

void Match::drawMatch() {
    graphicsManager->drawGameObjects();
}

void Match::updateMatch() {
    physicsManager->updateGameObjects();
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
//    std::cout << j["status"] << std::endl;
//    std::cout << j["from"] << std::endl;
//    std::cout << j["method"] << std::endl;
//    std::cout << j["params"] << std::endl;


    switch (gameObjectMessageId[j["method"]]) {
        case GAMEOBJECT_MESSAGE_MOVE_DOWN: {
            objectManager->getGameObjectById(0)->setSpeed(0,TANK_VELOCITY_Y);
            objectManager->getGameObjectById(0)->setRotation(270);
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
            objectManager->getGameObjectById(0)->setSpeed(0,-TANK_VELOCITY_Y);
            objectManager->getGameObjectById(0)->setRotation(90);
            break;
        }
        case GAMEOBJECT_MESSAGE_STOP: {
            objectManager->getGameObjectById(0)->setSpeed(0,0);
            break;
        }
    }
    ///@todo обработать message
}



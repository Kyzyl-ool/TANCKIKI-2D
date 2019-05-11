//
// Created by Кежик Кызыл-оол on 2019-03-19.
//

#include <iostream>
#include <stdio.h>
#include "EventManager.hpp"
#include "json/json.hpp"
#include "Tank.hpp"
#include <vector>

using json = nlohmann::json;

bool EventManager::pollEvent() {
    return mainWindow.pollEvent(event);
}

EventManager::EventManager(sf::RenderWindow &theMainWindow, sf::Event &the_event, int playerId, gameState_t *the_state,
                           tgui::Gui &the_gui, InterfaceManager &interfaceManager)
        :
        mainWindow(theMainWindow),
playerId(playerId),
gui(the_gui),
event(the_event),
interfaceManager(interfaceManager)
{
    state = the_state;
}

std::string EventManager::getMessageFromGameObjects() {
    ///@todo реализовать согласно ТЗ

    if (pollEvent())
    {
        switch (*state) {
            case GAME_STATE_MULTIPLAYER_MATCH:
            case GAME_STATE_MATCH: {
                return returnMessageFromMatchActions();
            }
            case GAME_STATE_MATCH_PAUSE: {
                handleMatchPauseActions();
                break;
            }
            default:
                break;
        }
    }
    return std::string();
}

std::string EventManager::returnMessageFromMatchActions() {
    bool labeled = sf::Keyboard::isKeyPressed(sf::Keyboard::Tab);
    if (labeled) {
        interfaceManager.showHealth();
    } else {
        interfaceManager.cancelShow();
    }

    char arrows = getPressedArrows(sf::Keyboard::Left, sf::Keyboard::Down, sf::Keyboard::Up, sf::Keyboard::Right);
        switch (event.type) {
            case sf::Event::KeyReleased: {
                switch (event.key.code) {
                    case sf::Keyboard::A:
                    case sf::Keyboard::D:
                    case sf::Keyboard::Left:
                    case sf::Keyboard::Right: {
                        if (arrows & 0b1000 || arrows & 0b0001) {
                            return goMessage(arrows);
                        }
                            json json_message;
                            json_message["status"] = "OK";
                            json_message["from"] = playerId;
                            json_message["method"] = "noRotation";
                            json_message["params"] = json::array();
//                    std::cout << json_message.dump();
                            return json_message.dump();

                    }
                    case sf::Keyboard::Up:
                    case sf::Keyboard::Down:
                    case sf::Keyboard::S:
                    case sf::Keyboard::W:
                    {
                        json json_message;
                        json_message["status"] = "OK";
                        json_message["from"] = playerId;
                        json_message["method"] = "stop";
                        json_message["params"] = json::array();
//                    std::cout << json_message.dump();
                        return json_message.dump();
                    }
                    default:
                        break;
                }
                break;
            }
            case sf::Event::KeyPressed: {
                switch (event.key.code) {
                    case sf::Keyboard::Space: {
                        json json_message;
                        json_message["status"] = "OK";
                        json_message["from"] = playerId;
                        json_message["method"] = "shoot";
                        json_message["params"] = json::array({});
//                        std::cout << json_message.dump() << std::endl;
                        return json_message.dump();
                    }
                    case sf::Keyboard::Left:
                    case sf::Keyboard::A: {
                        return goMessage(0b1000);
                    }
                    case sf::Keyboard::Right:
                    case sf::Keyboard::D: {
                        return goMessage(0b0001);
                    }
                    case sf::Keyboard::Up:
                    case sf::Keyboard::W: {
                        return goMessage(0b0010);
                    }
                    case sf::Keyboard::Down:
                    case sf::Keyboard::S: {
                        return goMessage(0b0100);
                    }
                    case sf::Keyboard::Escape: {
                        *state = GAME_STATE_MATCH_PAUSE;
//                    std::cout << "Game state is MATCH_PAUSE\n";
                        ///@todo return json message with paused state
                        break;
                    }
                    default: {
//                    std::cout << "You pressed " << event.key.code << std::endl;
                        break;
                    }
                }
                break;
            }
            case sf::Event::Closed: {
                mainWindow.close();
                ///@todo return json message about closing
                break;
            }
            default:
                break;
    }
    return std::string();
}

void EventManager::handleMatchPauseActions() {
    switch (event.type)
    {
        case sf::Event::Closed: {
            mainWindow.close();
            ///@todo return json message about closing
            break;
        }
        case sf::Event::KeyPressed: {
            switch (event.key.code) {
                case sf::Keyboard::Escape: {
                    *state = GAME_STATE_MATCH;
//                    std::cout << "Game state is MATCH\n";
                    break;
                }
                default:
                    break;
            }
            break;
        }
        default:
            break;
    }

}

char EventManager::getPressedArrows(sf::Keyboard::Key left, sf::Keyboard::Key down, sf::Keyboard::Key up,
                                    sf::Keyboard::Key right) {
    assert(left);
    assert(down);
    assert(up);
    assert(right);
    char result = 0;
    if (sf::Keyboard::isKeyPressed(left))
        result |= 0b1000;
    if (sf::Keyboard::isKeyPressed(down))
        result |= 0b0100;
    if (sf::Keyboard::isKeyPressed(up))
        result |= 0b0010;
    if (sf::Keyboard::isKeyPressed(right))
        result |= 0b0001;

    return result;
}

std::string EventManager::goMessage(char direction) {
    switch (direction) {
        case 0b1000: {
            json json_message;
            json_message["status"] = "OK";
            json_message["from"] = playerId;
            json_message["method"] = "moveLeft";
            json_message["params"] = json::array();
//                    std::cout << json_message.dump();
            return json_message.dump();
        }
        case 0b0100: {
            json json_message;
            json_message["status"] = "OK";
            json_message["from"] = playerId;
            json_message["method"] = "moveDown";
            json_message["params"] = json::array();
//                    std::cout << json_message.dump();
            return json_message.dump();
        }
        case 0b0010: {
            json json_message;
            json_message["status"] = "OK";
            json_message["from"] = playerId;
            json_message["method"] = "moveUp";
            json_message["params"] = json::array();
//                    std::cout << json_message.dump();
            return json_message.dump();
        }
        case 0b0001: {
            json json_message;
            json_message["status"] = "OK";
            json_message["from"] = playerId;
            json_message["method"] = "moveRight";
            json_message["params"] = json::array();
//                    std::cout << json_message.dump();
            return json_message.dump();
        }
        default: {
            return std::string ();
//            assert(!"Invalid direction.");
        }
    }
}

void EventManager::setPlayerId(int playerId) {
    EventManager::playerId = playerId;
}

ObjectManager *EventManager::getObjectManager() const {
    return objectManager;
}

void EventManager::setObjectManager(ObjectManager *iobjectManager) {
    EventManager::objectManager = iobjectManager;
}

#define MILLISECONDS_TO_SEND_SYNC_MESSAGE 250
std::string EventManager::getSyncMessage() {
    if (syncClock.getElapsedTime().asMilliseconds() > MILLISECONDS_TO_SEND_SYNC_MESSAGE) {
        syncClock.restart();

        Tank* myTank = objectManager->getTankById(playerId);

        json json_message;
        json_message["status"] = "OK";
        json_message["from"] = playerId;
        json_message["method"] = "sync";
        json_message["params"] = { (int)(myTank->getX() * 100)/100., (int)(myTank->getY() * 100)/100., (int)(myTank->getHealth() * 100)/100., (int)(myTank->getSpeedTower() * 100)/100., (int)(myTank->getRecharge() * 100)/100., (int)(myTank->getTowerX() * 100)/100., (int)(myTank->getTowerY() * 100)/100., myTank->getAmmun(), myTank->getRotation(), myTank->getTowerRotation()};
        return json_message.dump();
    }
    else
        return "";
}

std::string EventManager::getMouseMessage() {
//                    auto tmp = sf::Mouse::getPosition(mainWindow);
//                int sinus = tmp->checkOrient(tmp1.x, tmp1.y);
//                if(sinus>0)
//                    tmp->setSpeedTower(TANK_TOWER_SPEED);
//                else
//                    tmp->setSpeedTower(-TANK_TOWER_SPEED);
//                if(sinus < 10 && sinus > -10)
//                    tmp->setSpeedTower(0);


    Tank* myTank = objectManager->getTankById(playerId);
    auto tmp = sf::Mouse::getPosition(mainWindow);
    float sinus = myTank->checkOrient(tmp.x, tmp.y);

//    std::cout << sinus << std::endl;

    if (sinus < 10 && sinus > -10) {
        if (myTank->getSpeedTower() != 0) {
            json json_message;
            json_message["status"] = "OK";
            json_message["from"] = playerId;
            json_message["method"] = "rotateTowerStop";
            json_message["params"] = json::array();
            return json_message.dump();
        }
        else
            return std::string();
    }

    if(sinus>0) {
        if (myTank->getSpeedTower() <= 0) {
            json json_message;
            json_message["status"] = "OK";
            json_message["from"] = playerId;
            json_message["method"] = "rotateTowerLeft";
            json_message["params"] = json::array();
            return json_message.dump();
        }
        else
            return std::string();
    }
    else {
        if (myTank->getSpeedTower() >= 0) {
            json json_message;
            json_message["status"] = "OK";
            json_message["from"] = playerId;
            json_message["method"] = "rotateTowerRight";
            json_message["params"] = json::array();
            return json_message.dump();
        }
        else
            return std::string();
    }
    return std::string();
}

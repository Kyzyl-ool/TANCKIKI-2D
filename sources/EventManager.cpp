//
// Created by Кежик Кызыл-оол on 2019-03-19.
//

#include <iostream>
#include <stdio.h>
#include "EventManager.hpp"
#include "json/json.hpp"
using json = nlohmann::json;

bool EventManager::pollEvent() {
    return mainWindow->pollEvent(*event);
}

EventManager::EventManager(sf::RenderWindow *theMainWindow, sf::Event *the_event, int playerId, gameState_t *the_state)
        :
playerId(playerId)
{
    mainWindow = theMainWindow;
    event = the_event;
    state = the_state;
}

std::string EventManager::getMessageFromGameObjects() {
    ///@todo реализовать согласно ТЗ
    if (pollEvent())
    {
        switch (*state) {
            case GAME_STATE_MATCH: {
                return returnMessageFromMatchActions();
                break;
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
    switch (event->type) {
        case sf::Event::Closed: {
            mainWindow->close();
            ///@todo return json message about closing
            break;
        }
        case sf::Event::KeyPressed:
        {
            switch (event->key.code) {
                case sf::Keyboard::Left:
                case sf::Keyboard::A: {
                    json json_message;
                    json_message["status"] = "OK";
                    json_message["from"] = playerId;
                    json_message["method"] = "moveLeft";
                    json_message["params"] = json::array();
//                    std::cout << json_message.dump();
                    return json_message.dump();
                }
                case sf::Keyboard::Right:
                case sf::Keyboard::D: {
                    json json_message;
                    json_message["status"] = "OK";
                    json_message["from"] = playerId;
                    json_message["method"] = "moveRight";
                    json_message["params"] = json::array();
//                    std::cout << json_message.dump();
                    return json_message.dump();
                }
                case sf::Keyboard::Up:
                case sf::Keyboard::W: {
                    json json_message;
                    json_message["status"] = "OK";
                    json_message["from"] = playerId;
                    json_message["method"] = "moveUp";
                    json_message["params"] = json::array();
//                    std::cout << json_message.dump();
                    return json_message.dump();
                }
                case sf::Keyboard::Down:
                case sf::Keyboard::S: {
                    json json_message;
                    json_message["status"] = "OK";
                    json_message["from"] = playerId;
                    json_message["method"] = "moveDown";
                    json_message["params"] = json::array();
//                    std::cout << json_message.dump();
                    return json_message.dump();
                }
                case sf::Keyboard::Escape: {
                    *state = GAME_STATE_MATCH_PAUSE;
//                    std::cout << "Game state is MATCH_PAUSE\n";
                    ///@todo return json message with paused state
                    break;
                }
                case sf::Keyboard::Space: {
                    json json_message;
                    json_message["status"] = "OK";
                    json_message["from"] = playerId;
                    json_message["method"] = "shoot";
                    json_message["params"] = json::array({});
//                    std::cout << json_message.dump() << std::endl;
                    return json_message.dump();
                }
                default: {
//                    std::cout << "You pressed " << event->key.code << std::endl;
                    break;
                }
            }
            break;
        }
        case sf::Event::KeyReleased: {
            switch (event->key.code) {
                case sf::Keyboard::Left:
                case sf::Keyboard::Right:
                case sf::Keyboard::Up:
                case sf::Keyboard::Down:
                case sf::Keyboard::A:
                case sf::Keyboard::S:
                case sf::Keyboard::W:
                case sf::Keyboard::D:
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
        default:
            break;
    }
    return std::string();
}

void EventManager::handleMatchPauseActions() {
    switch (event->type)
    {
        case sf::Event::Closed: {
            mainWindow->close();
            ///@todo return json message about closing
            break;
        }
        case sf::Event::KeyPressed: {
            switch (event->key.code) {
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

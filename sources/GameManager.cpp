#include "GameManager.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Tank.hpp"
#include <cmath>

GameManager::GameManager(sf::RenderWindow &the_mainWindow, tgui::Gui &the_gui, sf::Event &the_event) :
mainWindow(the_mainWindow),
gui(the_gui),
event(the_event)
{
    ///@todo проверить наличие файла player_info.json
    state = GAME_STATE_MAIN_MENU;
    interfaceManager = new InterfaceManager(mainWindow, nullptr, &state, the_gui);
    eventManager = new EventManager(mainWindow, event, -1, &state, gui);
}

void GameManager::runGame() {
    mainWindow.setKeyRepeatEnabled(false);
    float frequency(0);

    while (mainWindow.isOpen()) {

        interfaceManager->makeInterface();
        if (state != GAME_STATE_MATCH && state != GAME_STATE_MATCH_PAUSE) handleEvent();

        mainWindow.display();

        switch (state) {
            case GAME_STATE_CREATE_MATCH: {
                mainWindow.clear();
                std::string players_info_json, map_json;
                ///@todo прочитать players_info_json, map_json;
                match = new Match(mainWindow, players_info_json, map_json);
                interfaceManager->setMapName(match->getMapName());
                interfaceManager->setObjectManager(match->getObjectManager());
                state = GAME_STATE_MATCH;
                break;
            }
            case GAME_STATE_MATCH_PAUSE:
            case GAME_STATE_MATCH: {
//                sf::Clock clock;
//                float time = clock.getElapsedTime().asMicroseconds();
//                clock.restart();
//                frequency += time;
//                if(frequency < KTIME) continue;
//                else frequency = 0;
                mainWindow.clear();

                std::string message = eventManager->getMessageFromGameObjects();
                if (!message.empty()) match->processMessage(message);
                Tank* tmp = (Tank* )match->getObjectManager()->getGameObjectById(0);
                auto tmp1 = sf::Mouse::getPosition(mainWindow);
                int sinus = tmp->checkOrient(tmp1.x, tmp1.y);
                if(sinus>0)
                        tmp->setSpeedTower(TANK_TOWER_SPEED);
                else
                        tmp->setSpeedTower(-TANK_TOWER_SPEED);
                if(sinus == 0)
                    tmp->setSpeedTower(0);
                match->updateMatch();
                match->drawMatch();
                break;
            }
            default: {
                mainWindow.clear();
                break;
            }
        }

    }
}

void GameManager::handleEvent() {
    if (eventManager->pollEvent()) {
        gui.handleEvent(event);
        switch (event.type) {
            case sf::Event::Resized: {
                mainWindow.setView(sf::View(sf::FloatRect(0.f, 0.f, static_cast<float>(event.size.width), static_cast<float>(event.size.height))));
                gui.setView(mainWindow.getView());
                break;
            }
            case sf::Event::Closed: {
                mainWindow.close();
                break;
            }
            case sf::Event::KeyPressed: {
                switch (event.key.code) {
                    case sf::Keyboard::Enter: {
                        if (state == GAME_STATE_ENTER_LOGIN_PASSWORD)
                            if (interfaceManager->login())
                                state = GAME_STATE_MAIN_MENU;
                        break;
                    }
                    case sf::Keyboard::Escape: {
                        mainWindow.close();
                        std::cout << "Window closed by Escape\n";
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }
            }
            default: {
                break;
            }
        }
    }


}

GameManager::~GameManager() {
    delete(interfaceManager);
    delete(eventManager);
    delete(match);
}

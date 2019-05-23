#include "GameManager.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Tank.hpp"
#include <cmath>
#include <fstream>
#include <unistd.h>

GameManager::GameManager(sf::RenderWindow &the_mainWindow, tgui::Gui &the_gui, sf::Event &the_event,
                         NetworkManager &the_networkmanager, sf::View &view, std::string &iMyName) :
mainWindow(the_mainWindow),
gui(the_gui),
event(the_event),
networkManager(the_networkmanager),
view(view)
{
    ///@todo проверить наличие файла player_info.json
    state = GAME_STATE_MAIN_MENU;
    interfaceManager = new InterfaceManager(mainWindow, nullptr, &state, the_gui, networkManager, match, matches,
                                            current_match);
    eventManager = new EventManager(mainWindow, event, 0, &state, gui, *interfaceManager, iMyName);
}

void GameManager::runGame() {
    mainWindow.setKeyRepeatEnabled(false);
    while (mainWindow.isOpen()) {
        interfaceManager->makeInterface();
        if (state != GAME_STATE_MATCH && state != GAME_STATE_MATCH_PAUSE) handleEvent();
        mainWindow.display();

        switch (state) {
            case GAME_STATE_MULTIPLAYER_MATCH: {
//                std::cout << 'state - multiplyear match' << std::endl;
                mainWindow.clear();
                networkManager.processPakcetsFromServer();

                auto action = eventManager->getMessageFromGameObjects();

                if (!action.empty())
                    match->processMessage(action, -1);
                networkManager.sendMessageToServer(action);

//                auto mouseMessage = eventManager->getMouseMessage();
//                if (!mouseMessage.empty()) match->processMessage(mouseMessage);
                networkManager.sendMessageToServer(eventManager->getMouseMessage());

                Tank* tmp = match->getObjectManager()->getTankById(match->getMyPlayerId());
                auto tmp1 = sf::Mouse::getPosition(mainWindow);
                float sinus = tmp->checkOrient(tmp1.x, tmp1.y, &mainWindow);
                if(sinus>0)
                    tmp->setSpeedTower(TANK_TOWER_SPEED);
                else
                    tmp->setSpeedTower(-TANK_TOWER_SPEED);
                if(sinus < 0.03 && sinus > -0.03)
                    tmp->setSpeedTower(0);

                float time = clock.getElapsedTime().asMilliseconds();
                clock.restart();
                match->updateMatch(time);
                match->setPlayerCoordVorView();
                mainWindow.setView(view);
                match->drawMatch();
                networkManager.sendMessageToServer(eventManager->getSyncMessage());
                break;
            }
            case GAME_STATE_CREATE_MULTIPLAYER_MATCH: {
                if (isGameReady) {
                    state = GAME_STATE_MULTIPLAYER_MATCH;
                    break;
                }
//                std::cout << "create multi matchs" << std::endl;
                ///@todo прочитать players_info_json, map_json;
                std::string line, players_info_json, map_json;
                std::ifstream mapfile (MAP_FILE);
                std::ifstream playerInfofile ("./sources/json/players_info.txt");
                if (mapfile.is_open()) {
                    while (getline(mapfile,line))  {
                        map_json += line + '\n';
                    }
                    mapfile.close();
                }
                if (playerInfofile.is_open()) {
                    while (getline(playerInfofile, line)) {
                        players_info_json += line + '\n';
                    }
                    playerInfofile.close();
                }

                clock.restart();
                match = new Match(mainWindow, players_info_json, map_json, view, 0, &state);
                std::cout << "Match created" << std::endl;
                match->setDeathLine(0);
                interfaceManager->setMapName(match->getMapName());
                interfaceManager->setObjectManager(match->getObjectManager());
                interfaceManager->setMatch(match);
                for (const auto &widget : gui.getWidgets()) {
                    widget->disconnectAll();
                }
                gui.removeAllWidgets();
                networkManager.setMatch(match);
                char id = networkManager.establishConnection(current_match["game_id"].get <int> ());
                match->getObjectManager()->getTanks()[id]->setPlayerName(networkManager.getMyName());
                eventManager->setPlayerId(match->getMyPlayerId());
                eventManager->setObjectManager(match->getObjectManager());
                eventManager->setMatch(match);
                networkManager.setMyPlayerId(match->getMyPlayerId());
                isGameReady = true;
                break;
            }
            case GAME_STATE_MATCH_CHOOSE: {
//                std::cout << "state = match choose" << std::endl;
                mainWindow.clear();
                if (trottlingClock.getElapsedTime().asSeconds() > 1) {
                    if (!current_match.is_null())
                        if (networkManager.areAllReady(current_match["game_id"]))
                            state = GAME_STATE_CREATE_MULTIPLAYER_MATCH;
                        else {

                        }
                    trottlingClock.restart();
                }

//                networkManager.areAllReady();
                break;
            }
            case GAME_STATE_CREATE_MATCH: {
//                std::cout << "state - create match" << std::endl;
                if (isGameReady) {
                    state = GAME_STATE_MATCH;
                    break;
                }
                mainWindow.clear();
                ///@todo прочитать players_info_json, map_json;
                std::string line, players_info_json, map_json;
                std::ifstream mapfile (MAP_FILE);
                std::ifstream playerInfofile ("./sources/json/players_info.txt");
                if (mapfile.is_open())  {
                    while (getline(mapfile,line))  {
                        map_json += line + '\n';
                    }
                    mapfile.close();
                }
                if (playerInfofile.is_open())  {
                    while (getline(playerInfofile,line))  {
                        players_info_json += line + '\n';
                    }
                    playerInfofile.close();
                }

                clock.restart();
                match = new Match(mainWindow, players_info_json, map_json, view, 0, &state);
                interfaceManager->setMapName(match->getMapName());
                interfaceManager->setObjectManager(match->getObjectManager());
                interfaceManager->setMatch(match);
                eventManager->setObjectManager(match->getObjectManager());
                eventManager->setPlayerId(match->getMyPlayerId());
                eventManager->setMatch(match);
                isGameReady = true;
                break;
            }
            case GAME_STATE_MATCH_PAUSE:
            case GAME_STATE_MATCH: {
//                std::cout << "state - match" << std::endl;
                mainWindow.clear();
                std::string message = eventManager->getMessageFromGameObjects();

                if (!message.empty()) match->processMessage(message, -1);

                Tank* tmp = match->getObjectManager()->getTankById(match->getMyPlayerId());
                auto tmp1 = sf::Mouse::getPosition(mainWindow);
                float sinus = tmp->checkOrient(tmp1.x, tmp1.y, &mainWindow);
                if(sinus>0)
                    tmp->setSpeedTower(TANK_TOWER_SPEED);
                else
                    tmp->setSpeedTower(-TANK_TOWER_SPEED);
                if(sinus < 0.03 && sinus > -0.03)
                    tmp->setSpeedTower(0);

                float time = clock.getElapsedTime().asMilliseconds();
                clock.restart();
                match->updateMatch(time);
                match->setPlayerCoordVorView();
                mainWindow.setView(view);
                match->drawMatch();
//                gui.handleEvent();
                break;
            }
            case GAME_STATE_MAIN_MENU: {
//                std::cout << "state - main menu" << std::endl;
                if (isGameReady) {
                    isGameReady = false;
                    delete match;
                    match = nullptr;
                    current_match = json();
                }
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
                        if (state == GAME_STATE_ENTER_LOGIN_PASSWORD) {
                            std::pair<std::string, std::string> loginPass = InterfaceManager::login();
                            if (!loginPass.first.empty()) {
                                state = GAME_STATE_MAIN_MENU;
                                if (networkManager.authorize(loginPass))
                                    state = GAME_STATE_MATCH_CHOOSE;
                            }
                        }
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

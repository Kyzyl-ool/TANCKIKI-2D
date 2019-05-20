#include "GameManager.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Tank.hpp"
#include <cmath>
#include <fstream>
#include <unistd.h>

GameManager::GameManager(sf::RenderWindow &the_mainWindow, tgui::Gui &the_gui, sf::Event &the_event,
                         NetworkManager &the_networkmanager, sf::View &the_view) :
mainWindow(the_mainWindow),
gui(the_gui),
event(the_event),
networkManager(the_networkmanager),
view(the_view)
{
    ///@todo проверить наличие файла player_info.json
    state = GAME_STATE_MAIN_MENU;
    interfaceManager = new InterfaceManager(mainWindow, nullptr, &state, the_gui, networkManager, match, matches);
    eventManager = new EventManager(mainWindow, event, 0, &state, gui, *interfaceManager);
}

void GameManager::runGame() {
    mainWindow.setKeyRepeatEnabled(false);
    while (mainWindow.isOpen()) {
        handleEvent();
        doAction();
        interfaceManager->makeInterface();
//        mainWindow.clear();
        mainWindow.display();
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

void GameManager::doAction() {
    switch (state) {
        case GAME_STATE_MULTIPLAYER_MATCH: {
            mainWindow.clear();
            networkManager.processPakcetsFromServer();
            auto action = eventManager->getMessageFromGameObjects();
            if (!action.empty())
                match->processMessage(action, -1);
            networkManager.sendMessageToServer(action);
            networkManager.sendMessageToServer(action);

//                auto mouseMessage = eventManager->getMouseMessage();
//                if (!mouseMessage.empty()) match->processMessage(mouseMessage);
            networkManager.sendMessageToServer(eventManager->getMouseMessage());
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
            match = new Match(mainWindow, players_info_json, map_json, view, 0);
            std::cout << "Match created" << std::endl;
            match->setDeathLine(0);
            interfaceManager->setMapName(match->getMapName());
            interfaceManager->setObjectManager(match->getObjectManager());
            interfaceManager->setMatch(match);
            gui.removeAllWidgets();
            networkManager.setMatch(match);
            networkManager.establishConnection();
            eventManager->setPlayerId(match->getMyPlayerId());
            eventManager->setObjectManager(match->getObjectManager());
            eventManager->setMatch(match);
            networkManager.setMyPlayerId(match->getMyPlayerId());
            state = GAME_STATE_MULTIPLAYER_MATCH;
            break;
        }
        case GAME_STATE_WAIT_FOR_OTHER_PLAYERS: {
            json j = networkManager.getPlayersInGame(gameId)["result"];
            std::cout << j << std::endl;
            int k = 0;
            json playersList = json(j[std::to_string(k)]);
            std::cout << "Players in this game:" << std::endl;
            std::cout << "-------------------------------" << std::endl;
            do {
                std::cout << "nick: " << playersList["nickname"] << ", ready: " << playersList["ready"] << std::endl;
                k++;
                playersList = json(j[std::to_string(k)]);
            }
            while (!playersList.is_null());
            std::cout << "-------------------------------" << std::endl;
            sleep(1);
            std::cout << "Are you ready? [y/n]: ";
            char c;
            std::cin >> c;
            if (c == 'y') {
                networkManager.setReady(true);
            }
            else if (c == 'n') {
                networkManager.setReady(false);
            }

            if (networkManager.areAllReady(gameId))
                state = GAME_STATE_CREATE_MULTIPLAYER_MATCH;
//                    state = GAME_STATE_CREATE_MATCH;

            break;
        }
        case GAME_STATE_MATCH_CHOOSE: {
            mainWindow.clear();
            json j = networkManager.getGamesList();
            if (j.empty()) {
                std::cout << "There are no games in server. Do you want to create your own game? [y/n]: ";
                char c;
                std::cin >> c;
                if (c == 'y') {

                } else {
                    state = GAME_STATE_MAIN_MENU;
                }
            } else {
                int k = 0;
                json game = json(j[std::to_string(k)]);
                do {
                    std::cout << "-------------------------------" << std::endl;
                    std::cout << "Game creator: " << game["creator"] << std::endl;
                    std::cout << "Id: " << game["game_id"] << std::endl;
                    std::cout << "Name: " << game["name"] << std::endl;
                    std::cout << "-------------------------------" << std::endl;
                    k++;
                    game = json(j[std::to_string(k)]);
                }
                while (!game.is_null());

//                    std::cout << j << std::endl;
                std::cout << "Enter game id: ";
                std::cin >> gameId;
                networkManager.connectToGame(gameId);
                state = GAME_STATE_WAIT_FOR_OTHER_PLAYERS;
            }
            break;
        }
        case GAME_STATE_CREATE_MATCH: {
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
            match = new Match(mainWindow, players_info_json, map_json, view, 0);
            interfaceManager->setMapName(match->getMapName());
            interfaceManager->setObjectManager(match->getObjectManager());
            interfaceManager->setMatch(match);
            eventManager->setObjectManager(match->getObjectManager());
            eventManager->setPlayerId(match->getMyPlayerId());
            eventManager->setMatch(match);
            state = GAME_STATE_MATCH;
            break;
        }
        case GAME_STATE_MATCH_PAUSE:
        case GAME_STATE_MATCH: {
            mainWindow.clear();


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

            std::string message = eventManager->getMessageFromGameObjects();
            if (!message.empty()) match->processMessage(message, -1);

//                gui.handleEvent();
            break;
        }
        default: {
            mainWindow.clear();
            break;
        }
    }
}

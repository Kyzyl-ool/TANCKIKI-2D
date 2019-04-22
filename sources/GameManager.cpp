#include "GameManager.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Tank.hpp"
#include <cmath>

GameManager::GameManager(sf::RenderWindow &the_mainWindow, tgui::Gui &the_gui, sf::Event &the_event,
                         NetworkManager &the_networkmanager) :
mainWindow(the_mainWindow),
gui(the_gui),
event(the_event),
networkManager(the_networkmanager)
{
    ///@todo проверить наличие файла player_info.json
    state = GAME_STATE_MAIN_MENU;
    interfaceManager = new InterfaceManager(mainWindow, nullptr, &state, the_gui, networkManager);
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
                mainWindow.clear();
                std::string message = eventManager->getMessageFromGameObjects();
                networkManager.sendMessageToServer(message);
                if (!message.empty()) match->processMessage(message);
                networkManager.processPakcetsFromServer();
                float time = clock.getElapsedTime().asMilliseconds();
                clock.restart();
                match->updateMatch(time);
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
                        if (state == GAME_STATE_ENTER_LOGIN_PASSWORD) {
                            std::pair<std::string, std::string> loginPass = InterfaceManager::login();
                            if (!loginPass.first.empty()) {
                                state = GAME_STATE_MAIN_MENU;
                                networkManager.authorize(loginPass);
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

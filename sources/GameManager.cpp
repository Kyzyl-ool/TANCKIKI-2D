#include "GameManager.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

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
    while (mainWindow.isOpen()) {

        interfaceManager->makeInterface();
        if (state != GAME_STATE_MATCH && state != GAME_STATE_MATCH_PAUSE) {
            handleEvent();
            gui.draw();
        }

        mainWindow.display();
        mainWindow.clear();

        switch (state) {
            case GAME_STATE_CREATE_MATCH: {
                std::string players_info_json, map_json;
                ///@todo прочитать players_info_json, map_json;
                match = new Match(mainWindow, players_info_json, map_json);
                interfaceManager->setMapName(match->getMapName());
                state = GAME_STATE_MATCH;
                break;
            }
            case GAME_STATE_MATCH_PAUSE:
            case GAME_STATE_MATCH: {
                std::string message = eventManager->getMessageFromGameObjects();
                if (!message.empty()) match->processMessage(message);
                match->updateMatch();
                match->drawMatch();
                break;
            }
            default: {
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

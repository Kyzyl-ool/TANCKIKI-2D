//
// Created by Кежик Кызыл-оол on 2019-02-26.
//

#include <iostream>
#include "InterfaceManager.hpp"


InterfaceManager::InterfaceManager(sf::RenderWindow *the_mainWindow, ObjectManager *objectManager, gameState_t *state) :
objectManager(objectManager),
state(state)
{
    mainWindow = the_mainWindow;
}

void InterfaceManager::makeInterface() {
    switch (*state) {
        case GAME_STATE_MATCH:
        {
            drawMatchInterface();
            break;
        }
        case GAME_STATE_MAIN_MENU:
        {
            drawMainMenu();
            break;
        };
        case GAME_STATE_ENTER_NAME:
        {
            drawEnterNameScreen();
            break;
        }
        case GAME_STATE_CHOOSE_MAP:
        {
            drawChooseMapScreen();
            break;
        }
        case GAME_STATE_ERROR:
        {
            drawErrorScreen();
            std::cout << errString;
            break;
        }
        case GAME_STATE_MATCH_PAUSE:
        {
            drawMatchPauseWindow();
            break;
        }
        case GAME_STATE_CREATE_MATCH:
        {
            break;
        }
        default:
        {
            std::cout << "Interface manager unknown error at interface switch-case: " << *state << "\n";
            break;
        }
    }
}

void InterfaceManager::drawChooseMapScreen() {
    ///@todo ...
}

void InterfaceManager::drawMainMenu() {
    ///@todo ...
}


void InterfaceManager::drawEnterNameScreen() {
    ///@todo ... dodo
}



void InterfaceManager::drawErrorScreen() {
    ///@todo ...
}

void InterfaceManager::drawMatchInterface() {
    ///@todo ...
}


void InterfaceManager::setMapName(const std::string &mapName) {
    InterfaceManager::mapName = mapName;
}

void InterfaceManager::drawMatchPauseWindow() {
    ///@todo ...
}
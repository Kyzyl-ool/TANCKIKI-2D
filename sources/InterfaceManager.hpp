//
// Created by Кежик Кызыл-оол on 2019-02-26.
//

#ifndef TANCHIKI_INTERFACEMANAGER_HPP
#define TANCHIKI_INTERFACEMANAGER_HPP


#include <SFML/Graphics.hpp>
#include "ObjectManager.hpp"
#include "gameStates.hpp"

/*!
 * Этот класс отвечает за весь игровой интерфейс.
 */

class InterfaceManager
{
private:
    sf::RenderWindow* mainWindow;
    gameState_t* state;
    std::string errString;
    ObjectManager* objectManager;
    std::string mapName;
    sf::Event event;

public:
    void setMapName(const std::string &mapName);

    InterfaceManager(sf::RenderWindow *the_mainWindow, ObjectManager *the_objectManager, gameState_t *the_state);

    void makeInterface();

    void drawMainMenu();

    void drawEnterNameScreen();

    void drawChooseMapScreen();

    void drawMatchInterface();

    void drawMatchPauseWindow();

    void drawErrorScreen();
};

#endif //TANCHIKI_INTERFACEMANAGER_HPP

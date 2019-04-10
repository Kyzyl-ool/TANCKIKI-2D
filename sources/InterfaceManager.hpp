//
// Created by Кежик Кызыл-оол on 2019-02-26.
//

#ifndef TANCHIKI_INTERFACEMANAGER_HPP
#define TANCHIKI_INTERFACEMANAGER_HPP


#include <SFML/Graphics.hpp>
#include "ObjectManager.hpp"
#include "constants/gameStates.hpp"
#include <TGUI/TGUI.hpp>

/*!
 * Этот класс отвечает за весь игровой интерфейс.
 */

class InterfaceManager
{
private:
    sf::RenderWindow& mainWindow;
    tgui::Gui& gui;
    gameState_t* state;
public:
    void setState(gameState_t gameState);

private:
    std::string errString;
    ObjectManager* objectManager;
    std::string mapName;
    sf::Event event{};
    bool heathbarloaded = false;

public:
    void setMapName(const std::string &the_mapName);

    InterfaceManager(sf::RenderWindow &the_mainWindow, ObjectManager *the_objectManager, gameState_t *the_state,
                     tgui::Gui &the_gui);

    void makeInterface();

    static void signalHandler1(InterfaceManager *manager);

    static void signalHandler2(InterfaceManager *manager);

    static void signalHandler3(InterfaceManager *manager);

    static void login(const tgui::EditBox::Ptr& username, const tgui::EditBox::Ptr& password);

};

#endif //TANCHIKI_INTERFACEMANAGER_HPP

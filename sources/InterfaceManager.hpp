//
// Created by Кежик Кызыл-оол on 2019-02-26.
//

#ifndef TANCHIKI_INTERFACEMANAGER_HPP
#define TANCHIKI_INTERFACEMANAGER_HPP


#include <SFML/Graphics.hpp>
#include "ObjectManager.hpp"
#include "constants/gameStates.hpp"
#include "NetworkManager.hpp"
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
    NetworkManager& networkManager;

    std::string errString;
    ObjectManager* objectManager;
    std::string mapName;

    bool heathbarloaded = false;

    std::vector <tgui::ProgressBar::Ptr> healthTanks;

public:
    void setState(gameState_t gameState);
    void setObjectManager(ObjectManager *objectManager);

    void setMapName(const std::string &the_mapName);

    InterfaceManager(sf::RenderWindow &the_mainWindow, ObjectManager *the_objectManager, gameState_t *the_state,
                     tgui::Gui &the_gui, NetworkManager &the_networkmanager);

    void makeInterface();

    static void signalHandler1(InterfaceManager *manager);

    static void signalHandler2(InterfaceManager *manager);

    static void signalHandler3(InterfaceManager *manager);

    static void signalHandler4(InterfaceManager *manager);

    static std::pair<std::string, std::string> login();
};

#endif //TANCHIKI_INTERFACEMANAGER_HPP

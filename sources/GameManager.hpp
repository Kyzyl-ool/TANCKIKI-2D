//
// Created by Кежик Кызыл-оол on 2019-02-26.
//

#ifndef TANCHIKI_GAMEMANAGER_HPP
#define TANCHIKI_GAMEMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include "ObjectManager.hpp"
#include "PhysicsManager.hpp"
#include "GraphicsManager.hpp"
#include "InterfaceManager.hpp"
#include "Match.hpp"
#include "constants/gameStates.hpp"
#include "EventManager.hpp"


/*!
 * \brief Главный класс в программе, который агрегирует в себе всё, что работает в игре.
 */
class GameManager
{
private:
    sf::RenderWindow& mainWindow;
    tgui::Gui& gui;
    Match* match;
    InterfaceManager* interfaceManager;
    EventManager* eventManager;

    gameState_t state;
    sf::Event& event;
    std::string playerName;

public:
    GameManager(sf::RenderWindow &the_mainWindow, tgui::Gui &the_gui, sf::Event &the_event);
    ~GameManager();

    /*!
     * \brief запуск игры
     *
     * \details После вызова этого метода игра должна открыться
     * в окне и отобразить главное меню, где можно начать игру,
     * либо выйти из неё.
     */
    void runGame();
    void handleEvent();
    
};

#endif //TANCHIKI_GAMEMANAGER_HPP

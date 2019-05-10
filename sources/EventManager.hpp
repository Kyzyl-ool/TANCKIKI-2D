//
// Created by Кежик Кызыл-оол on 2019-03-19.
//

#ifndef TANCHIKI_EVENTMANAGER_HPP
#define TANCHIKI_EVENTMANAGER_HPP


#include <SFML/Graphics.hpp>
#include <TGUI/Gui.hpp>
#include "constants/gameStates.hpp"
#include "InterfaceManager.hpp"

class EventManager {
private:
    sf::RenderWindow& mainWindow;
    tgui::Gui& gui;
    gameState_t* state;
    sf::Event& event;
    int playerId;
    InterfaceManager& interfaceManager;

public:
    EventManager(sf::RenderWindow &theMainWindow, sf::Event &the_event, int playerId, gameState_t *the_state,
                 tgui::Gui &the_gui, InterfaceManager &interfaceManager);
    bool pollEvent();
    std::string getMessageFromGameObjects();

    std::string returnMessageFromMatchActions();
    void handleMatchPauseActions();
    char getPressedArrows(sf::Keyboard::Key left, sf::Keyboard::Key down, sf::Keyboard::Key up,
                              sf::Keyboard::Key right);
    std::string goMessage(char direction);
};


#endif //TANCHIKI_EVENTMANAGER_HPP

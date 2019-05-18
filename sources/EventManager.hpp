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
    int playerId = -1;
    sf::Clock syncClock;
    ObjectManager* objectManager;
    Match* match;
    int playerViewId = 0;
public:
    void setMatch(Match *match);

public:
    ObjectManager *getObjectManager() const;

    void setObjectManager(ObjectManager *iobjectManager);

public:
    void setPlayerId(int playerId);

private:
    InterfaceManager& interfaceManager;

public:
    EventManager(sf::RenderWindow &theMainWindow, sf::Event &the_event, int playerId, gameState_t *the_state,
                 tgui::Gui &the_gui, InterfaceManager &interfaceManager);
    bool pollEvent();
    std::string getMessageFromGameObjects();

    std::string returnMessageFromMatchActions();
    void handleMatchPauseActions();
    char getPressedArrows();
    std::string goMessage(char direction);
    std::string getSyncMessage();
    std::string getMouseMessage();
};


#endif //TANCHIKI_EVENTMANAGER_HPP

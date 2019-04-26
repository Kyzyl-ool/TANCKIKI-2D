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
#include "json/json.hpp"

using json = nlohmann::json;

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
public:
    void setState(gameState_t gameState);

private:
    std::string errString;
    ObjectManager* objectManager;
    std::string mapName;
public:
    void setObjectManager(ObjectManager *objectManager);

private:
    sf::Event event{};
    bool heathbarloaded = false;
    bool tanksnameloaded = false;

    std::vector <tgui::ProgressBar::Ptr> healthTanks;
    std::vector <tgui::Label::Ptr> nameTanks;

public:
    void setMapName(const std::string &the_mapName);

    InterfaceManager(sf::RenderWindow &the_mainWindow, ObjectManager *the_objectManager, gameState_t *the_state,
                     tgui::Gui &the_gui, NetworkManager &the_networkmanager);

    void makeInterface();

    static void signalHandler1(InterfaceManager *manager);

    static void signalHandler2(InterfaceManager *manager);

    static void signalHandler3(InterfaceManager *manager);

    static void signalHandler4(InterfaceManager *manager);

    void showHealth();

    void cancelShow();

    static std::pair<std::string, std::string> login();

    ///@todo показать окно с доступными матчами
    void ShowMatchesDialog(json j);
    ///@todo закрыть окно с матчами
    void closeMatchesDialog();

    ///@todo срабатывает при старте матча
    void onMatchClick(int match_id);

    ///@todo срабатывает, если нажать на создание матча
    void onCreateMatchClick();
};

#endif //TANCHIKI_INTERFACEMANAGER_HPP

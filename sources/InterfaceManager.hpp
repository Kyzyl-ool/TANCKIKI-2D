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
    Match* match;
public:
    void setMatch(Match *match);

private:

    std::string errString;
    ObjectManager* objectManager;
    std::string mapName;

    bool heathbarloaded = false;
    bool tanksnameloaded = false;
    bool matchesLoaded = false;
    bool ammuncount = false;

    std::vector <tgui::ProgressBar::Ptr> healthTanks;
    std::vector <tgui::Label::Ptr> nameTanks;
    tgui::Label::Ptr ammun_count;

    std::vector <json>& matches;
public:
    void setMatches(const std::vector<json> &matches);

public:
    void setState(gameState_t gameState);
    void setObjectManager(ObjectManager *objectManager);

    void setMapName(const std::string &the_mapName);

    InterfaceManager(sf::RenderWindow &the_mainWindow, ObjectManager *the_objectManager,
                     gameState_t *the_state, tgui::Gui &the_gui, NetworkManager &the_networkmanager,
                     Match *iMatch, std::vector<json> &iMatches);

    void makeInterface();

    static void signalHandler1(InterfaceManager *manager);

    static void signalHandler2(InterfaceManager *manager);

    static void signalHandler3(InterfaceManager *manager);

    static void signalHandler4(InterfaceManager *manager);

    void showHealth();

    void cancelShow();

    static std::pair<std::string, std::string> login();

    void renderMatches();

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

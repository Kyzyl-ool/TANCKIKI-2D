//
// Created by Кежик Кызыл-оол on 2019-02-26.
//

#include <iostream>
#include "InterfaceManager.hpp"
#include "WidgetsMenu.hpp"
#include "Tank.hpp"
#include "Match.hpp"


InterfaceManager::InterfaceManager(sf::RenderWindow &the_mainWindow, ObjectManager *the_objectManager,
                                   gameState_t *the_state, tgui::Gui &the_gui, NetworkManager &the_networkmanager,
                                   Match *iMatch) :

        mainWindow(the_mainWindow),
        objectManager(the_objectManager),
        state(the_state),
        gui(the_gui),
        networkManager(the_networkmanager),
        match(iMatch)
{
    try {
        static auto picture = tgui::Picture::create({"images/forest.svg", {0, 0, 1000, 700}}); //Failed to create texture, invalid size (0x0)
        picture->setSize({"100%", "100%"});
        gui.add(picture);

        static auto singleButton = tgui::Button::create("Singleplayer"); //кнопка Singleplayer
        singleButton->setSize({"50%", "16.67%"});
        singleButton->setPosition({"25%", "10%"});
        singleButton->setTextSize(0);
        gui.add(singleButton);
        WidgetsMenu::add_widget(singleButton);

        static auto multiButton = tgui::Button::create("Multiplayer"); //кнопка Multiplayer
        multiButton->setSize({"50%", "16.67%"});
        multiButton->setPosition({"25%", "30%"});
        multiButton->setTextSize(0);
        gui.add(multiButton);
        WidgetsMenu::add_widget(multiButton);

        static auto settingsButton = tgui::Button::create("Settings"); //кнопка Settings
        settingsButton->setSize({"50%", "16.67%"});
        settingsButton->setPosition({"25%", "50%"});
        settingsButton->setTextSize(0);
        gui.add(settingsButton);
        WidgetsMenu::add_widget(settingsButton);

        static auto quitButton = tgui::Button::create("Exit"); //кнопка Exit
        quitButton->setSize({"50%", "16.67%"});
        quitButton->setPosition({"25%", "70%"});
        quitButton->setTextSize(0);
        gui.add(quitButton);
        WidgetsMenu::add_widget(quitButton);

        static auto loginWindow = tgui::MessageBox::create();
        loginWindow->setSize({"40%", "30%"});
        loginWindow->setPosition({"30%", "31%"});
        loginWindow->setTitle("Please Login");
        loginWindow->setVisible(false);
        loginWindow->setPositionLocked(true);
        gui.add(loginWindow);
        WidgetsMenu::add_widget(loginWindow);

        static auto editBoxUsername = tgui::EditBox::create();
        editBoxUsername->setSize({"66.67%", "12.5%"});
        editBoxUsername->setPosition({"16.67%", "16.67%"});
        editBoxUsername->setDefaultText("Username");
        editBoxUsername->setTextSize(0);
        loginWindow->add(editBoxUsername);
        WidgetsMenu::add_box(editBoxUsername);

        static auto editBoxPassword = tgui::EditBox::copy(editBoxUsername);
        editBoxPassword->setPosition({"16.67%", "41.6%"});
        editBoxPassword->setPasswordCharacter('*');
        editBoxPassword->setDefaultText("Password");
        editBoxPassword->setTextSize(0);
        loginWindow->add(editBoxPassword);
        WidgetsMenu::add_box(editBoxPassword);

        static auto buttonLogin = tgui::Button::create("Login");
        buttonLogin->setSize({"20%", "16.67%"});
        buttonLogin->setPosition({"60 %", "70%"});
        buttonLogin->setTextSize(0);
        loginWindow->add(buttonLogin);

        static auto buttonCancel = tgui::Button::create("Cancel");
        buttonCancel->setSize({"20%", "16.67%"});
        buttonCancel->setPosition({"20%", "70%"});
        buttonCancel->setTextSize(0);
        loginWindow->add(buttonCancel);

        singleButton->connect("pressed", &InterfaceManager::signalHandler1, this);
        singleButton->connect("pressed", [&](){
            gui.remove(picture);
            gui.remove(singleButton);
            gui.remove(multiButton);
            gui.remove(quitButton);
            gui.remove(settingsButton);
            WidgetsMenu::widget_remove();
        });

        multiButton->connect("pressed", &InterfaceManager::signalHandler2, this);
        multiButton->connect("pressed", [&](){
            WidgetsMenu::change_ava(1);
            editBoxUsername->setText("kyzyloolk");
            editBoxPassword->setText("akTPLWGd");
        });

        quitButton->connect("pressed", &InterfaceManager::signalHandler3, this);
        quitButton->connect("pressed", [&](){ mainWindow.close(); });

        settingsButton->connect("pressed", &InterfaceManager::signalHandler4, this);

        buttonLogin->connect("pressed", [&](){
            std::pair <std::string, std::string> tmp = WidgetsMenu::login();
            if (!tmp.first.empty()) {
                networkManager.authorize(tmp);
            }
        });

        buttonCancel->connect("pressed", [&](){
            WidgetsMenu::change_ava(0);
        });
    }
    catch (const tgui::Exception& e) {
        std::cerr << "Failed to load TGUI widgets: " << e.what() << std::endl;
        assert(0);
    }
}

void InterfaceManager::makeInterface() {
    switch (*state) {
        case GAME_STATE_MULTIPLAYER_MATCH:
        case GAME_STATE_MATCH: {
            auto tanks = objectManager->getTanks(); //вектор танков

            int id = match->getMyPlayerId();

            if (ammuncount) {
                auto s = std::to_string(tanks[id]->getAmmun());
                try {
                    ammun_count->setText("Bullets: " + s);
                    if(!tanks[id]->isAlive()) {
                        ammun_count->setVisible(false);
                    }
                }
                catch (const tgui::Exception& e) {
                    std::cerr << "Failed to load TGUI widgets: " << e.what() << std::endl;
                    assert(0);
                }
            }

            else {
                auto s = std::to_string(tanks[id]->getAmmun());
                try {
                    ammun_count = tgui::Label::create("Bullets: " + s);
                    ammun_count->getRenderer()->setTextColor(sf::Color::White);
                    ammun_count->getRenderer()->setTextStyle(sf::Text::Bold);
                    ammun_count->setTextSize(20);
                    ammun_count->getRenderer()->setBackgroundColor(sf::Color::Black);
                    ammun_count->setAutoSize(true);
                    ammun_count->setPosition(50, WINDOW_HEIGHT - 50);
                    gui.add(ammun_count);
                }
                catch (const tgui::Exception& e) {
                    std::cerr << "Failed to load TGUI widgets: " << e.what() << std::endl;
                    assert(0);
                }
                ammuncount = true;
            }

            if (tanksnameloaded) {

                for (auto i = 0; i < tanks.size(); i++) {
                    auto x  = tanks[i]->getViewCoordX(match);
                    auto y  = tanks[i]->getViewCoordY(match);
                    auto sx = tanks[i]->getSizeX();
                    auto sy = tanks[i]->getSizeY();

                    try {
                        nameTanks[i]->setPosition(x - 0.5*sx, y+sy*0.8);
//                        nameTanks[i]->setSize(5 * sx, 5 * sy * 0.3); //it's large size

                        if(!tanks[i]->isAlive()) {
                            nameTanks[i]->setVisible(false);
                        }
                    }
                    catch (const tgui::Exception& e) {
                        std::cerr << "Failed to load TGUI widgets: " << e.what() << std::endl;
                        assert(0);
                    }
                }

            }

            else {
                for (auto i = 0; i < tanks.size(); i++) {

                    try {
                        nameTanks.push_back(tgui::Label::create(tanks[i]->getName()));
                        nameTanks[i]->getRenderer()->setTextColor(sf::Color::White);
                        nameTanks[i]->getRenderer()->setTextStyle(sf::Text::Bold);
                        nameTanks[i]->setTextSize(20);
                        nameTanks[i]->getRenderer()->setBackgroundColor(sf::Color::Black);
                        nameTanks[i]->setAutoSize(true);
                        nameTanks[i]->setVisible(false);
                        gui.add(nameTanks[i]);
                    }
                    catch (const tgui::Exception& e) {
                        std::cerr << "Failed to load TGUI widgets: " << e.what() << std::endl;
                        assert(0);
                    }
                }
                tanksnameloaded = true;
            }


            if(heathbarloaded) {

                for (auto i = 0; i < tanks.size(); i++) {

                    auto h  = tanks[i]->getHealth();
                    auto mh = tanks[i]->getMaxHealth();
                    auto x  = tanks[i]->getViewCoordX(match);
                    auto y  = tanks[i]->getViewCoordY(match);
                    auto sx = tanks[i]->getSizeX();
                    auto sy = tanks[i]->getSizeY();

                    auto name = tanks[i]->getName();

                    try {
                        healthTanks[i]->setPosition(x - 0.5*sx, y - sy);
                        healthTanks[i]->setSize(sx, sy * 0.3);
                        healthTanks[i]->setValue((unsigned int) (100 * h / mh));
//                        progressBar->setInheritedOpacity(0.5);
                        if(!tanks[i]->isAlive()) {
                            healthTanks[i]->setVisible(false);
                        }
                    }
                    catch (const tgui::Exception& e) {
                        std::cerr << "Failed to load TGUI widgets: " << e.what() << std::endl;
                        assert(0);
                    }
                }
            }
            else {
                for (auto i = 0; i < tanks.size(); i++) {

                    try {
                        healthTanks.push_back(tgui::ProgressBar::create());
                        gui.add(healthTanks[i]);
                    }
                    catch (const tgui::Exception& e) {
                        std::cerr << "Failed to load TGUI widgets: " << e.what() << std::endl;
                        assert(0);
                    }
                }
                heathbarloaded = true;
            }
            break;
        }
    }
    gui.draw();
}

void InterfaceManager::setMapName(const std::string &the_mapName) {
    InterfaceManager::mapName = the_mapName;
}

void InterfaceManager::signalHandler1(InterfaceManager *manager) {
    std::cout << "SinglePlayer pressed" << std::endl;
    manager->setState(GAME_STATE_CREATE_MATCH);
}

void InterfaceManager::signalHandler2(InterfaceManager *manager) {
    std::cout << "MultiPlayer pressed" << std::endl;
    manager->setState(GAME_STATE_ENTER_LOGIN_PASSWORD);
}

void InterfaceManager::signalHandler3(InterfaceManager *manager) {
    std::cout << "EXIT pressed" << std::endl;
}

void InterfaceManager::signalHandler4(InterfaceManager *manager) {
    std::cout << "SETTINGS pressed" << std::endl;
}

void InterfaceManager::setState(gameState_t gameState) {
    *InterfaceManager::state = gameState;
}

std::pair<std::string, std::string> InterfaceManager::login() {
    return WidgetsMenu::login();
}

void InterfaceManager::setObjectManager(ObjectManager *objectManager) {
    InterfaceManager::objectManager = objectManager;
}

void InterfaceManager::showHealth() {
    auto tanks = objectManager->getTanks();
    for (auto i = 0; i < nameTanks.size(); i++) {
        if(tanks[i]->isAlive()) {
            nameTanks[i]->setVisible(true);
        }
    }
}

void InterfaceManager::cancelShow() {
    auto tanks = objectManager->getTanks();
    for (auto i = 0; i < nameTanks.size(); i++) {
        if(tanks[i]->isAlive()) {
            nameTanks[i]->setVisible(false);
        }
    }
}

void InterfaceManager::ShowMatchesDialog(json j) {
    json tmp;
    tmp["amount_of_players_in_match"] = {1, 0, 4}; // кол-во игроков в матче
    tmp["names"] = {"Join us", "Test match", "Hello everyone"}; // название матча
    tmp["who"] = {"Kezhik", "Maxim", "Artem"}; // кто создал матч
    tmp["id"] = {67, 33, 108};

    std::vector <int> amount_of_players_in_match = tmp["amount_of_players_in_match"].get < std::vector <int> >();
    std::vector <std::string> names = tmp["names"].get <std::vector <std::string> >();
    std::vector <std::string> who = tmp["who"].get <std::vector <std::string> >();
    std::vector <int> id = tmp["id"].get < std::vector <int> >();
}

void InterfaceManager::setMatch(Match *match) {
    InterfaceManager::match = match;
}


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
                                   Match *iMatch, std::vector<json> &iMatches) :

        mainWindow(the_mainWindow),
        objectManager(the_objectManager),
        state(the_state),
        gui(the_gui),
        networkManager(the_networkmanager),
        match(iMatch),
        matches(iMatches)
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

        buttonLogin->connect("pressed", [&](){
            std::pair <std::string, std::string> tmp = WidgetsMenu::login();
            if (!tmp.first.empty()) {
                networkManager.authorize(tmp);
            }
        });

        buttonCancel->connect("pressed", [&](){
            WidgetsMenu::change_ava(0);
        });


        static auto settingsWindow = tgui::MessageBox::create();
        settingsWindow->setSize({"80%", "75%"});
        settingsWindow->setPosition({"10%", "10%"});
        settingsWindow->setTitle("Settings");
        settingsWindow->setVisible(false);
        settingsWindow->setPositionLocked(true);
        gui.add(settingsWindow);
        WidgetsMenu::add_widget(settingsWindow);

        static auto settingsAccept = tgui::Button::create("Accept");
        settingsAccept->setSize({"20%", "12%"});
        settingsAccept->setPosition({"65%", "80%"});
        settingsAccept->setTextSize(0);
        settingsWindow->add(settingsAccept);

        static auto settingsCancel = tgui::Button::create("Cancel");
        settingsCancel->setSize({"20%", "12%"});
        settingsCancel->setPosition({"15%", "80%"});
        settingsCancel->setTextSize(0);
        settingsWindow->add(settingsCancel);


        static auto BUL = tgui::Group::create();
        BUL->setSize("25%", "90%");
        BUL->setPosition("0%", "5%");
        settingsWindow->add(BUL);

        static auto labelBullets = tgui::Label::create();
        labelBullets->setText("Bullets:");
        labelBullets->setPosition("10%", "0%");
        labelBullets->setTextSize(20);
        BUL->add(labelBullets);

        static auto radioButton1 = tgui::RadioButton::create();
        radioButton1->setPosition("10%", "15%");
        radioButton1->setText("1");
        radioButton1->setSize(20, 20);
        BUL->add(radioButton1);

        static auto radioButton2 = tgui::RadioButton::create();
        radioButton2->setPosition("10%", "25%");
        radioButton2->setText("2");
        radioButton2->setSize(20, 20);
        BUL->add(radioButton2);

        static auto radioButton3 = tgui::RadioButton::create();
        radioButton3->setPosition("10%", "35%");
        radioButton3->setText("3");
        radioButton3->setSize(20, 20);
        BUL->add(radioButton3);


        static auto SKIN = tgui::Group::create();
        SKIN->setSize("25%", "90%");
        SKIN->setPosition("25%", "5%");
        settingsWindow->add(SKIN);

        static auto labelSkin = tgui::Label::create();
        labelSkin->setText("Skin:");
        labelSkin->setPosition("10%", "0%");
        labelSkin->setTextSize(20);
        SKIN->add(labelSkin);

        static auto skinButton1 = tgui::RadioButton::create();
        skinButton1->setPosition("10%", "15%");
        skinButton1->setText("1");
        skinButton1->setSize(20, 20);
        SKIN->add(skinButton1);

        static auto skinButton2 = tgui::RadioButton::create();
        skinButton2->setPosition("10%", "25%");
        skinButton2->setText("2");
        skinButton2->setSize(20, 20);
        SKIN->add(skinButton2);

        static auto skinButton3 = tgui::RadioButton::create();
        skinButton3->setPosition("10%", "35%");
        skinButton3->setText("3");
        skinButton3->setSize(20, 20);
        SKIN->add(skinButton3);

        static auto skinButton4 = tgui::RadioButton::create();
        skinButton4->setPosition("10%", "45%");
        skinButton4->setText("3");
        skinButton4->setSize(20, 20);
        SKIN->add(skinButton4);

        static auto skinButton5 = tgui::RadioButton::create();
        skinButton5->setPosition("10%", "55%");
        skinButton5->setText("3");
        skinButton5->setSize(20, 20);
        SKIN->add(skinButton5);

        static auto tankView = tgui::Panel::create();
        tankView->setSize("40%", "40%");
        tankView->setPosition("55%", "5%");
        settingsWindow->add(tankView);


        static auto labelColor = tgui::Label::create();
        labelColor->setText("Color:");
        labelColor->setPosition("55%", "50%");
        labelColor->setTextSize(20);
        settingsWindow->add(labelColor);

        static auto labelBulDam = tgui::Label::create();
        labelBulDam->setText("Bullet Damage:");
        labelBulDam->setPosition("55%", "60%");
        labelBulDam->setTextSize(20);
        settingsWindow->add(labelBulDam);

        static auto labelRelTime = tgui::Label::create();
        labelRelTime->setText("Reload time:");
        labelRelTime->setPosition("55%", "70%");
        labelRelTime->setTextSize(20);
        settingsWindow->add(labelRelTime);


        settingsButton->connect("pressed", &InterfaceManager::signalHandler4, this);
        settingsButton->connect("pressed", [&](){
            WidgetsMenu::change_ava(2);
        });

        settingsAccept->connect("pressed", [&](){
            WidgetsMenu::change_ava(3);
        });

        settingsCancel->connect("pressed", [&](){
            WidgetsMenu::change_ava(3);
        });
    }
    catch (const tgui::Exception& e) {
        std::cerr << "Failed to load TGUI widgets: " << e.what() << std::endl;
        assert(0);
    }
}

void InterfaceManager::makeInterface() {
    switch (*state) {
        case GAME_STATE_CREATE_MATCH:
        case GAME_STATE_CREATE_MULTIPLAYER_MATCH:
        {
            gui.removeAllWidgets();
            break;
        }
        case GAME_STATE_MATCH_CHOOSE: {
            renderMatches();
            break;
        }
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
                    ammun_count->setPosition(50, WINDOW_HEIGHT - 100);
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

                    auto x  = tanks[i]->getViewCoordX();
                    auto y  = tanks[i]->getViewCoordY();
                    auto sx = tanks[i]->getSizeX();
                    auto sy = tanks[i]->getSizeY();

                    try {
                        nameTanks[i]->setPosition(x - 0.5*sx, y+sy*0.4);
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
                    auto x  = tanks[i]->getViewCoordX();
                    auto y  = tanks[i]->getViewCoordY();
                    auto sx = tanks[i]->getSizeX();
                    auto sy = tanks[i]->getSizeY();

                    auto name = tanks[i]->getName();

                    try {
                        healthTanks[i]->setPosition(x - 0.5*sx, y - sy*1.6);
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

void InterfaceManager::setMatches(const std::vector<json> &matches) {
    InterfaceManager::matches = matches;
}

void InterfaceManager::renderMatches() {
    if (matchesLoaded) {

    } else {
        gui.removeAllWidgets();
        try {
//            static auto picture = tgui::Picture::create({"images/forest.svg", {0, 0, 1000, 700}}); //Failed to create texture, invalid size (0x0)
//            picture->setSize({"100%", "100%"});
//            gui.add(picture);

            tgui::Theme theme{"./sources/themes/Black.txt"};

            auto label = tgui::Label::create();
            label->setRenderer(theme.getRenderer("Label"));
            label->setText("Matches list:");
            label->setPosition(10, 90);
            label->setTextSize(18);
            gui.add(label);


            label = tgui::Label::create();
            label->setRenderer(theme.getRenderer("Label"));
            label->setText("Choose a match from the list");
            label->setPosition(10, 240);
            label->setTextSize(18);
            gui.add(label);

            auto listBox = tgui::ListBox::create();
            listBox->setRenderer(theme.getRenderer("ListBox"));
            listBox->setSize(250, 120);
            listBox->setItemHeight(24);
            listBox->setPosition(10, 340);


            for (int i = 0; i < matches.size(); ++i) {
//                std::cout << matches[i] << std::endl;
                listBox->addItem(matches[i]["name"].get<std::string>());

            }
            ///@todo add items

//            listBox->addItem("Item 2");
//            listBox->addItem("Item 3");
            gui.add(listBox);


            matchesLoaded = true;
        }
        catch (const tgui::Exception &e) {
            std::cerr << "TGUI Exception: " << e.what() << std::endl;
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


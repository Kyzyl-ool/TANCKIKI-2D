//
// Created by Кежик Кызыл-оол on 2019-02-26.
//

#include <iostream>
#include <fstream>
#include "InterfaceManager.hpp"
#include "WidgetsMenu.hpp"
#include "Tank.hpp"
#include "Match.hpp"


InterfaceManager::InterfaceManager(sf::RenderWindow &the_mainWindow, ObjectManager *the_objectManager,
                                   gameState_t *the_state,
                                   tgui::Gui &the_gui, NetworkManager &the_networkmanager, Match *iMatch,
                                   std::vector<json> &iMatches,
                                   json &iCurrentMatch) :

        mainWindow(the_mainWindow),
        objectManager(the_objectManager),
        state(the_state),
        gui(the_gui),
        networkManager(the_networkmanager),
        match(iMatch),
        matches(iMatches),
        currentMatch(iCurrentMatch)
{

}

void InterfaceManager::loadMainMenuWidgets() {
    try {
        static auto picture = tgui::Picture::create({"images/forest.svg", sf::IntRect(0, 0, 1000, 700)}); //Failed to create texture, invalid size (0x0)
        picture->setSize("100%", "100%");
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


        appendSignal(singleButton, singleButton->connect("pressed", &InterfaceManager::signalHandler1, this));
        appendSignal(singleButton, singleButton->connect("pressed", [&](){
            gui.remove(picture);
            gui.remove(singleButton);
            gui.remove(multiButton);
            gui.remove(quitButton);
            gui.remove(settingsButton);
            WidgetsMenu::widget_remove();
        }));

        appendSignal(multiButton, multiButton->connect("pressed", &InterfaceManager::signalHandler2, this));
        appendSignal(multiButton, multiButton->connect("pressed", [&](){
            WidgetsMenu::change_ava(1);
        }));

        appendSignal(quitButton, quitButton->connect("pressed", &InterfaceManager::signalHandler3, this));
        appendSignal(quitButton, quitButton->connect("pressed", [&](){ mainWindow.close(); }));

        appendSignal(buttonLogin, buttonLogin->connect("pressed", [&](){
            std::pair <std::string, std::string> tmp = WidgetsMenu::login();
            if (!tmp.first.empty()) {
                networkManager.authorize(tmp);
            }
        }));

        appendSignal(buttonCancel, buttonCancel->connect("pressed", [&](){
            WidgetsMenu::change_ava(0);
        }));


        static auto settingsWindow = tgui::MessageBox::create();
        settingsWindow->setSize({"80%", "75%"});
        settingsWindow->setPosition({"10%", "10%"});
        settingsWindow->setTitle("Settings");
        settingsWindow->setVisible(false);
        settingsWindow->setPositionLocked(true);
        gui.add(settingsWindow);
        WidgetsMenu::add_widget(settingsWindow);

        static auto settingsBack = tgui::Button::create("Back");
        settingsBack->setSize({"15%", "7%"});
        settingsBack->setPosition({"7%", "90%"});
        settingsBack->setTextSize(0);
        settingsWindow->add(settingsBack);


        static auto BUL = tgui::Group::create();
        BUL->setSize("25%", "90%");
        BUL->setPosition("0%", "5%");
        settingsWindow->add(BUL);

        static auto labelBullets = tgui::Label::create();
        labelBullets->setText("Bullets:");
        labelBullets->setPosition("10%", "0%");
        labelBullets->setTextSize(20);
        BUL->add(labelBullets);

        std::ifstream fi("./sources/json/armament.json");
        json armament;
        fi >> armament;
        int bullet = armament["bullet"];
        int skin = armament["skin"];

        static auto radioButton1 = tgui::RadioButton::create();
        radioButton1->setPosition("10%", "15%");
        radioButton1->setText("Light");
        radioButton1->setSize(20, 20);
        BUL->add(radioButton1);

        static auto radioButton2 = tgui::RadioButton::create();
        radioButton2->setPosition("10%", "25%");
        radioButton2->setText("Medium");
        radioButton2->setSize(20, 20);
        BUL->add(radioButton2);

        static auto radioButton3 = tgui::RadioButton::create();
        radioButton3->setPosition("10%", "35%");
        radioButton3->setText("Powerful");
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
        skinButton1->setText("Yellow");
        skinButton1->setSize(20, 20);
        SKIN->add(skinButton1);

        static auto skinButton2 = tgui::RadioButton::create();
        skinButton2->setPosition("10%", "25%");
        skinButton2->setText("Green");
        skinButton2->setSize(20, 20);
        SKIN->add(skinButton2);

        static auto skinButton3 = tgui::RadioButton::create();
        skinButton3->setPosition("10%", "35%");
        skinButton3->setText("Purple");
        skinButton3->setSize(20, 20);
        SKIN->add(skinButton3);

        static auto skinButton4 = tgui::RadioButton::create();
        skinButton4->setPosition("10%", "45%");
        skinButton4->setText("Blue");
        skinButton4->setSize(20, 20);
        SKIN->add(skinButton4);

        static auto skinButton5 = tgui::RadioButton::create();
        skinButton5->setPosition("10%", "55%");
        skinButton5->setText("Violet");
        skinButton5->setSize(20, 20);
        SKIN->add(skinButton5);

        fi.close();

        sf::Image gugugu;

        gugugu.loadFromFile(IMAGE_FOR_MAP);

        sf::Texture texture1;
        texture1.loadFromImage(gugugu,sf::IntRect(0,0,64,64));

        sf::Texture back;
        back.create(64*9,64*4);

        for(int i =0;i< 4; ++i) {
            for(int j=0;j<9; ++j) {
                back.update(texture1, 64*j, 64*i);
            }
        }

        static auto background = tgui::Picture::create(back);

        static auto tankView = tgui::Panel::create();
        tankView->setSize("50%", "40%");
        tankView->setPosition("45%", "5%");
        settingsWindow->add(tankView);

        static auto bulletView = tgui::Group::create();
        bulletView->setSize("5%", "40%");
        bulletView->setPosition("87%", "5%");
        settingsWindow->add(bulletView);

        static auto label1 = tgui::Label::create();
        label1->setText("HP:");
        label1->setSize("25%","10%");
        label1->setPosition("45%", "50%");
        label1->setTextSize(20);
        label1->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Right);
        settingsWindow->add(label1);

        static auto label2 = tgui::Label::create();
        label2->setText("Bullet damage: ");
        label2->setSize("25%","10%");
        label2->setPosition("45%", "60%");
        label2->setTextSize(20);
        label2->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Right);
        settingsWindow->add(label2);

        static auto label3 = tgui::Label::create();
        label3->setText("Reload time: ");
        label3->setSize("25%","10%");
        label3->setPosition("45%", "70%");
        label3->setTextSize(20);
        label3->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Right);
        settingsWindow->add(label3);

        static auto labelColor = tgui::Label::create("1000");
        labelColor->setSize("25%","10%");
        labelColor->setPosition("70%", "50%");
        labelColor->setTextSize(20);
        settingsWindow->add(labelColor);

        static auto labelBulDam = tgui::Label::create();
        labelBulDam->setSize("25%","10%");
        labelBulDam->setPosition("70%", "60%");
        labelBulDam->setTextSize(20);
        settingsWindow->add(labelBulDam);

        static auto labelRelTime = tgui::Label::create();
        labelRelTime->setSize("25%","10%");
        labelRelTime->setPosition("70%", "70%");
        labelRelTime->setTextSize(20);
        settingsWindow->add(labelRelTime);

        auto tankTexture1 = tgui::Texture("images/Htanks.png", {295,214,95,53});
        static auto tankPicture1 = tgui::Picture::create(tankTexture1);
        auto towerTexture1 = tgui::Texture("images/Htanks.png", {298,174,86,40});
        static auto towerPicture1 = tgui::Picture::create(towerTexture1);

        auto tankTexture2 = tgui::Texture("images/Htanks.png", {297,108,95,53});
        static auto tankPicture2 = tgui::Picture::create(tankTexture2);
        auto towerTexture2 = tgui::Texture("images/Htanks.png", {300,68,86,40});
        static auto towerPicture2 = tgui::Picture::create(towerTexture2);

        auto tankTexture3 = tgui::Texture("images/Htanks.png", {289,525,95,53});
        static auto tankPicture3 = tgui::Picture::create(tankTexture3);
        auto towerTexture3 = tgui::Texture("images/Htanks.png", {292,485,86,40});
        static auto towerPicture3 = tgui::Picture::create(towerTexture3);

        auto tankTexture4 = tgui::Texture("images/Htanks.png", {398,109,95,53});
        static auto tankPicture4 = tgui::Picture::create(tankTexture4);
        auto towerTexture4 = tgui::Texture("images/Htanks.png", {401,69,86,40});
        static auto towerPicture4 = tgui::Picture::create(towerTexture4);

        auto tankTexture5 = tgui::Texture("images/Htanks.png", {196,108,95,53});
        static auto tankPicture5 = tgui::Picture::create(tankTexture5);
        auto towerTexture5 = tgui::Texture("images/Htanks.png", {199,68,86,40});
        static auto towerPicture5 = tgui::Picture::create(towerTexture5);

        tankPicture1->setPosition(40, "26%");
        tankPicture2->setPosition(40, "26%");
        tankPicture3->setPosition(40, "26%");
        tankPicture4->setPosition(40, "26%");
        tankPicture5->setPosition(40, "26%");

        towerPicture1->setPosition(105, 5 + tankView->getSize().y * 0.26);
        towerPicture2->setPosition(105, 5 + tankView->getSize().y * 0.26);
        towerPicture3->setPosition(105, 5 + tankView->getSize().y * 0.26);
        towerPicture4->setPosition(105, 5 + tankView->getSize().y * 0.26);
        towerPicture5->setPosition(105, 5 + tankView->getSize().y * 0.26);

        auto bulletTexture1 = tgui::Texture("images/bullet_1.png", {20,13,10,8});
        static auto bulletPicture1 = tgui::Picture::create(bulletTexture1);

        auto bulletTexture2 = tgui::Texture("images/bullet_1.png", {39,222,20,11});
        static auto bulletPicture2 = tgui::Picture::create(bulletTexture2);

        auto bulletTexture3 = tgui::Texture("images/bullet_1.png", {279,214,15,12});
        static auto bulletPicture3 = tgui::Picture::create(bulletTexture3);

        if (changesizebool) {

        } else {
            bulletPicture1->setSize({bulletPicture1->getSize().x * 1.5, bulletPicture1->getSize().y * 1.5});
            bulletPicture2->setSize({bulletPicture2->getSize().x * 1.5, bulletPicture2->getSize().y * 1.5});
            bulletPicture3->setSize({bulletPicture3->getSize().x * 1.5, bulletPicture3->getSize().y * 1.5});
            changesizebool = true;
        }
        bulletPicture1->setPosition("2%", "49%");
        bulletPicture2->setPosition("2%", "48%"); //+26
        bulletPicture3->setPosition("2%", "48%");

        tankPicture1->setSize({"50%", "50%"});
        towerPicture1->setSize({"50%", "50%"});
        tankPicture2->setSize({"50%", "50%"});
        towerPicture2->setSize({"50%", "50%"});
        tankPicture3->setSize({"50%", "50%"});
        towerPicture3->setSize({"50%", "50%"});
        tankPicture4->setSize({"50%", "50%"});
        towerPicture4->setSize({"50%", "50%"});
        tankPicture5->setSize({"50%", "50%"});
        towerPicture5->setSize({"50%", "50%"});

        switch (skin) {
            case 1:
                skinButton1->setChecked(true);
                tankView->add(background);
                tankView->add(tankPicture1);
                tankView->add(towerPicture1);
                break;
            case 2:
                skinButton2->setChecked(true);
                tankView->add(background);
                tankView->add(tankPicture2);
                tankView->add(towerPicture2);
                break;
            case 3:
                skinButton3->setChecked(true);
                tankView->add(background);
                tankView->add(tankPicture3);
                tankView->add(towerPicture3);
                break;
            case 4:
                skinButton4->setChecked(true);
                tankView->add(background);
                tankView->add(tankPicture4);
                tankView->add(towerPicture4);
                break;
            case 5:
                skinButton5->setChecked(true);
                tankView->add(background);
                tankView->add(tankPicture5);
                tankView->add(towerPicture5);
                break;
            default:
                assert(!"Invalid skin");
        }

        switch (bullet) {
            case 1:
                radioButton1->setChecked(true);
                bulletView->add(bulletPicture1);
                labelRelTime->setText(std::to_string(int(RECHARGE_OF_LOWSHOT))+" ms");
                labelBulDam->setText(std::to_string(DAMAGE_OF_LOWSHOT)+" hp");
                break;
            case 2:
                radioButton2->setChecked(true);
                bulletView->add(bulletPicture2);
                labelRelTime->setText(std::to_string(int(RECHARGE_OF_MIDDLESHOT))+" ms");
                labelBulDam->setText(std::to_string(DAMAGE_OF_MIDDLESHOT)+" hp");
                break;
            case 3:
                radioButton3->setChecked(true);
                bulletView->add(bulletPicture3);
                labelRelTime->setText(std::to_string(int(RECHARGE_OF_POWERFULLSHOT))+" ms");
                labelBulDam->setText(std::to_string(DAMAGE_OF_POWERFULLSHOT)+" hp");
                break;
            default:
                assert(!"Invalid radiobutton");
        }

        appendSignal(radioButton1, radioButton1->connect("checked", [&](){
            bulletView->removeAllWidgets();
            bulletView->add(bulletPicture1);
            labelRelTime->setText(std::to_string(int(RECHARGE_OF_LOWSHOT))+" ms");
            labelBulDam->setText(std::to_string(DAMAGE_OF_LOWSHOT)+" hp");
        }));

        appendSignal(radioButton2, radioButton2->connect("checked", [&](){
            bulletView->removeAllWidgets();
            bulletView->add(bulletPicture2);
            labelRelTime->setText(std::to_string(int(RECHARGE_OF_MIDDLESHOT))+" ms");
            labelBulDam->setText(std::to_string(DAMAGE_OF_MIDDLESHOT)+" hp");
        }));

        appendSignal(radioButton3, radioButton3->connect("checked", [&](){
            bulletView->removeAllWidgets();
            bulletView->add(bulletPicture3);
            labelRelTime->setText(std::to_string(int(RECHARGE_OF_POWERFULLSHOT))+" ms");
            labelBulDam->setText(std::to_string(DAMAGE_OF_POWERFULLSHOT)+" hp");
        }));

        skinButton1->connect("checked", [&](){
            tankView->removeAllWidgets();
            tankView->add(background);
            tankView->add(tankPicture1);
            tankView->add(towerPicture1);
        });
        skinButton2->connect("checked", [&](){
            tankView->removeAllWidgets();
            tankView->add(background);
            tankView->add(tankPicture2);
            tankView->add(towerPicture2);
        });
        skinButton3->connect("checked", [&](){
            tankView->removeAllWidgets();
            tankView->add(background);
            tankView->add(tankPicture3);
            tankView->add(towerPicture3);
        });
        skinButton4->connect("checked", [&](){
            tankView->removeAllWidgets();
            tankView->add(background);
            tankView->add(tankPicture4);
            tankView->add(towerPicture4);
        });
        skinButton5->connect("checked", [&](){
            tankView->removeAllWidgets();
            tankView->add(background);
            tankView->add(tankPicture5);
            tankView->add(towerPicture5);
        });

//        gui.add(towerPicture);


//        sf:: setTexture("images/Htanks.png");
//        setSprite(297,108,95,53);
//        setSpriteTower(300,68,86,40);

        appendSignal(settingsButton, settingsButton->connect("pressed", &InterfaceManager::signalHandler4, this));
        appendSignal(settingsButton, settingsButton->connect("pressed", [&](){
            WidgetsMenu::change_ava(2);
        }));

        settingsBack->connect("pressed", [&](){
            WidgetsMenu::change_ava(3);
            int bullet = -1, skin = -1;
            if (radioButton1->isChecked())
                bullet = 1;
            if (radioButton2->isChecked())
                bullet = 2;
            if (radioButton3->isChecked())
                bullet = 3;
            if (skinButton1->isChecked())
                skin = 1;
            if (skinButton2->isChecked())
                skin = 2;
            if (skinButton3->isChecked())
                skin = 3;
            if (skinButton4->isChecked())
                skin = 4;
            if (skinButton5->isChecked())
                skin = 5;


            assert(!(bullet == -1 || skin == -1));
            std::ofstream fo("./sources/json/armament.json");
            json j;
            j["bullet"] = bullet;
            j["skin"] = skin;
            fo << j << std::endl;
            fo.close();
        });
    }
    catch (const tgui::Exception& e) {
        std::cerr << "Failed to load TGUI widgets: " << e.what() << std::endl;
        assert(0);
    }
}

void InterfaceManager::makeInterface() {
    switch (*state) {
        case GAME_STATE_MATCH_PAUSE: {
            if (pauseloaded) {
                gui.get("LaL")->setVisible(true);
            } else {
                try {
                    static auto pauseWindow = tgui::MessageBox::create();
                    pauseWindow->setSize({"40%", "30%"});
                    pauseWindow->setPosition({"30%", "31%"});
                    pauseWindow->setTitle("Pause");
//                    pauseWindow->setText("Do you really wanna exit?");
                    pauseWindow->setTitleTextSize(12);
                    pauseWindow->setPositionLocked(true);
                    gui.add(pauseWindow);
                    gui.setWidgetName(pauseWindow, "LaL");

                    static auto buttonExit = tgui::Button::create("Exit");
                    buttonExit->setSize({"20%", "16.67%"});
                    buttonExit->setPosition({"60 %", "70%"});
                    buttonExit->setTextSize(0);
                    pauseWindow->add(buttonExit);

                    static auto buttonCancel = tgui::Button::create("Cancel");
                    buttonCancel->setSize({"20%", "16.67%"});
                    buttonCancel->setPosition({"20%", "70%"});
                    buttonCancel->setTextSize(0);
                    pauseWindow->add(buttonCancel);

                    static auto label = tgui::Label::create();
                    label->setSize(pauseWindow->getSize().x, "65%");
                    label->setText("Do you really want to exit?");
                    label->setTextSize(20);
                    label->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
                    label->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);
                    pauseWindow->add(label);
                    appendSignal(buttonExit, buttonExit->connect("pressed", [&]() {
                        *state = GAME_STATE_MAIN_MENU;
                    }));

                    appendSignal(buttonCancel, buttonCancel->connect("pressed", [&](){
//                        pauseloaded = false;
//                        gui.remove(pauseWindow);
//                        pauseWindow->setVisible(false);
                        *state = GAME_STATE_MATCH;
                    }));

                }
                catch (const tgui::Exception &e) {
                    std::cerr << "Failed to load TGUI widgets: " << e.what() << std::endl;
                    assert(0);
                }

                pauseloaded = true;
            }
            break;
        }
        case GAME_STATE_MAIN_MENU: {
            if (!mainmenuloaded) {
                for (const auto &item : beingDisconnected) {
                    item.first->disconnect(item.second);
                }
                gui.removeAllWidgets();
                loadMainMenuWidgets();
                mainmenuloaded = true;
            }
            break;
        }
        case GAME_STATE_CREATE_MATCH:
        case GAME_STATE_CREATE_MULTIPLAYER_MATCH:
        {
            matchesLoaded = false;
            tanksnameloaded = false;
            heathbarloaded = false;
            pauseloaded = false;
            mainmenuloaded = false;
            messageloaded = false;
            ammuncount = false;
            noticeadded = false;
            healthTanks.clear();
            nameTanks.clear();
            noticeTanks.clear();
            noticeKilled.clear();

            for (const auto &item : beingDisconnected) {
                item.first->disconnect(item.second);
            }
            gui.removeAllWidgets();
            break;
        }
        case GAME_STATE_MATCH_CHOOSE: {
            renderMatches();
            break;
        }
        case GAME_STATE_MULTIPLAYER_MATCH:
        case GAME_STATE_MATCH: {
            if (pauseloaded)
               gui.get("LaL")->setVisible(false);
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
                    ammun_count->setInheritedOpacity(0.9);
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
                        nameTanks[i]->setText(tanks[i]->getName());
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

            ///@todo: добавить уведомление об убийствах

            if(noticeadded) {
                for (auto i = 0; i < tanks.size(); i++) {

                    if (!tanks[i]->isAlive() && !noticeTanks[i]) {

                        try {
                            if (tanks[i]->getLastEnemy() == -1)
                                noticeKilled[i]->setText("LAVA killed " + tanks[i]->getName());
                            else
                                noticeKilled[i]->setText(tanks[tanks[i]->getLastEnemy()]->getName() + " killed " + tanks[i]->getName());
                            noticeKilled[i]->setPosition(mainWindow.getSize().x - noticeKilled[i]->getSize().x, "5%");
                            noticeKilled[i]->setVisible(true);

                            for (auto j = 0; j < tanks.size(); j++) {
                                if ((j != i) && noticeTanks[j])
                                    noticeKilled[j]->setPosition(noticeKilled[j]->getPosition().x, noticeKilled[j]->getPosition().y + 27);
                            }

                        }
                        catch (const tgui::Exception &e) {
                            std::cerr << "Failed to load TGUI widgets: " << e.what() << std::endl;
                            assert(0);
                        }
                        noticeTanks[i] = true;
                    }
                }
            } else {
                for (auto i = 0; i < tanks.size(); i++) {

                    noticeTanks.push_back(false);

                    try {
                        noticeKilled.push_back(tgui::Label::create());
                        noticeKilled[i]->setTextSize(20);
                        noticeKilled[i]->getRenderer()->setBackgroundColor(sf::Color::Black);
                        noticeKilled[i]->getRenderer()->setTextColor(sf::Color::White);
                        noticeKilled[i]->setInheritedOpacity(0.7);
                        noticeKilled[i]->setVisible(false);
                        gui.add(noticeKilled[i]);
                    }
                    catch (const tgui::Exception &e) {
                        std::cerr << "Failed to load TGUI widgets: " << e.what() << std::endl;
                        assert(0);
                    }
                }
                noticeadded = true;
            }
            break;
        }
        case GAME_STATE_MULTIPLAYER_ENDED:
        case GAME_STATE_MATCH_ENDED: {
            if (!messageloaded)
            try {
                for (const auto &item : beingDisconnected) {
                    item.first->disconnect(item.second);
                }
                gui.removeAllWidgets();
                static auto windowWin = tgui::MessageBox::create();
                windowWin->setPosition("35%", "40%");
                windowWin->setSize("30%","20%");
                gui.add(windowWin);

                static auto label = tgui::Label::create(objectManager->getWinner()->getName()+" won!");
                label->setSize(windowWin->getSize().x, "65%");
                label->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
                label->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);
                label->setTextSize(20);
                windowWin->add(label);

                static auto buttonExit = tgui::Button::create("Exit");
                buttonExit->setSize("20%","20%");
                buttonExit->setPosition("40%","65%");
                windowWin->add(buttonExit);

                appendSignal(buttonExit, buttonExit->connect("pressed", [&](){
                    *state = GAME_STATE_MAIN_MENU;
                }));

                messageloaded = true;

            }
            catch (const tgui::Exception &e) {
                std::cerr << "Failed to load TGUI widgets: " << e.what() << std::endl;
                assert(0);
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
        for (const auto &item : beingDisconnected) {
            item.first->disconnect(item.second);
        }
        gui.removeAllWidgets();
        try {
//            static auto picture = tgui::Picture::create({"images/forest.svg", {0, 0, 1000, 700}}); //Failed to create texture, invalid size (0x0)
//            picture->setSize({"100%", "100%"});
//            gui.add(picture);

            tgui::Theme theme{"./sources/themes/Black.txt"};

            static auto labelList = tgui::Label::create();
            labelList->setRenderer(theme.getRenderer("Label"));
            labelList->setText("Matches list:");
            labelList->setPosition("5%", "10%");
            labelList->setTextSize(20);
            gui.add(labelList);

            static auto butRefresh = tgui::BitmapButton::create();
            butRefresh->setRenderer(theme.getRenderer("Button"));
            butRefresh->setImage("images/refresh.png");
            butRefresh->setImageScaling(0.8);
            butRefresh->setSize({"5%", mainWindow.getSize().x * 0.05});
            butRefresh->setPosition({"40%", "8%"});
            butRefresh->setTextSize(20);
            gui.add(butRefresh);

            static auto labelChoose = tgui::Label::create();
            labelChoose->setRenderer(theme.getRenderer("Label"));
            labelChoose->setText("Choose a match from the list");
            labelChoose->setPosition("55%", "45%");
            labelChoose->setTextSize(20);
            gui.add(labelChoose);

            static auto listBox = tgui::ListBox::create();
            listBox->setRenderer(theme.getRenderer("ListBox"));
            listBox->setSize("40%", "65%");
            listBox->setItemHeight(24);
            listBox->setPosition("5%", "20%");

            for (int i = 0; i < matches.size(); ++i) {
//                std::cout << matches[i] << std::endl;
                listBox->addItem(matches[i]["name"].get<std::string>());

            }
            ///@todo add items (вроде они уже спокойно добавляются)

//            listBox->addItem("Item 2");
//            listBox->addItem("Item 3");
            gui.add(listBox);
            gui.setWidgetName(listBox, "ListBox");


            static auto butBack = tgui::Button::create("Back");
            butBack->setRenderer(theme.getRenderer("Button"));
            butBack->setSize({"15%", "7%"});
            butBack->setPosition({"5%", "90%"});
            butBack->setTextSize(20);
            gui.add(butBack);

            static auto butCreate = tgui::Button::create("Create new");
            butCreate->setRenderer(theme.getRenderer("Button"));
            butCreate->setSize({"20%", "7%"});
            butCreate->setPosition({"25%", "90%"});
            butCreate->setTextSize(20);
            gui.add(butCreate);

            static auto groupMatch = tgui::Group::create();
            groupMatch->setVisible(false);
            groupMatch->setSize("40%", "90%");
            groupMatch->setPosition("55%", "10%");
            gui.add(groupMatch);
            gui.setWidgetName(groupMatch, "groupMatch");

            static auto labelInfo = tgui::Label::create();
            labelInfo->setRenderer(theme.getRenderer("Label"));
            labelInfo->setText("Information about match:");
            labelInfo->setPosition("5%", "0%");
            labelInfo->setTextSize(20);
            groupMatch->add(labelInfo);

            static auto labelName = tgui::Label::create();
            labelName->setRenderer(theme.getRenderer("Label"));
            labelName->setText("Name: ");
            labelName->setPosition("0%", "15%");
            labelName->setTextSize(20);
            groupMatch->add(labelName);
            groupMatch->setWidgetName(labelName, "Name");

            static auto labelHost = tgui::Label::create();
            labelHost->setRenderer(theme.getRenderer("Label"));
            labelHost->setText("Host: ");
            labelHost->setPosition("0%", "25%");
            labelHost->setTextSize(20);
            groupMatch->add(labelHost);
            groupMatch->setWidgetName(labelHost, "Host");

            static auto labelCreated = tgui::Label::create();
            labelCreated->setRenderer(theme.getRenderer("Label"));
            labelCreated->setText("Players: ");
            labelCreated->setPosition("0%", "35%");
            labelCreated->setTextSize(20);
            groupMatch->add(labelCreated);
            groupMatch->setWidgetName(labelCreated, "Created");


            static auto playersLabel = tgui::Label::create("Players in game:");
            playersLabel->setPosition("0%", "45%");
            groupMatch->add(playersLabel);
            static auto playersList = tgui::ListView::create();
            playersList->setRenderer(theme.getRenderer("ListView"));
            playersList->setPosition("0%", "50%");
            groupMatch->add(playersList);
            groupMatch->setWidgetName(playersList, "PlayersList");

            static auto butReady = tgui::Button::create("Ready");
            butReady->setVisible(false);
            butReady->setRenderer(theme.getRenderer("Button"));
            butReady->setSize({"15%", "7%"});
            butReady->setPosition({"80%", "90%"});
            butReady->setTextSize(20);
            gui.add(butReady);

            static auto butJoin = tgui::Button::create("Join");
//            butJoin->setVisible(false);
            butJoin->setRenderer(theme.getRenderer("Button"));
            butJoin->setSize({"15%", "7%"});
            butJoin->setPosition({"55%", "90%"});
            butJoin->setTextSize(20);
            gui.add(butJoin);

            static auto createWindow = tgui::MessageBox::create();
            createWindow->setRenderer(theme.getRenderer("MessageBox"));
            createWindow->setSize({"40%", "30%"});
            createWindow->setPosition({"30%", "31%"});
            createWindow->setTitle("Create Match");
            createWindow->setVisible(false);
            createWindow->setPositionLocked(true);
            createWindow->setFocused(true);
            gui.add(createWindow);

            static auto editBox = tgui::EditBox::create();
            editBox->setRenderer(theme.getRenderer("EditBox"));
            editBox->setSize({"66.67%", "25%"});
            editBox->setPosition({"16.67%", "16.67%"});
            editBox->setDefaultText("Insert match name");
            editBox->setTextSize(16);
            createWindow->add(editBox);

            static auto buttonOK = tgui::Button::create("OK");
            buttonOK->setRenderer(theme.getRenderer("Button"));
            buttonOK->setSize({"20%", "16.67%"});
            buttonOK->setPosition({"60 %", "70%"});
            buttonOK->setTextSize(16);
            createWindow->add(buttonOK);

            static auto buttonCancel = tgui::Button::create("Cancel");
            buttonCancel->setRenderer(theme.getRenderer("Button"));
            buttonCancel->setSize({"20%", "16.67%"});
            buttonCancel->setPosition({"20%", "70%"});
            buttonCancel->setTextSize(16);
            createWindow->add(buttonCancel);

            butCreate->connect("pressed", [&](){
                listBox->setEnabled(false);
                butBack->setEnabled(false);
                butCreate->setEnabled(false);
                butReady->setEnabled(false);
                createWindow->setVisible(true);
                butRefresh->setEnabled(false);
                butJoin->setEnabled(false);
            });

            buttonCancel->connect("pressed", [&](){
                listBox->setEnabled(true);
                butBack->setEnabled(true);
                butCreate->setEnabled(true);
                butReady->setEnabled(true);
                createWindow->setVisible(false);
                butRefresh->setEnabled(true);
                butJoin->setEnabled(true);
            });

            appendSignal(butRefresh, butRefresh->connect("pressed", [&](){
                onGlobalRefresh();
            }));

            appendSignal(butReady, butReady->connect("pressed", [&](){
                if(networkManager.isReady())
                {
                    networkManager.setReady(false);
                    butReady->setText("Ready");
                } else {
                    networkManager.setReady(true);
                    butReady->setText("Not ready");
                }
                onMatchRefresh();
            }));

            appendSignal(buttonOK, buttonOK->connect("pressed", [&]() {
                std::string matchName = editBox->getText();
                if (!matchName.empty()) {
                    networkManager.connectToGame(networkManager.createNewGame(matchName, 1));

                    listBox->setEnabled(true);
                    butBack->setEnabled(true);
                    butCreate->setEnabled(true);
                    butReady->setEnabled(true);
                    createWindow->setVisible(false);
                    butRefresh->setEnabled(true);

                    onGlobalRefresh();
                }
            }));


            appendSignal(listBox, listBox->connect("ItemSelected", [&]() {
                if (listBox->getSelectedItemIndex() != -1) {
                    labelChoose->setVisible(false);
                    butReady->setVisible(true);
                    groupMatch->setVisible(true);
                    onMatchRefresh();
                }
                else {
                    labelChoose->setVisible(true);
                    butReady->setVisible(false);
                    groupMatch->setVisible(false);
                }

            }));

            appendSignal(butBack, butBack->connect("pressed", [&](){
                for (const auto &item : beingDisconnected) {
                    item.first->disconnect(item.second);
                }
                gui.removeAllWidgets();
                matchesLoaded = false;
                mainmenuloaded = false;
                *state = GAME_STATE_MAIN_MENU;
                std::cout << "BACK PRESSED" << std::endl;
            }));


            onGlobalRefresh();
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

void InterfaceManager::onGlobalRefresh() {
    json j = networkManager.getGamesList();
    matches.clear();
    if (j.empty()) {
        std::cout << "There are no games in server\n";
    } else {
        int k = 0;
        json game = json(j[std::to_string(k)]);
        while (!game.is_null()) {
            matches.push_back(game);
            k++;
            game = json(j[std::to_string(k)]);
        }
    }

    auto ListBox = gui.get <tgui::ListBox> ("ListBox");
    ListBox->removeAllItems();
    for (const auto &item : matches) {
        ListBox->addItem(item["name"].get <std::string>());
    }


}

void InterfaceManager::onMatchRefresh() {
    auto listBox = gui.get <tgui::ListBox> ("ListBox");
    currentMatch = matches[listBox->getSelectedItemIndex()];
    std::cout << currentMatch << std::endl;

    auto groupMatch = gui.get<tgui::Group>("groupMatch");
    auto labelHost = groupMatch->get<tgui::Label>("Host");
    auto labelPlayers = groupMatch->get<tgui::Label>("Created");
    auto labelName = groupMatch->get<tgui::Label>("Name");

//                    networkManager.get

    labelHost->setText("Host: " + networkManager.getNick(currentMatch["creator"].get<std::string>()));
    labelPlayers->setText("Created: " + currentMatch["time_of_creation"].get<std::string>());
    labelName->setText("Name: " + currentMatch["name"].get<std::string>());

    json j = networkManager.getPlayersInGame(currentMatch["game_id"])["result"];


    std::vector <json> players(0);
    int k = 0;
    json player = json(j[std::to_string(k)]);
//                    std::cout << player << std::endl;
    while (!player.is_null()) {
        players.push_back(player);
        k++;
        player = json(j[std::to_string(k)]);
    }

    auto playersList = groupMatch->get <tgui::ListView> ("PlayersList");
    playersList->removeAllItems();
    for (const auto &item : players) {
        std::string state = (item["ready"].get <bool> ()) ? "ready" : "not ready";
        playersList->addItem(item["nickname"].get <std::string> ()+" ("+state+")");
    }
}

void InterfaceManager::appendSignal(tgui::Widget::Ptr w, int id) {
    beingDisconnected.push_back(std::make_pair(w, id));
}


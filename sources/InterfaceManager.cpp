//
// Created by Кежик Кызыл-оол on 2019-02-26.
//

#include <iostream>
#include "InterfaceManager.hpp"
#include "WidgetsMenu.hpp"


InterfaceManager::InterfaceManager(
        sf::RenderWindow &the_mainWindow, ObjectManager *the_objectManager,
        gameState_t *the_state,
        tgui::Gui &the_gui) :

        mainWindow(the_mainWindow),
        objectManager(the_objectManager),
        state(the_state),
        gui(the_gui)
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

//            loginWindow->setVisible(true);
//            singleButton->setEnabled(false);
//            multiButton->setEnabled(false);
//            settingsButton->setEnabled(false);
//            quitButton->setEnabled(false);
        });

        quitButton->connect("pressed", &InterfaceManager::signalHandler3, this);
        quitButton->connect("pressed", [&](){ mainWindow.close(); });

        settingsButton->connect("pressed", &InterfaceManager::signalHandler4, this);

        buttonLogin->connect("pressed", [&](){

            WidgetsMenu::login();

//            InterfaceManager::login(editBoxUsername,
//                                    editBoxPassword,
//                                    loginWindow,
//                                    singleButton,
//                                    multiButton,
//                                    settingsButton,
//                                    quitButton);
        });

        buttonCancel->connect("pressed", [&](){

            WidgetsMenu::change_ava(0);

//            loginWindow->setVisible(false);
//            singleButton->setEnabled(true);
//            multiButton->setEnabled(true);
//            settingsButton->setEnabled(true);
//            quitButton->setEnabled(true);
        });

        ///@todo check that login AND password were typed
        ///@todo Enter pressed -> LOGIN
    }
    catch (const tgui::Exception& e)
    {
        std::cerr << "Failed to load TGUI widgets: " << e.what() << std::endl;
        assert(0);
    }
}

void InterfaceManager::makeInterface() {
    switch (*state) {
        case GAME_STATE_MATCH: {
            ///@todo проверить, что шкалы здоровья добавлены
            ///@todo если да, то
            ///@todo задать положение
//                auto x = objectManager->getTanks()[0]->getX();
//                auto y =objectManager->getTanks()[0]->getY();
            ///@todo если нет, то
            ///@todo добавить шкалы здоровья
            heathbarloaded = true;
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

/*
void InterfaceManager::login(const tgui::EditBox::Ptr &username,
                             const tgui::EditBox::Ptr &password,
                             const tgui::MessageBox::Ptr &window,
                             const tgui::Button::Ptr &single,
                             const tgui::Button::Ptr &multi,
                             const tgui::Button::Ptr &set,
                             const tgui::Button::Ptr &quit) {
    if (username->getText().isEmpty() || password->getText().isEmpty()) {
        if(username->getText().isEmpty()) {
            username->setDefaultText("Enter the username");
        }
        if(password->getText().isEmpty()) {
            password->setDefaultText("Enter the password");
        }
    }
    else {
        std::cout << "Username: " << username->getText().toAnsiString() << std::endl;
        std::cout << "Password: " << password->getText().toAnsiString() << std::endl;
        ///@todo сформировать http-запрос
        std::string message("Authorization...");

        window->setVisible(false);
        single->setEnabled(true);
        multi->setEnabled(true);
        set->setEnabled(true);
        quit->setEnabled(true);

        ///@todo вызывать это непосредственно,
        ///@todo то есть через класс.
        ///@todo для этого сделать класс

//        loginWindow->setVisible(false);
//        singleButton->setEnabled(true);
//        multiButton->setEnabled(true);
//        settingsButton->setEnabled(true);
//        quitButton->setEnabled(true);
    }

//    WidgetsMenu::get_widget();
}*/


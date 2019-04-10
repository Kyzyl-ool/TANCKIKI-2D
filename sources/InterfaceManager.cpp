//
// Created by Кежик Кызыл-оол on 2019-02-26.
//

#include <iostream>
#include "InterfaceManager.hpp"


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

        static auto singleButton = tgui::Button::create("Singleplayer");
        singleButton->setSize({"50%", "16.67%"});
        singleButton->setPosition({"25%", "10%"});
        singleButton->setTextSize(0);
        gui.add(singleButton);

        static auto fictButton = tgui::Button::create();
        fictButton->setSize(240,160);
        fictButton->setPosition({"21%", "23%"});
        fictButton->setVisible(false);
        gui.add(fictButton);

        static auto multiButton = tgui::Button::create("Multiplayer");
        multiButton->setSize({"50%", "16.67%"});
        multiButton->setPosition({"25%", "40%"});
        multiButton->setTextSize(0);
        gui.add(multiButton);

        static auto quitButton = tgui::Button::create("Exit");
        quitButton->setSize({"50%", "16.67%"});
        quitButton->setPosition({"25%", "70%"});
        quitButton->setTextSize(0);
        gui.add(quitButton);

        static auto loginWindow = tgui::MessageBox::create();
        loginWindow->setSize({"40%", "30%"});
        loginWindow->setPosition({"30%", "31%"});
        loginWindow->setTitle("Please Login");
        loginWindow->setVisible(false);
        loginWindow->setPositionLocked(true);
//            loginWindow->setMaximumSize(fictButton->getSize()); // как эту функцию юзать?
//            loginWindow->setMinimumSize(fictButton->getSize());
        gui.add(loginWindow);

        static auto editBoxUsername = tgui::EditBox::create();
        editBoxUsername->setSize({"66.67%", "12.5%"});
        editBoxUsername->setPosition({"16.67%", "16.67%"});
        editBoxUsername->setDefaultText("Username");
        editBoxUsername->setTextSize(0);
        loginWindow->add(editBoxUsername);

        static auto editBoxPassword = tgui::EditBox::copy(editBoxUsername);
        editBoxPassword->setPosition({"16.67%", "41.6%"});
        editBoxPassword->setPasswordCharacter('*');
        editBoxPassword->setDefaultText("Password");
        editBoxPassword->setTextSize(0);
        loginWindow->add(editBoxPassword);

        static auto button = tgui::Button::create("Login");
        button->setSize({"50%", "16.67%"});
        button->setPosition({"25%", "70%"});
        button->setTextSize(0);
        loginWindow->add(button);

        singleButton->connect("pressed", &InterfaceManager::signalHandler1, this);
        singleButton->connect("pressed", [&](){
            gui.remove(picture);
            gui.remove(singleButton);
            gui.remove(multiButton);
            gui.remove(quitButton);
        });

        multiButton->connect("pressed", &InterfaceManager::signalHandler2, this);
        multiButton->connect("pressed", [&](){ loginWindow->setVisible(true); });

        quitButton->connect("pressed", &InterfaceManager::signalHandler3, this);
        quitButton->connect("pressed", [&](){ mainWindow.close(); });

        button->connect("pressed", &InterfaceManager::login, editBoxUsername, editBoxPassword);
        button->connect("pressed", [&](){ loginWindow->setVisible(false); });
    }
    catch (const tgui::Exception& e)
    {
        std::cerr << "Failed to load TGUI widgets: " << e.what() << std::endl;
        assert(0);
    }
}

void InterfaceManager::makeInterface() {
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

void InterfaceManager::setState(gameState_t gameState) {
    *InterfaceManager::state = gameState;
}

void InterfaceManager::login(const tgui::EditBox::Ptr &username, const tgui::EditBox::Ptr& password) {
    std::cout << "Username: " << username->getText().toAnsiString() << std::endl;
    std::cout << "Password: " << password->getText().toAnsiString() << std::endl;
}
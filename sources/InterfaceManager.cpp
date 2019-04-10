//
// Created by Кежик Кызыл-оол on 2019-02-26.
//

#include <iostream>
#include "InterfaceManager.hpp"
#include "constants/widgets_names.hpp"


InterfaceManager::InterfaceManager(
        sf::RenderWindow &the_mainWindow, ObjectManager *the_objectManager,
        gameState_t *the_state,
        tgui::Gui &the_gui) :

        mainWindow(the_mainWindow),
        objectManager(the_objectManager),
        state(the_state),
        gui(the_gui)
{

}

void InterfaceManager::makeInterface() {
    switch (*state) {
        case GAME_STATE_CREATE_MATCH:
        {
            drawCreatingMatch();
            break;
        }
        case GAME_STATE_MATCH:
        {
            drawMatchInterface();
        }
        case GAME_STATE_MATCH_PAUSE:
        {
            drawMatchPauseWindow();
            break;
        }
        case GAME_STATE_MAIN_MENU:
        {
            drawMainMenu();
        };
        case GAME_STATE_ENTER_NAME:
        {
            drawEnterNickScreen();
        }
        case GAME_STATE_CHOOSE_MAP:
        {
            drawChooseMapScreen();
            break;
        }
        case GAME_STATE_ERROR:
        {
            drawErrorScreen();
            std::cout << errString;
            assert(0);
        }
        default:
        {
//            std::cout << "Interface manager unknown error at interface switch-case: " << *state << "\n";
            break;
        }
    }
}

void InterfaceManager::drawChooseMapScreen() {
    if (widgets[WIDGETS_CHOOSE_MAP]) {
        ///@todo load choose map widget
    }
}


void InterfaceManager::drawMainMenu() {
    if (!widgets[WIDGETS_MAIN_MENU]) {
        ///@todo load main menu widgets
        try {
            auto picture = tgui::Picture::create({"images/forest.svg", {0, 0, 1000, 700}}); //Failed to create texture, invalid size (0x0)
            picture->setSize({"100%", "100%"});
            gui.add(picture);

            auto singleButton = tgui::Button::create("Singleplayer");
            singleButton->setSize({"50%", "16.67%"});
            singleButton->setPosition({"25%", "10%"});
            singleButton->setTextSize(0);
            singleButton->connect("pressed", &InterfaceManager::signalHandler1, this);

            gui.add(singleButton);

            auto fictButton = tgui::Button::create();
            fictButton->setSize(240,160);
            fictButton->setPosition({"21%", "23%"});
            fictButton->setVisible(false);
            gui.add(fictButton);

            auto multiButton = tgui::Button::create("Multiplayer");
            multiButton->setSize({"50%", "16.67%"});
            multiButton->setPosition({"25%", "40%"});
            multiButton->setTextSize(0);

            multiButton->connect("pressed", &InterfaceManager::signalHandler2, this);
            gui.add(multiButton);

            auto quitButton = tgui::Button::create("Exit");
            quitButton->setSize({"50%", "16.67%"});
            quitButton->setPosition({"25%", "70%"});
            quitButton->setTextSize(0);

            quitButton->connect("pressed", &InterfaceManager::signalHandler3, this);
            quitButton->connect("pressed", [&](){ mainWindow.close(); });
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

            auto editBoxUsername = tgui::EditBox::create();
            editBoxUsername->setSize({"66.67%", "12.5%"});
            editBoxUsername->setPosition({"16.67%", "16.67%"});
            editBoxUsername->setDefaultText("Username");
            editBoxUsername->setTextSize(0);
            loginWindow->add(editBoxUsername);

            auto editBoxPassword = tgui::EditBox::copy(editBoxUsername);
            editBoxPassword->setPosition({"16.67%", "41.6%"});
            editBoxPassword->setPasswordCharacter('*');
            editBoxPassword->setDefaultText("Password");
            editBoxPassword->setTextSize(0);
            loginWindow->add(editBoxPassword);

            auto button = tgui::Button::create("Login");
            button->setSize({"50%", "16.67%"});
            button->setPosition({"25%", "70%"});
            button->setTextSize(0);
            loginWindow->add(button);

            button->connect("pressed", &InterfaceManager::login, editBoxUsername, editBoxPassword);
            button->connect("pressed", [&](){ loginWindow->setVisible(false); });

            multiButton->connect("pressed", [&](){ loginWindow->setVisible(true); });

            widgets[WIDGETS_MAIN_MENU] = true;
        }
        catch (const tgui::Exception& e)
        {
            std::cerr << "Failed to load TGUI widgets: " << e.what() << std::endl;
            assert(0);
        }

    }
}


void InterfaceManager::drawEnterNickScreen() {
    if (!widgets[WIDGETS_ENTER_NAME]) {
        ///@todo load enter name widget
    }
}

void InterfaceManager::drawErrorScreen() {
    ///@todo ...
}

void InterfaceManager::drawMatchInterface() {
    ///@todo ...
}


void InterfaceManager::setMapName(const std::string &the_mapName) {
    InterfaceManager::mapName = the_mapName;
}

void InterfaceManager::drawMatchPauseWindow() {
    ///@todo ...
}

void InterfaceManager::drawCreatingMatch() {
    if (!widgets[WIDGETS_CREATING_MATCH]) {
        ///@todo load creating match widgets
    }
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

void InterfaceManager::login(const tgui::EditBox::Ptr &username, tgui::EditBox::Ptr password) {
    std::cout << "Username: " << username->getText().toAnsiString() << std::endl;
    std::cout << "Password: " << password->getText().toAnsiString() << std::endl;
}
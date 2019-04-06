//
// Created by Кежик Кызыл-оол on 2019-02-26.
//

#include <iostream>
#include "InterfaceManager.hpp"

void login(tgui::EditBox::Ptr username, tgui::EditBox::Ptr password)
{
    std::cout << "Username: " << username->getText().toAnsiString() << std::endl;
    std::cout << "Password: " << password->getText().toAnsiString() << std::endl;
}

void loadWidgets( tgui::Gui& gui )
{
    // Create the background image
    // The picture is of type tgui::Picture::Ptr which is actually just a typedef for std::shared_widget<Picture>
    // The picture will fit the entire window and will scale with it
    auto picture = tgui::Picture::create();
    picture->setSize({"100%", "100%"});
    gui.add(picture);

    // Create the username edit box
    // Similar to the picture, we set a relative position and size
    // In case it isn't obvious, the default text is the text that is displayed when the edit box is empty
    auto editBoxUsername = tgui::EditBox::create();
    editBoxUsername->setSize({"66.67%", "12.5%"});
    editBoxUsername->setPosition({"16.67%", "16.67%"});
    editBoxUsername->setDefaultText("Username");
    gui.add(editBoxUsername);

    // Create the password edit box
    // We copy the previous edit box here and keep the same size
    auto editBoxPassword = tgui::EditBox::copy(editBoxUsername);
    editBoxPassword->setPosition({"16.67%", "41.6%"});
    editBoxPassword->setPasswordCharacter('*');
    editBoxPassword->setDefaultText("Password");
    gui.add(editBoxPassword);

    // Create the login button
    auto button = tgui::Button::create("Login");
    button->setSize({"50%", "16.67%"});
    button->setPosition({"25%", "70%"});
    gui.add(button);

    // Call the login function when the button is pressed and pass the edit boxes that we created as parameters
    button->connect("pressed", login, editBoxUsername, editBoxPassword);
}


InterfaceManager::InterfaceManager(sf::RenderWindow &the_mainWindow, ObjectManager *the_objectManager,
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
        case GAME_STATE_MATCH:
        {
            drawMatchInterface();
            break;
        }
        case GAME_STATE_MAIN_MENU:
        {
            drawMainMenu();
            break;
        };
        case GAME_STATE_ENTER_NAME:
        {
            drawEnterNameScreen();
            break;
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
            break;
        }
        case GAME_STATE_MATCH_PAUSE:
        {
            drawMatchPauseWindow();
            break;
        }
        case GAME_STATE_CREATE_MATCH:
        {
            break;
        }
        default:
        {
            std::cout << "Interface manager unknown error at interface switch-case: " << *state << "\n";
            break;
        }
    }
}

void InterfaceManager::drawChooseMapScreen() {
    ///@todo ...
}

void InterfaceManager::drawMainMenu() {
    try
    {
        loadWidgets(gui);
    }
    catch (const tgui::Exception& e)
    {
        std::cerr << "Failed to load TGUI widgets: " << e.what() << std::endl;
    }

}


void InterfaceManager::drawEnterNameScreen() {
    ///@todo ...
}



void InterfaceManager::drawErrorScreen() {
    ///@todo ...
}

void InterfaceManager::drawMatchInterface() {
    ///@todo ...
}


void InterfaceManager::setMapName(const std::string &mapName) {
    InterfaceManager::mapName = mapName;
}

void InterfaceManager::drawMatchPauseWindow() {
    ///@todo ...
}
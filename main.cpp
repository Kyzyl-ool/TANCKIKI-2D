#include <iostream>
#include "sources/GameManager.hpp"
#include <SFML/Graphics.hpp>
#include "sources/windowConfig.hpp"
#include <TGUI/TGUI.hpp>


int main() {
    sf::RenderWindow mainWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_NAME);
    tgui::Gui gui(mainWindow);
    sf::Event event{};
    GameManager* Game = new GameManager(mainWindow, gui, event);
    Game->runGame();
    return 0;
}
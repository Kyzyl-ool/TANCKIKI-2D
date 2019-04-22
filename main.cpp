#include <iostream>
#include "sources/GameManager.hpp"
#include <SFML/Graphics.hpp>
#include "sources/windowConfig.hpp"
#include <TGUI/TGUI.hpp>


int main() {
    sf::RenderWindow mainWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_NAME);
    mainWindow.setFramerateLimit(60);
    tgui::Gui gui(mainWindow);
    sf::Event event{};
    NetworkManager networkManager("95.163.180.31", 54000);
    auto* Game = new GameManager(mainWindow, gui, event, networkManager);
    Game->runGame();
    delete Game;
    return 0;
}
#include <iostream>
#include "sources/GameManager.hpp"
#include <SFML/Graphics.hpp>
#include "sources/windowConfig.hpp"
#include <TGUI/TGUI.hpp>


int main() {
    sf::RenderWindow mainWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_NAME);
    mainWindow.setFramerateLimit(60);
    sf::View view;
    view.reset(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));//размер "вида" камеры при создании объекта вида камеры
    tgui::Gui gui(mainWindow);
    sf::Event event{};
//    NetworkManager networkManager("95.163.180.31", 54000);
    NetworkManager networkManager("127.0.0.1", 54000);
    GameManager* Game = new GameManager(mainWindow, gui, event, networkManager, view);
    Game->runGame();
    delete Game;
    return 0;
}
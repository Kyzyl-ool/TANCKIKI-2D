//
// Created by Кежик Кызыл-оол on 2019-02-26.
//

#include "GraphicsManager.hpp"
#include "blocks.hpp"

void GraphicsManager::drawGameObjects() {
    for (const auto &item : objectManager->getObjects()) {
        item->draw(window);
    }
}

GraphicsManager::GraphicsManager(ObjectManager *theObjectManager, block_t *blocks, unsigned int amount_of_blocks_y,
                                 unsigned int amount_of_blocks_x, sf::RenderWindow *the_window) {
    window = the_window;
    objectManager = theObjectManager;
}

sf::RenderWindow* GraphicsManager::getWindow() {
    return window;
}

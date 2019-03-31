//
// Created by Кежик Кызыл-оол on 2019-02-26.
//

#include <iostream>
#include "PhysicsManager.hpp"

PhysicsManager::PhysicsManager(ObjectManager *theObjectManager) {
    objectManager = theObjectManager;
}

void PhysicsManager::updateGameObjects() {
    for (const auto &object1 : objectManager->getObjects()) {
        for (const auto &object2 : objectManager->getObjects()) {
            if (object1 != object2 && object1->collideCheck(object2)) {
                std::cout << "MUHAHA\n";
            }
        }
        object1->update();
    }
}

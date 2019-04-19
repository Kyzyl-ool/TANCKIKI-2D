//
// Created by Кежик Кызыл-оол on 2019-02-26.
//

#include <iostream>
#include "PhysicsManager.hpp"
#include "Tank.hpp"
#include <time.h>


PhysicsManager::PhysicsManager(ObjectManager *theObjectManager) {
    objectManager = theObjectManager;
}

void PhysicsManager::updateGameObjects(Match *match) {
    sf::Clock clock;
    float time = clock.getElapsedTime().asMicroseconds();
    clock.restart();
    time = time*KTIME/60;

    for (const auto &object1 : objectManager->getObjects()) {
        object1->update(time);
        for (const auto &object2 : objectManager->getObjects()) {
            if(object1 == object2) break;
            if (object1 != nullptr && object1->isAlive() && object2 != nullptr && object2->isAlive() && object1->collideCheck(object2)) {
                object1->collideResponse(object2, time);
                object2->collideResponse(object1, time);
            }

        }

        if(object1->collideCheck(match)) {
            object1->collideResponse(match, time);
        }
    }
}

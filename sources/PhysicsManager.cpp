//
// Created by Кежик Кызыл-оол on 2019-02-26.
//

#include <iostream>
#include "PhysicsManager.hpp"


PhysicsManager::PhysicsManager(ObjectManager *theObjectManager) {
    objectManager = theObjectManager;
}

void PhysicsManager::updateGameObjects(Match *match) {
    for (const auto &object1 : objectManager->getObjects()) {
        for (const auto &object2 : objectManager->getObjects()) {
            if(object1 == object2) break;
            if (object1 != nullptr && object1->isAlive() && object2 != nullptr && object2->isAlive() && object1->collideCheck(object2)) {
                object1->collideResponse(object2);
                object2->collideResponse(object1);
                std::cout << "MUHAHA\n";
            }
        }
        //std::vector<int> vec;
        //if(object1->isAlive())
             //vec=object1->collideCheck(match);
        //if(!vec.empty()) {
            //std::cout << vec.front()<< " ";
            //object1->collideResponse(match, vec);
        //}

        object1->update();
    }
}

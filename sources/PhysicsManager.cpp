//
// Created by Кежик Кызыл-оол on 2019-02-26.
//

#include <iostream>
#include "PhysicsManager.hpp"
#include "Tank.hpp"
#include <time.h>
#include "Ammunition.hpp"
#include "Match.hpp"


PhysicsManager::PhysicsManager(ObjectManager *theObjectManager) {
    objectManager = theObjectManager;
}

void PhysicsManager::updateGameObjects(Match *match, float time) {
    for (const auto &object1 : objectManager->getObjects()) {
        if (object1 != nullptr && object1->isAlive()) {
            object1->update(time);

            if(object1->getType() == TANK && (object1->getX() < MAP_WIDTH/(match->getAmountBlocksX())*(match->getDeathTLine()+2)
            || object1->getX() > MAP_WIDTH/match->getAmountBlocksX()*(match->getAmountBlocksX()-match->getDeathTLine()-2)
            || object1->getY() < MAP_HEIGHT/match->getAmountBlocksY()*(match->getDeathTLine()+2)
            || object1->getY() > MAP_HEIGHT/match->getAmountBlocksY()*(match->getAmountBlocksY()-match->getDeathTLine()-2))) {
                ((Tank*)object1)->setHealth(((Tank*)object1)->getHealth()-DAMAGE_OF_DEATHTIME);
            }

            for (const auto &object2 : objectManager->getObjects()) {
                if (object1 == object2) break;
                if (object2 != nullptr && object2->isAlive() && object1->collideCheck(object2)) {
                    object1->collideResponse(object2, time);
                    object2->collideResponse(object1, time);
                }
            }
            if(object1->getType() == TANK && !object1->isAlive()) {
                Ammunition *amm = new Ammunition(((Tank*)object1)->getAmmun()/((Tank*)object1)->getCountAmmun());
                amm->setPosition(object1->getX(), object1->getY());
                objectManager->addGameObject(amm);
            }

            if (object1->collideCheck(match)) {
                object1->collideResponse(match, time);
            }
        }
    }
}


//
// Created by Apxapa on 26.04.2019.
//

#include "Repair.hpp"
#include "Tank.hpp"

int Repair::getHealth() {
    return health;
}

void Repair::collideResponse(GameObject *obj, float time) {
    if(obj->getType() == TANK) {
        alive = false;
    }
}

Repair::Repair(int health_) : GameObject::GameObject() {
    type = REPAIR;
    setTexture("images/ammun.png");
    setSprite(242,374,110,140);
    setSizeSprite(40,50);
    health = health_;
}

void Repair::draw(sf::RenderWindow &window) {
    if(isAlive()) {
        window.draw(sprite);
    }
}
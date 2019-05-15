//
// Created by Apxapa on 26.04.2019.
//

#include "Ammunition.hpp"



void Ammunition::setCount(int c) {
    count = c;
}

int Ammunition::getCount() {
    return count;
}

void Ammunition::collideResponse(GameObject *obj, float time) {
    if(obj->getType() == TANK) {
        alive = false;
    }
}

Ammunition::Ammunition(int c) : GameObject::GameObject() {
    type = AMMUN;
    setTexture("images/ammun.png");
    setSprite(100,374,110,140);
    setSizeSprite(40,50);
    count = c;
}

void Ammunition::draw(sf::RenderWindow &window) {
    if(isAlive()) {
        window.draw(sprite);
    }
}

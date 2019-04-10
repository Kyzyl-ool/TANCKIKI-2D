//
// Created by Apxapa on 31.03.2019.
//

#include "Bullet.hpp"
#include <cmath>

Bullet::Bullet() : GameObject::GameObject() {
    type=BULLET;
}

void Bullet::draw(sf::RenderWindow &window) {
    if(alive)
    window.draw(Bullet::sprite);
}


void Bullet::collideResponse(GameObject *obj, float time) {
    if(obj->getType()==TANK && obj->getObjectId() != ownerId) {
        alive = false;
    }
}

void Bullet::update(float time) {
    setPosition(x+speed*cosf(getRotation()/180*M_PI)*time,y+speed*sinf(getRotation()/180*M_PI)*time);
}

int Bullet::getPower() {
    return power;
}

void Bullet::setPower(int pow) {
    power=pow;
}

void Bullet::collideResponse(Match *match, float time) {
    setAlive(false);
}


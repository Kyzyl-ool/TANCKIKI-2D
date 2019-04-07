//
// Created by Apxapa on 31.03.2019.
//

#include "Bullet.hpp"

Bullet::Bullet() : GameObject::GameObject() {
    type=BULLET;
}

void Bullet::draw(sf::RenderWindow &window) {
    if(alive)
    window.draw(Bullet::sprite);
}


void Bullet::collideResponse(GameObject *obj) {
    if(obj->getType()==TANK && obj->getObjectId() != ownerId) {
        alive = false;
    }
}

void Bullet::update() {
    setPosition(x+speedX*TIME,y+speedY*TIME);
}

int Bullet::getPower() {
    return power;
}

void Bullet::setPower(int pow) {
    power=pow;
}

//void Bullet::collideResponse(Match *match, std::vector<int> vec) {
//    setAlive(false);
//}


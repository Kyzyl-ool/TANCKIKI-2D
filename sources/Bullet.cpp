//
// Created by Apxapa on 31.03.2019.
//

#include "Bullet.hpp"
#include <cmath>

Bullet::Bullet() : GameObject::GameObject() {
    type=BULLET;
}

Bullet::Bullet(Bullet_t typeBullet) : GameObject::GameObject() {
    type=BULLET;
    if(typeBullet==LOWSHOT) {
        setSpeed(SPEED_OF_LOW_BULLET);
        setTexture("images/bullet_1.png");
        setSprite(20,13,10,8);
        setSizeSprite(13, 10);
        setPower(DAMAGE_OF_LOWSHOT);
    }
    if(typeBullet==MIDDLESHOT) {
        setSpeed(SPEED_OF_MIDDLE_BULLET);
        setTexture("images/bullet_1.png");
        setSprite(39,222,20,11);
        setSizeSprite(18, 10);
        setPower(DAMAGE_OF_MIDDLESHOT);
    }
    if(typeBullet==POWERFULLSHOT) {
        setSpeed(SPEED_OF_POWERFULLSHOT);
        setTexture("images/bullet_1.png");
        setSprite(279,214,15,12);
        setSizeSprite(25, 20);
        setPower(DAMAGE_OF_POWERFULLSHOT);
    }
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


//
// Created by Apxapa on 30.03.2019.
//

#include "Tank.hpp"
#include <cmath>



Tank::Tank() : GameObject::GameObject() {
    Tank::type=TANK;
}


int Tank::getHealth() {
    return Tank::health;
}

void Tank::setHealth(int health) {
    Tank::health=health;
}

void Tank::update() {
    setPosition(x+speedX*TIME,y+speedY*TIME);
}

void Tank::draw(sf::RenderWindow* window) {
    if(alive)
    window->draw(Tank::sprite);
    else {
        sf::Sprite spr;
        spr.setTexture(texture);
        spr.setPosition(x,y);
        spr.setTextureRect(sf::IntRect(288,96,16,16));
        spr.setOrigin(16/2,16/2);
        window->draw(spr);
    }
}


void Tank::collideResponse(GameObject *obj) {
    if(obj->getType()==TANK) {
        alive=false;
    }
}

GameObject * Tank::shot(Bullet_t BULLET) {
    Bullet *bul;
    bul = new Bullet;
    float angle= getRotation()/ 2 / (float) M_PI;
    bul->setOwnerId(gameObjectId);
    if(BULLET==LOWSHOT) {
        bul->setPosition(x + (sizeX + X_OF_LOW_BULLET)/2 * cosf(angle),
                         y - (sizeY + Y_OF_LOW_BULLET)/2 * sinf(angle));
        bul->setSpeed(SPEED_OF_LOW_BULLET * cosf(angle),
                      SPEED_OF_LOW_BULLET * sinf(angle));
        bul->setTexture("images/bullet_1.png");
        bul->setSprite(20,13,10,8);
        bul->setSizeSprite(X_OF_LOW_BULLET, Y_OF_LOW_BULLET);
        bul->setSizeObj(X_OF_LOW_BULLET,Y_OF_LOW_BULLET);
    }
    bul->setAlive(true);
    bul->setRotation(angle);
    return bul;
}





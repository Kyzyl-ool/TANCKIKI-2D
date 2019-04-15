//
// Created by Apxapa on 30.03.2019.
//

#include "Tank.hpp"
#include <cmath>

#include <iostream>


Tank::Tank(float health) : GameObject::GameObject(), health(health) {
    Tank::type=TANK;
}


float Tank::getHealth() {
    return Tank::health;
}

void Tank::setHealth(float health_) {
    Tank::health=health_;
}

void Tank::update(float time) {
    setPosition(x+speed*cosf(getRotation()/180*M_PI)*time,y+speed*sinf(getRotation()/180*M_PI)*time);
    spriteTower.setPosition(x+speed*cosf(getRotation()/180*M_PI)*time,y+speed*sinf(getRotation()/180*M_PI)*time);
    setRotation(getRotation()+speedAngle*time);
    spriteTower.setRotation(spriteTower.getRotation()+speedTower*time);
    if(health < 1) setAlive(false);
}


void Tank::draw(sf::RenderWindow &window) {
    if(isAlive())
    window.draw(Tank::sprite);
    window.draw(Tank::spriteTower);
}


void Tank::collideResponse(GameObject *obj, float time) {
    if(obj->getType()==TANK) {
        health = health-0.04;
        setPosition(x-speed*cosf(getRotation()/180*M_PI)*time,y-speed*sinf(getRotation()/180*M_PI)*time);
        setRotation(getRotation()-speedAngle*time);
    }
    if(obj->getType()==BULLET && obj->getOwnerId() != gameObjectId) {
        health = health - ((Bullet*)obj)->getPower();
    }
}

void Tank::collideResponse(Match *match, float time) {
    health = health-0.02;
    setPosition(x-speed*cosf(getRotation()/180*M_PI)*time,y-speed*sinf(getRotation()/180*M_PI)*time);
}

GameObject * Tank::shot(Bullet_t BULLET) {
    Bullet *bul;
    bul = new Bullet;
    float angle= getRotation()/ 180* M_PI;
    bul->setOwnerId(gameObjectId);
    if(BULLET==LOWSHOT) {
        bul->setPosition(x + (sizeX + X_OF_LOW_BULLET)/2 * cosf(angle),
                         y + (sizeY + Y_OF_LOW_BULLET)/2 * sinf(angle));
        bul->setSpeed(SPEED_OF_LOW_BULLET);
        bul->setTexture("images/bullet_1.png");
        bul->setSprite(20,13,10,8);
        bul->setSizeSprite(X_OF_LOW_BULLET, Y_OF_LOW_BULLET);
        bul->setPower(10);
    }
    bul->setAlive(true);
    bul->setRotation(getRotation());
    return bul;
}

float Tank::getSpeedTower() {
    return speedTower;
}

void Tank::setSpeedTower(float angleSpeed) {
    speedTower = angleSpeed;
}

void Tank::setSpriteTower(int X, int Y, int sizeX_, int sizeY_) {
    spriteTower.setTexture(texture);
    spriteTower.setTextureRect(sf::IntRect(X,Y,sizeX_,sizeY_));
    if(type == TANK) {
        spriteTower.setOrigin(sizeX_ *24/80, sizeY_ / 2);
    }
    spriteTower.setPosition(x+sizeX*24/70,y+sizeY*1/2);
}

void Tank::setTextureTower(const char* address) {
    sf::Image image;
    image.loadFromFile(address);
    image.createMaskFromColor(sf::Color::White);
    textureTower.loadFromImage(image);
}





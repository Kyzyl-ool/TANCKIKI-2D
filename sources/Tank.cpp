//
// Created by Apxapa on 30.03.2019.
//

#include "Tank.hpp"
#include <cmath>

#include <iostream>


Tank::Tank(float health, const std::string& the_name) : GameObject::GameObject(), health(health), maxHealth(health) {
    Tank::type=TANK;
    if(the_name=="ChickenKiller") {
        setTexture("images/Htanks.png");
        setSprite(297,108,95,53);
        setSizeSprite(90,50);
        setTextureTower("images/Htanks.png");
        setSpriteTower(300,68,86,40);
        setAlive(true);
    }
}

void Tank::setTextBoom(const char* address) {
    sf::Image image;
    image.loadFromFile(address);
    image.createMaskFromColor(sf::Color::White);
    textBoom.loadFromImage(image);
}

void setSprBoom(int X, int Y, int sizeX, int sizeY) {

}


float Tank::getHealth() {
    return Tank::health;
}

void Tank::setHealth(float health_) {
    Tank::health=health_;
}

void Tank::update(float time) {
    setPosition(x+speed*cosf(getRotation()/180*M_PI)*time,y+speed*sinf(getRotation()/180*M_PI)*time);
    spriteTower.setPosition(x,y);
    setRotation(getRotation()+speedAngle*time);
    spriteTower.setRotation(spriteTower.getRotation()+speedTower*time);
    if(health <= 0) setAlive(false);
}


void Tank::draw(sf::RenderWindow &window) {
    if(isAlive()) {
        window.draw(Tank::sprite);
        window.draw(Tank::spriteTower);
    }
}


void Tank::collideResponse(GameObject *obj, float time) {
    if(obj->getType()==TANK) {
        float kk = 1.00;
        health = health-0;
        setPosition(x-kk*speed*cosf(getRotation()/180*M_PI)*time,y-kk*speed*sinf(getRotation()/180*M_PI)*time);
        setRotation(getRotation()-kk*speedAngle*time);
        spriteTower.setPosition(x,y);
    }
    if(obj->getType()==BULLET && obj->getOwnerId() != gameObjectId) {
        health = health - ((Bullet*)obj)->getPower();
    }
}

void Tank::collideResponse(Match *match, float time) {
    float kk = 1.00;
    health = health-0.002;
    setPosition(x-kk*speed*cosf(getRotation()/180*M_PI)*time,y-kk*speed*sinf(getRotation()/180*M_PI)*time);
    setRotation(getRotation()-kk*speedAngle*time);
    spriteTower.setPosition(x,y);
}

GameObject * Tank::shot(Bullet_t BULLET) {
    Bullet *bul;
    bul = new Bullet;
    float angle= spriteTower.getRotation()/ 180* M_PI;
    bul->setOwnerId(gameObjectId);
    if(BULLET==LOWSHOT) {
        bul->setPosition(x + sizeX*0.61 * cosf(angle), y + sizeX*0.61 * sinf(angle));
        bul->setSpeed(SPEED_OF_LOW_BULLET);
        bul->setTexture("images/bullet_1.png");
        bul->setSprite(20,13,10,8);
        bul->setSizeSprite(20, 12);
        bul->setPower(10);
    }
    bul->setAlive(true);
    bul->setRotation(spriteTower.getRotation());
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
        spriteTower.setOrigin(sizeX_ *20/90, sizeY_ * 25/50);
    }
    spriteTower.setScale(0.9,0.9);
}

void Tank::setTextureTower(const char* address) {
    sf::Image image;
    image.loadFromFile(address);
    image.createMaskFromColor(sf::Color::White);
    textureTower.loadFromImage(image);
}

int Tank::checkOrient(float X, float Y) {
    return lround((Y-y)*cosf(spriteTower.getRotation()/180*M_PI) - (X-x)*sinf(spriteTower.getRotation()/180*M_PI)+0.5);
}

float Tank::getMaxHealth() const {
    return maxHealth;
}

const std::string &Tank::getName() const {
    return name;
}




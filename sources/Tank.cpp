//
// Created by Apxapa on 30.03.2019.
//

#include "Tank.hpp"
#include <cmath>

#include <iostream>


Tank::Tank(float health, const std::string &the_player_name, const std::string color)
        : GameObject::GameObject(), health(health), maxHealth(health) {
    Tank::type=TANK;
    speedTower =0;
    playerName="ChickenKiller";
    setTexture("images/Htanks.png");
    setTextureTower("images/Htanks.png");
    if(color == "green1") {
        setSprite(297,108,95,53);
        setSpriteTower(300,68,86,40);
    }
    if(color == "yellow1") {
        setSprite(295,214,95,53);
        setSpriteTower(298,174,86,40);
    }
    if(color == "yellow2") {
        setSprite(297,315,95,53);
        setSpriteTower(300,275,86,40);
    }
    if(color == "yellow3") {
        setSprite(295,421,95,53);
        setSpriteTower(298,381,86,40);
    }
    if(color == "purple1") {
        setSprite(289,525,95,53);
        setSpriteTower(292,485,86,40);
    }
    if(color == "purple2") {
        setSprite(291,636,95,53);
        setSpriteTower(294,596,86,40);
    }
    if(color == "purple3") {
        setSprite(293,741,95,53);
        setSpriteTower(296,701,86,40);
    }
    if(color == "violet1") {
        setSprite(196,108,95,53);
        setSpriteTower(199,68,86,40);
    }
    if(color == "violet2") {
        setSprite(196,213,95,53);
        setSpriteTower(199,173,86,40);
    }
    if(color == "violet3") {
        setSprite(195,319,95,53);
        setSpriteTower(198,279,86,40);
    }
    if(color == "violet4") {
        setSprite(195,427,95,53);
        setSpriteTower(198,387,86,40);
    }

    if(color == "blue1") {
        setSprite(398,109,95,53);
        setSpriteTower(401,69,86,40);
    }
    if(color == "blue2") {
        setSprite(397,214,95,53);
        setSpriteTower(400,174,86,40);
    }
    if(color == "blue3") {
        setSprite(397,316,95,53);
        setSpriteTower(400,276,86,40);
    }
    if(color == "blue4") {
        setSprite(393,422,95,53);
        setSpriteTower(396,382,86,40);
    }
    if(color == "green2") {
        setSprite(390,524,95,53);
        setSpriteTower(393,484,86,40);
    }
    if(color == "green3") {
        setSprite(393,636,95,53);
        setSpriteTower(396,596,86,40);
    }
    if(color == "green4") {
        setSprite(397,739,95,53);
        setSpriteTower(400,699,86,40);
    }
    setSizeSprite(90,50);
    setAlive(true);
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
    setRotation(getRotation()+speedAngle*time);
    spriteTower.setPosition(x,y);
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
        health = health-0.03*time;
        setRotation(getRotation()-speedAngle*time);
        setPosition(x-speed*cosf(getRotation()/180*M_PI)*time,y-speed*sinf(getRotation()/180*M_PI)*time);
        spriteTower.setPosition(x,y);
    }
    if(obj->getType()==BULLET && obj->getOwnerId() != gameObjectId) {
        health = health - ((Bullet*)obj)->getPower();
    }
}

void Tank::collideResponse(Match *match, float time) {
    health = health-0.03*time;
    setRotation(getRotation()-speedAngle*time);
    setPosition(x-speed*cosf(getRotation()/180*M_PI)*time,y-speed*sinf(getRotation()/180*M_PI)*time);
    spriteTower.setPosition(x,y);
}

GameObject * Tank::shot() {
    Bullet *bul;
    bul = new Bullet(bulType);
    float angle= spriteTower.getRotation()/ 180* M_PI;
    bul->setOwnerId(gameObjectId);
    if(bulType==LOWSHOT) {
        bul->setPosition(x + sizeX*0.70 * cosf(angle), y + sizeX*0.70 * sinf(angle));
    }
    if(bulType==MIDDLESHOT) {
        bul->setPosition(x + sizeX*0.72 * cosf(angle), y + sizeX*0.72 * sinf(angle));
    }
    if(bulType==POWERFULLSHOT) {
        bul->setPosition(x + sizeX*0.75 * cosf(angle), y + sizeX*0.75 * sinf(angle));
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
        spriteTower.setOrigin(sizeX_ *0.222, sizeY_ * 0.5);
    }
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
    return playerName;
}

Bullet_t Tank::getTypeBullet() {
    return bulType;
}

void Tank::setTypeBullet(Bullet_t TypeBullet) {
    bulType = TypeBullet;
}





#include <utility>

//
// Created by Apxapa on 30.03.2019.
//

#include "Tank.hpp"
#include "Ammunition.hpp"
#include "Repair.hpp"
#include "Match.hpp"
#include <cmath>

#include <iostream>



Tank::Tank(float health, const std::string &the_player_name, const std::string &color)
        : GameObject::GameObject(), health(health), maxHealth(health) {
    Tank::type=TANK;
    lastEnemy = -1;
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
    setSizeSprite(126,70);
    spriteTower.setScale(1.18,1.18);
}

void Tank::setTextBoom(const char* address) {
    sf::Image image;
    image.loadFromFile(address);
    image.createMaskFromColor(sf::Color::White);
    textBoom.loadFromImage(image);
}



float Tank::getHealth() {
    return Tank::health;
}

void Tank::setHealth(float health_) {
    Tank::health=health_;
}

float Tank::getViewCoordX(Match *match) {
    return x - (match->getGraphicsManager()->getView().getCenter().x-WINDOW_WIDTH/2);
}


float Tank::getViewCoordY(Match *match) {
    return y - (match->getGraphicsManager()->getView().getCenter().y-WINDOW_HEIGHT/2);
}

void Tank::update(float time) {
    setPosition(x+speed*cosf(getRotation()/180*M_PI)*time,y+speed*sinf(getRotation()/180*M_PI)*time);
    setRotation(getRotation()+speedAngle*time);
    spriteTower.setPosition(x,y);
    spriteTower.setRotation(spriteTower.getRotation()+speedTower*time);
    updateRecharge(time);
    if(health <= 0) {
        setAlive(false);
    }
}

int Tank::getAmmun() {
    return ammunition;
}


void Tank::draw(sf::RenderWindow &window) {
    if(isAlive()) {
        window.draw(Tank::sprite);
        window.draw(Tank::spriteTower);
    }
}


void Tank::collideResponse(GameObject *obj, float time) {
    if(obj->getType()==REPAIR) {
        health += ((Repair*)obj)->getHealth();
        if(health>maxHealth) health = maxHealth;
    }
    if(obj->getType()==AMMUN) {
        if(getTypeBullet() == LOWSHOT)
            ammunition += ((Ammunition*)obj)->getCount()*COEF_LOWSHOT;
        if(getTypeBullet() == MIDDLESHOT)
            ammunition += ((Ammunition*)obj)->getCount()*COEF_MIDDLESHOT;
        if(getTypeBullet() == POWERFULLSHOT)
            ammunition += ((Ammunition*)obj)->getCount()*COEF_POWERFULLSHOT;
    }
    if(obj->getType()==TANK) {
        health = health-DAMAGE_OF_COLLISION*time;
        setRotation(getRotation()-speedAngle*time);
        setPosition(x-speed*cosf(getRotation()/180*M_PI)*time,y-speed*sinf(getRotation()/180*M_PI)*time);
        spriteTower.setPosition(x,y);
    }
    if(obj->getType()==BULLET && obj->getOwnerId() != gameObjectId) {
        health = health - ((Bullet*)obj)->getPower();
        lastEnemy = obj->getOwnerId();
        if(health <= 0) {
            setAlive(false);
        }
    }
}

int Tank::getLastEnemy() {
    return lastEnemy;
}

void Tank::collideResponse(Match *match, float time) {
    health = health-DAMAGE_OF_COLLISION*time;
    setRotation(getRotation()-speedAngle*time);
    setPosition(x-speed*cosf(getRotation()/180*M_PI)*time,y-speed*sinf(getRotation()/180*M_PI)*time);
    spriteTower.setPosition(x,y);
}

GameObject * Tank::shot() {
    if(getRecharge()>0 || ammunition == 0) return nullptr;

    Bullet *bul;
    bul = new Bullet(bulType);
    float angle= spriteTower.getRotation()/ 180* M_PI;
    bul->setOwnerId(gameObjectId);
    if(bulType==LOWSHOT) {
        bul->setPosition(x + sizeX*0.60 * cosf(angle), y + sizeX*0.60 * sinf(angle));
        setRecharge(RECHARGE_OF_LOWSHOT);
    }
    if(bulType==MIDDLESHOT) {
        bul->setPosition(x + sizeX*0.62 * cosf(angle), y + sizeX*0.62 * sinf(angle));
        setRecharge(RECHARGE_OF_MIDDLESHOT);
    }
    if(bulType==POWERFULLSHOT) {
        bul->setPosition(x + sizeX*0.67 * cosf(angle), y + sizeX*0.67 * sinf(angle));
        setRecharge(RECHARGE_OF_POWERFULLSHOT);
    }
    bul->setAlive(true);
    bul->setRotation(spriteTower.getRotation());
    ammunition = ammunition - 1;
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

float Tank::checkOrient(float X, float Y, sf::RenderWindow *window) {
    X=X*WINDOW_WIDTH/window->getSize().x;
    Y=Y*WINDOW_HEIGHT/window->getSize().y;

    float vx = WINDOW_WIDTH/2;
    float vy = WINDOW_HEIGHT/2;
    if(x<WINDOW_WIDTH/2) vx = x;
    if(x>MAP_WIDTH-WINDOW_WIDTH/2) vx = WINDOW_WIDTH - (MAP_WIDTH-x);
    if(y<WINDOW_HEIGHT/2) vy = y;
    if(y>MAP_HEIGHT-WINDOW_HEIGHT/2) vy = WINDOW_HEIGHT - (MAP_HEIGHT-y);
    float phi = spriteTower.getRotation()/180*M_PI;
    float deltaPhi = asinf(((Y-vy)*cosf(phi) - (X-vx)*sinf(phi))/sqrtf((Y-vy)*(Y-vy)+(X-vx)*(X-vx)));
    return deltaPhi;
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
    int k = 4;
    if(TypeBullet == LOWSHOT) {
        count_ammun = COEF_LOWSHOT;
    }
    if(TypeBullet == MIDDLESHOT) {
        count_ammun = COEF_MIDDLESHOT;
    }
    if(TypeBullet == POWERFULLSHOT) {
        count_ammun = COEF_POWERFULLSHOT;
    }
    ammunition = k*count_ammun;
}

int Tank::getCountAmmun() {
    return count_ammun;
}

float Tank::getRecharge() {
    return recharge;
}

void Tank::setRecharge(float recharge_) {
    recharge = recharge_;
}

void Tank::updateRecharge(float time) {
    recharge = recharge-time;
    if(recharge<0) recharge = 0;
}


float Tank::getTowerX() const {
    return towerX;
}

float Tank::getTowerY() const {
    return towerY;
}

void Tank::setTowerX(float towerX) {
    Tank::towerX = towerX;
}

void Tank::setTowerY(float towerY) {
    Tank::towerY = towerY;
}

void
Tank::setConfiguration(float iX, float iY, float ihealth, float itowerSpeed, float irecharge, float itowerX,
                       float itowerY, int iammunition, float iRotaton, float iTowerRotation, std::string name) {
    x = iX;
    y = iY;
    health = ihealth;
    speedTower = itowerSpeed;
    recharge = irecharge;
    towerX = itowerX;
    towerY = itowerY;
    ammunition = iammunition;
    setRotation(iRotaton);
    spriteTower.setRotation(iTowerRotation);
    playerName = std::move(name);
}

float Tank::getTowerRotation() {
    return spriteTower.getRotation();
}

void Tank::setPlayerName(const std::string &playerName) {
    Tank::playerName = playerName;
}




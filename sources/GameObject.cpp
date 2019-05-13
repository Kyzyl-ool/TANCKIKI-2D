#include <utility>

//
// Created by Кежик Кызыл-оол on 2019-02-26.
//

#include "GameObject.hpp"
#include "Match.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>

GameObject::GameObject() {
    GameObject::speed = 0;
    speedAngle = 0;
    alive = true;
}

void GameObject::update(float time) {

}


void GameObject::setRotation(float angle){
    GameObject::sprite.setRotation(angle);
}

float GameObject::getRotation() const{
    return sprite.getRotation();
}

float GameObject::getSizeX() const {
    return sizeX;
}

float GameObject::getSizeY() const {
    return sizeY;
}


void GameObject::setSizeSprite(float sizeX_, float sizeY_) {
    sprite.setScale(sizeX_/sizeX, sizeY_/sizeY);
    sizeX=sizeX_;
    sizeY=sizeY_;
}

GameObject::~GameObject() {

}

bool GameObject::collideCheck(GameObject *obj) {
    return Collision::CircleTest(sprite, obj->getSprite()) && Collision::BoundingBoxTest(sprite, obj->getSprite());
}

bool GameObject::collideCheck(Match *match) {
    block_t *blocks = match->getBlocks();
    float sizeBlx = ((float)MAP_WIDTH)/match->getAmountBlocksX();
    float sizeBly = ((float)MAP_HEIGHT)/match->getAmountBlocksY();

    int jj =  (int)(x - (sizeX+sizeY)/2)/sizeBlx;
    int ii = (int)(y - (sizeX+sizeY)/2)/sizeBly;
    int n = (int)(x + (sizeX+sizeY)/2)/sizeBlx;
    int m = (int)(y + (sizeX+sizeY)/2)/sizeBly;

    for (int i = ii; i < m+1; ++i) {
        for (int j = jj; j < n+1; ++j) {
            if (i * match->getAmountBlocksX() + j < match->getAmountBlocksX()*match->getAmountBlocksY() &&
            blocks[i * match->getAmountBlocksX() + j] == BL_0) {
                sf::Sprite spr;
                spr.setTextureRect(sf::IntRect(0, 0, sizeBlx, sizeBly));
                spr.setPosition((j+0.5)*sizeBlx, (i+0.5)*sizeBly);
                if(Collision::BoundingBoxTest(spr, sprite))
                    return true;
                }
            }
        }
    return false;
}


void GameObject::collideResponse(GameObject *obj, float time) {

}

void GameObject::collideResponse(Match *match, float time) {

}

float GameObject::getX() const {
    return x;
}

float GameObject::getY() const {
    return y;
}

bool GameObject::isAlive() const {
    return alive;
}

const sf::Sprite &GameObject::getSprite() const {
    return sprite;
}

const sf::Texture &GameObject::getTexture() const {
    return texture;
}


void GameObject::setAlive(bool alive_) {
    GameObject::alive = alive_;
}

void GameObject::setPosition(float X, float Y){
    GameObject::x=X;
    GameObject::y=Y;
    GameObject::sprite.setPosition(X,Y);
}


void GameObject::setSprite(sf::Sprite sprite_){

}

void GameObject::setSprite(int X, int Y, int sizeX_, int sizeY_){
    GameObject::sizeX=sizeX_;
    GameObject::sizeY=sizeY_;
    GameObject::sprite.setTexture(GameObject::texture);
    GameObject::sprite.setTextureRect(sf::IntRect(X,Y,sizeX_,sizeY_));
    if(type == TANK) {
        GameObject::sprite.setOrigin(sizeX_ *1/2, sizeY_ / 2);
    }
    else sprite.setOrigin(sizeX_ *1/2, sizeY_ / 2);
}

void GameObject::setTexture(sf::Texture texture_){
    GameObject::texture=texture_;
}

void GameObject::setTexture(const char* address) {
    sf::Image image;
    image.loadFromFile(address);
    if(type == TANK) {
        image.createMaskFromColor(sf::Color::White);
    }
    if(type == BULLET) {
        image.createMaskFromColor(sf::Color::Black);
    }
    GameObject::texture.loadFromImage(image);
}


void GameObject::setSpeed(float sp) {
    GameObject::speed = sp;
}

void GameObject::draw(sf::RenderWindow &window) {

}

float GameObject::getSpeed() const {
    return speed;
}


void GameObject::multSize(float k){
    GameObject::sizeX=k*sizeX;
    GameObject::sizeY=k*sizeY;
    GameObject::sprite.setScale(k*sprite.getScale().x, k*sprite.getScale().y);
}

gameObject_t GameObject::getType() const {
    return type;
}

int GameObject::getOwnerId() const {
    return ownerId;
}

int GameObject::getObjectId() const {
    return gameObjectId;
}

void GameObject::setObjectId(int id) {
    gameObjectId=id;
}

void GameObject::setOwnerId(int pid) {
    ownerId=pid;
}

GameObject * GameObject::shot() {

}

float GameObject::getSpeedAngle() const {
    return speedAngle;
}

void GameObject::setSpeedAngle(float spAngle) {
    speedAngle = spAngle;
}



void GameObject::rotateLeft() {
    if(type == TANK) {
        setSpeedAngle(-TANK_ANGLE_SPEED);
    }
}

void GameObject::rotateRight() {
    if(type == TANK) {
        setSpeedAngle(TANK_ANGLE_SPEED);
    }
}

void GameObject::stopRotate() {
    setSpeedAngle(0);
}

void GameObject::go() {
    if(type == TANK) {
        setSpeed(TANK_VELOCITY);
    }
}

void GameObject::stop() {
    setSpeed(0);
}

void GameObject::brake() {
    setSpeed(-TANK_VELOCITY);
}

float GameObject::getScale() {
    return scale;
}

void GameObject::setScale(float sc) {
    scale = sc;
}

void GameObject::setX(float x) {
    GameObject::x = x;
}

void GameObject::setY(float y) {
    GameObject::y = y;
}

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
    GameObject::speedX = 0;
    GameObject::speedY = 0;
    speedAngle = 0;
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

void GameObject::setSizeObj(float sizeX_, float sizeY_) {
    GameObject::sizeX=sizeX_;
    GameObject::sizeY=sizeY_;
}

void GameObject::setSizeSprite(float sizeX_, float sizeY_) {
    GameObject::sprite.setScale(sizeX_/GameObject::sizeX, sizeY_/GameObject::sizeY);
}

GameObject::~GameObject() {

}

bool GameObject::collideCheck(GameObject *obj) {
        sf::Sprite spr1 = sprite;                               /// ХОРОШИЙ РАБОЧИЙ КОСТЫЛЬ
        sf::Sprite spr2 = obj->getSprite();
        spr1.setTextureRect(sf::IntRect(0, 0, (int) sizeX, (int) sizeY));
        spr2.setTextureRect(sf::IntRect(0, 0, (int) obj->getSizeX(), (int) obj->getSizeY()));

        if (Collision::CircleTest(spr1, spr2)) {
            return Collision::BoundingBoxTest(spr1, spr2);
        }
    return false;
}

bool GameObject::collideCheck(Match *match) {
    block_t *blocks = match->getBlocks();
    int jj = (int) (x - sizeX/2)*match->getAmountBlocksX()/WINDOW_WIDTH;
    int ii = (int) (y - sizeY/2)*match->getAmountBlocksY()/WINDOW_HEIGHT;
    int n = (int) (x + sizeX/2)*match->getAmountBlocksX()/WINDOW_WIDTH;
    int m = (int) (y + sizeY/2)*match->getAmountBlocksY()/WINDOW_HEIGHT;
    std::vector<int> vec;

    for (int i = ii; i < m+1; ++i) {
        for (int j = jj; j < n+1; ++j) {
            if (i * match->getAmountBlocksX() + j < match->getAmountBlocksX()*match->getAmountBlocksY() &&
            blocks[i * match->getAmountBlocksX() + j] == BL_0) {
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
    GameObject::sprite.setOrigin(sizeX_/2,sizeY_/2);
}

void GameObject::setTexture(sf::Texture texture_){
    GameObject::texture=texture_;
}

void GameObject::setTexture(const char* address) {
    sf::Image image;
    image.loadFromFile(address);
    GameObject::texture.loadFromImage(image);
}


void GameObject::setSpeed(float spX, float spY) {
    GameObject::speedX = spX;
    GameObject::speedY = spY;
}

void GameObject::draw(sf::RenderWindow &window) {

}

float GameObject::getSpeedX() const {
    return speedX;
}

float GameObject::getSpeedY() const {
    return speedY;
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

GameObject * GameObject::shot(Bullet_t BULLET) {

}

float GameObject::getSpeedAngle() const {
    return speedAngle;
}

void GameObject::setSpeedAngle(float spAngle) {
    speedAngle = spAngle;
}

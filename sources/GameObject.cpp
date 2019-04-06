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
    GameObject::speedX=0;
    GameObject::speedY=0;
    std::cout << "GameObject created.\n";
}

void GameObject::update() {

}


void GameObject::setRotation(float angle){
    GameObject::sprite.setRotation(-angle);
}

float GameObject::getRotation() const{
    return -sprite.getRotation();
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
        spr1.setOrigin(sizeX / 2, sizeY / 2);
        spr2.setTextureRect(sf::IntRect(0, 0, (int) obj->getSizeX(), (int) obj->getSizeY()));
        spr2.setOrigin(sizeX / 2, sizeY / 2);

        if (Collision::CircleTest(spr1, spr2)) {
            return Collision::BoundingBoxTest(spr1, spr2);
        }
    return false;
}

//std::vector<int> GameObject::collideCheck(Match *match) {
//    block_t *blocks = match->getBlocks();
//    int jj = (int) (x - sizeX)/16;
//    int ii = (int) (y - sizeY)/16;
//    int n = (int) (x + sizeX )/16;
//    int m = (int) (y + sizeY )/16;
//    std::vector<int> vec;
//
//    for (int i = ii; i < m+1; ++i) {
//        for (int j = jj; j < n+1; ++j) {
//            if (blocks[i * match->getAmountBlocksX() + j] == BL_0) {
//                sf::Texture textur;
//                textur.create(16, 16);
//                sf::Sprite spr;
//                spr.setTexture(textur);
//                spr.setTextureRect(sf::IntRect(0, 0, 16, 16));
//                spr.setPosition((float)j * WINDOW_WIDTH / match->getAmountBlocksX(),
//                                (float)i * WINDOW_HEIGHT / match->getAmountBlocksY());
//
//                sf::Sprite spr1 = sprite;
//                spr1.setTextureRect(sf::IntRect(0, 0, (int) sizeX, (int) sizeY));
//                spr1.setOrigin(sizeX / 2, sizeY / 2);
//
//                if (Collision::BoundingBoxTest(spr, spr1)) vec.push_back(i * match->getAmountBlocksX() + j);
//            }
//        }
//    }
//    return vec;
//}


void GameObject::collideResponse(GameObject *obj) {

}

//void GameObject::collideResponse(Match *match, std::vector<int> vec) {
//    for(const auto place : vec) {
//        if(match->getBlocks()[place]==BL_0)
//        setAlive(false);
//    }
//}

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


void GameObject::setAlive(bool alive) {
    GameObject::alive = alive;
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

void GameObject::draw(sf::RenderWindow *window) {

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

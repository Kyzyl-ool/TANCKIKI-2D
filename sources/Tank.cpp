//
// Created by Apxapa on 30.03.2019.
//

#include "Tank.hpp"
#include <cmath>
#include "Collision.hpp"


class Point
{
public:
    float x;
    float y;
};


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


bool Tank::collideCheck(GameObject *obj) {
    if (obj->getType() == TANK) {

        sf::Sprite spr1 = sprite;                               /// ХОРОШИЙ РАБОЧИЙ КОСТЫЛЬ
        sf::Sprite spr2 = obj->getSprite();
        spr1.setTextureRect(sf::IntRect(0,0,(int)sizeX,(int)sizeY));
        spr1.setOrigin(sizeX/2,sizeY/2);
        spr2.setTextureRect(sf::IntRect(0,0,(int)obj->getSizeX(),(int)obj->getSizeY()));
        spr2.setOrigin(sizeX/2,sizeY/2);

        if (Collision::CircleTest(spr1, spr2)) {
            return Collision::BoundingBoxTest(spr1, spr2);
        }
    }
  return false;
}

void Tank::collideResponse(GameObject *obj) {
    if(obj->getType()==TANK) {
        alive=false;
    }
}





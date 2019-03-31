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
    window->draw(Tank::sprite);
}

int checkLocPointStraight(Point A, Point B, Point C){ ///A и B задают прямую, C - точка, 1 - если точка слева над прямой, 0 - если под
    if(A.x==B.x){
        return C.x < A.x;
    }
        float k=atanf((B.y-A.y)/(B.x-A.x));
        float b=A.y-k*A.x;
        return C.y > k * C.x + b;
}

bool checkLocPointSquare(Point A, Point B, Point C, Point D, Point X){ ///сначала НИЖНЯЯ левая, против часовой стрелки
    return checkLocPointStraight(A, B, X) && !checkLocPointStraight(B, C, X) && !checkLocPointStraight(C, D, X) && checkLocPointStraight(D, A, X);
}


bool Tank::collideCheck(GameObject* obj) {
    if (obj->getType() == TANK) {
        if (Collision::CircleTest(sprite, obj->getSprite())) {
            return Collision::BoundingBoxTest(sprite, obj->getSprite());
        }
    }

  return false;
}

void Tank::collideResponse(GameObject *obj) {
    if(obj->getType()==TANK) {

    }
}

float Tank::getDiam() {
    return d;
}




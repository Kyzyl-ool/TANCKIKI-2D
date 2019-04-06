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


Tank::Tank()  : GameObject::GameObject()  {
    Tank::type=TANK;
}


int Tank::getHealth() {
    return Tank::health;
}

void Tank::setHealth(int health) {
    Tank::health=health;
}

void Tank::update() {
    float dx, dy;
    int angle = (int)getRotation();
    switch (angle)
    {
        case 0: dx = speed; dy = 0; break;
        case -180: dx = -speed; dy = 0; break;
        case -90: dx = 0; dy = speed; break;
        case -270: dx = 0; dy = -speed; break;
        default: dx = 0; dy = 0; break;
    }

    setPosition(x+dx*TIME,y+dy*TIME);
}

void Tank::draw(sf::RenderWindow &window) {
    window.draw(Tank::sprite);
}

int checkLocPointStraight(Point A, Point B, Point C){ ///A и B задают прямую, C - точка, 0 - если точка слева от прямой, 1 - если справа
    float D = (C.x - A.x) * (B.y - A.y) - (C.y - A.y) * (B.x - A.x);
    if(D>0) return 4;
    else if (D==0) return 0;
    else return -1;
}

int checkLoc3PointStraight(Point A, Point B, Point C1, Point C2, Point C3){
    int res= checkLocPointStraight(A, B, C1)+ checkLocPointStraight(A, B, C2)+ checkLocPointStraight(A, B, C3);
    if(res % 4 == 0) return 1;
    else if(res<1) return -1;
    else return 0;
}

bool Tank::collideCheck(GameObject* obj) {
    if (obj->getType() == TANK) {
        if (Collision::CircleTest(sprite, obj->getSprite())) {
            return Collision::BoundingBoxTest(sprite, obj->getSprite());
        }
    }
//    if(obj->getType()==TANK) {
//        Point A[4], B[4], Q[3], R[3];
//        float d1 = sqrtf(powf(sizeX / 2, 2) + powf(sizeY / 2, 2));
//        float d2 = sqrtf(powf(obj->getSizeX() / 2, 2) + powf(obj->getSizeY() / 2, 2));
//        if (powf(d1 + d2, 2) < powf(x - obj->getX(), 2) + powf(y - obj->getY(), 2))
//            return true;
//        float cos1 = cosf(GameObject::getRotation());float sin1 = sinf(GameObject::getRotation());
//        float cos2 = cosf(obj->getRotation());float sin2 = sinf(obj->getRotation());
//
//        A[3].x = x + d1 * cos1;A[3].y = y + d1 * sin1;
//        A[2].x = x + d1 * cos1;A[2].y = y - d1 * sin1;
//        A[1].x = x - d1 * cos1;A[1].y = y + d1 * sin1;
//        A[0].x = x - d1 * cos1;A[0].y = y - d1 * sin1;
//
//        B[3].x = obj->getX() + d2 * cos2;B[3].y = obj->getY() + d2 * sin2;
//        B[2].x = obj->getX() + d2 * cos2;B[2].y = obj->getY() - d2 * sin2;
//        B[1].x = obj->getX() - d2 * cos2;B[1].y = obj->getY() + d2 * sin2;
//        B[0].x = obj->getX() - d2 * cos2;B[0].y = obj->getY() - d2 * sin2;
//
//        int T = 2 * (x > obj->getX()) + (y > obj->getY());
//
//        switch (T) {
//            case 0 :Q[0] = A[3];Q[1] = A[2];Q[2] = A[1];R[0] = B[0];R[1] = B[1];R[2] = B[2];
//            case 1 :Q[0] = A[2];Q[1] = A[3];Q[2] = A[0];R[0] = B[1];R[1] = B[0];R[2] = B[3];
//            case 2 :Q[0] = A[1];Q[1] = A[3];Q[2] = A[0];R[0] = B[2];R[1] = B[0];R[2] = B[3];
//            case 3 :Q[0] = A[0];Q[1] = A[2];Q[2] = A[1];R[0] = B[3];R[1] = B[1];R[2] = B[2];
//            default:break;
//        }
//        if ((checkLocPointStraight(Q[0], Q[1], Q[2]) != -1 && checkLoc3PointStraight(Q[0], Q[1], R[0], R[1], R[2]) != 1)
//            || (checkLocPointStraight(Q[0], Q[1], Q[2]) != 4 &&
//                checkLoc3PointStraight(Q[0], Q[1], R[0], R[1], R[2]) != -1))
//            return true;
//        if ((checkLocPointStraight(Q[0], Q[2], Q[1]) != -1 && checkLoc3PointStraight(Q[0], Q[2], R[0], R[1], R[2]) != 1)
//            || (checkLocPointStraight(Q[0], Q[2], Q[1]) != 4 &&
//                checkLoc3PointStraight(Q[0], Q[2], R[0], R[1], R[2]) != -1))
//            return true;
//
//        switch (T) {
//            case 0 :Q[0] = B[3];Q[1] = B[2];Q[2] = B[1];R[0] = A[0];R[1] = A[1];R[2] = A[2];
//            case 1 :Q[0] = B[2];Q[1] = B[3];Q[2] = B[0];R[0] = A[1];R[1] = A[0];R[2] = A[3];
//            case 2 :Q[0] = B[1];Q[1] = B[3];Q[2] = B[0];R[0] = A[2];R[1] = A[0];R[2] = A[3];
//            case 3 :Q[0] = B[0];Q[1] = B[2];Q[2] = B[1];R[0] = A[3];R[1] = A[1];R[2] = A[2];
//            default:break;
//        }
//        if ((checkLocPointStraight(Q[0], Q[1], Q[2]) != -1 && checkLoc3PointStraight(Q[0], Q[1], R[0], R[1], R[2]) != 1)
//            || (checkLocPointStraight(Q[0], Q[1], Q[2]) != 4 &&
//                checkLoc3PointStraight(Q[0], Q[1], R[0], R[1], R[2]) != -1))
//            return true;
//        if ((checkLocPointStraight(Q[0], Q[2], Q[1]) != -1 && checkLoc3PointStraight(Q[0], Q[2], R[0], R[1], R[2]) != 1)
//            || (checkLocPointStraight(Q[0], Q[2], Q[1]) != 4 &&
//                checkLoc3PointStraight(Q[0], Q[2], R[0], R[1], R[2]) != -1))
//            return true;
//    }

  return false;
}

void Tank::collideResponse(GameObject* obj){
    int T = 2 * (x > obj->getX()) + (y > obj->getY());
    int line; ///0 right 1 up 2 3

    switch (T) {
        case 0 : if(obj->getX()-x>obj->getY()-y) line=1;
                else line = 0;
        case 1 : if(obj->getX()-x>y-obj->getY()) line=1;
                else line = 2;
        case 2 : if(x-obj->getX()>obj->getY()-y) line=3;
                else line = 0;
        case 3 : if(x-obj->getX()>y-obj->getY()) line=3;
                else line = 2;
        default:break;
    }
    if(getRotation()==90*line)
        speed=0;
}
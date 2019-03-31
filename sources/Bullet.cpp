//
// Created by Apxapa on 31.03.2019.
//

#include "Bullet.hpp"

Bullet::Bullet() : GameObject::GameObject() {
    Bullet::type=BULLET;
}

Bullet::Bullet(GameObject *obj) {

}

void Bullet::draw(sf::RenderWindow *window) {
    window->draw(Bullet::sprite);
}

bool Bullet::collideCheck(GameObject *obj) {
}

void Bullet::collideResponse(GameObject *obj) {

}

void Bullet::update() {
    setPosition(x+speedX*TIME,y+speedY*TIME);
}



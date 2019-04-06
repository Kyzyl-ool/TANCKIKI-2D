//
// Created by Apxapa on 31.03.2019.
//

#ifndef TANCKIKI_2D_BULLET_HPP
#define TANCKIKI_2D_BULLET_HPP

#include "GameObject.hpp"


class Bullet: public GameObject {
public:
    Bullet();

    void update() override;



    void draw(sf::RenderWindow* window) override;

    void collideResponse(GameObject* obj) override;
};





#endif //TANCKIKI_2D_BULLET_HPP

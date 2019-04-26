//
// Created by Apxapa on 31.03.2019.
//

#ifndef TANCKIKI_2D_BULLET_HPP
#define TANCKIKI_2D_BULLET_HPP

#include "GameObject.hpp"


class Bullet: public GameObject {
    int power;
public:
    Bullet();
    Bullet(Bullet_t);

    void update(float time) override;

    int getPower();

    void setPower(int power);

    void draw(sf::RenderWindow& window) override;

    void collideResponse(GameObject *obj, float time) override;

    void collideResponse(Match *match, float time) override ;
};





#endif //TANCKIKI_2D_BULLET_HPP

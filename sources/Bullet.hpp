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

    void update() override;

    int getPower();

    void setPower(int power);

    void draw(sf::RenderWindow& window) override;

    void collideResponse(GameObject* obj) override;

    //void collideResponse(Match *match, std::vector<int> vec) override ;
};





#endif //TANCKIKI_2D_BULLET_HPP

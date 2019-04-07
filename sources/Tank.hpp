//
// Created by Apxapa on 30.03.2019.
//

#ifndef TANCKIKI_2D_TANK_H
#define TANCKIKI_2D_TANK_H

#include "GameObject.hpp"
#include "Bullet.hpp"

class Tank : public GameObject {
protected:
    int health;

    Bullet_t bulType;

public:
    void update() override;
    
    void draw(sf::RenderWindow &window) override;


    void collideResponse(GameObject *obj) override;
    //void collideResponse(Match *match, std::vector<int> vec) override;

    GameObject * shot(Bullet_t BULLET) override;

    int getHealth();

    void setHealth(int healthScore);
};



#endif //TANCKIKI_2D_TANK_H
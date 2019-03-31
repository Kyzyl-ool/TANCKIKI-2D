//
// Created by Apxapa on 30.03.2019.
//

#ifndef TANCKIKI_2D_TANK_H
#define TANCKIKI_2D_TANK_H

#include "GameObject.hpp"
#include "Bullet.hpp"

enum Tank_t {
    TANK1,
    TANK2,
};




class Tank : public GameObject {
protected:
    int health;

public:
    void update() override;

    Tank();

    void draw(sf::RenderWindow* window) override;

    bool collideCheck(GameObject *obj) override;

    void collideResponse(GameObject *obj) override;

    int getHealth();

    void setHealth(int healthScore);

    void shot(Bullet_t BULLET);
};



#endif //TANCKIKI_2D_TANK_H
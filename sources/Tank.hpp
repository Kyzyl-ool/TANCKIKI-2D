//
// Created by Apxapa on 30.03.2019.
//

#ifndef TANCKIKI_2D_TANK_H
#define TANCKIKI_2D_TANK_H

#include "GameObject.hpp"

class Tank : public GameObject {
protected:
    int health;

public:
    void update() override;

    void draw(sf::RenderWindow &window) override;

    bool collideCheck(GameObject* obj) override;

    void collideResponse(GameObject* obj) override;

    Tank();

    int getHealth();

    void setHealth(int healthScore);
};



#endif //TANCKIKI_2D_TANK_H
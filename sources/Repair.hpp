//
// Created by Apxapa on 26.04.2019.
//

#ifndef TANCHIKI_REPAIR_HPP
#define TANCHIKI_REPAIR_HPP

#include "GameObject.hpp"

class Repair : public GameObject {
private:
    int health;
public:
    Repair(int health);
    int getHealth();

    void draw(sf::RenderWindow &window) override;
    void collideResponse(GameObject *obj, float time) override;
};




#endif //TANCHIKI_REPAIR_HPP

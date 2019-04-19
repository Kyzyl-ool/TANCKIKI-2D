//
// Created by Apxapa on 30.03.2019.
//

#ifndef TANCKIKI_2D_TANK_H
#define TANCKIKI_2D_TANK_H

#include "GameObject.hpp"
#include "Bullet.hpp"

class Tank : public GameObject {
protected:
    float health;
    Bullet_t bulType;
    std::string name = "Unnamed";
public:
    const std::string &getName() const;

public:
    Tank(float health, std::string the_name);
    void update(float time) override;

    void draw(sf::RenderWindow &window) override;


    void collideResponse(GameObject *obj, float time) override;
    void collideResponse(Match *match, float time) override;

    GameObject * shot(Bullet_t BULLET) override;

    float getHealth();

    void setHealth(float healthScore);
};



#endif //TANCKIKI_2D_TANK_H
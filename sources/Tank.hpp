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
    sf::Texture textureTower;
    sf::Sprite spriteTower;
    float speedTower;
    Bullet_t bulType;

public:
    Tank(float health);
    void update(float time) override;

    void draw(sf::RenderWindow &window) override;


    void collideResponse(GameObject *obj, float time) override;
    void collideResponse(Match *match, float time) override;

    GameObject *shot(Bullet_t BULLET) override;

    float getHealth();
    float getSpeedTower();

    void setTextureTower(const char* address);
    void setSpriteTower(int X, int Y, int sizeX_, int sizeY_);
    void setSpeedTower(float angleSpeed);
    void setHealth(float healthScore);

};



#endif //TANCKIKI_2D_TANK_H
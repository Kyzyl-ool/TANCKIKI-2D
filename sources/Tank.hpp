//
// Created by Apxapa on 30.03.2019.
//

#ifndef TANCKIKI_2D_TANK_H
#define TANCKIKI_2D_TANK_H

#include "GameObject.hpp"
#include "Bullet.hpp"

class Match;

class Tank : public GameObject {
protected:
    float health;
    sf::Texture textureTower;
    sf::Sprite spriteTower;
    float speedTower;
    float maxHealth;
    sf::Texture textBoom;
    sf::Sprite sprBoom;
    float recharge;
    float towerX, towerY;
    int owner = -1;
public:
    void setTowerY(float towerY);

public:
    void setTowerX(float towerX);

public:
    float getTowerY() const;

public:
    float getTowerX() const;

public:
    float getMaxHealth() const;

protected:
    Bullet_t bulType;
    std::string playerName = "Unnamed";
public:
    void setPlayerName(const std::string &playerName);

protected:
    int ammunition;
    int count_ammun;
    int lastEnemy;
public:
    const std::string &getName() const;
    Tank(float health, const std::string &the_player_name, const std::string &color);
    void update(float time) override;

    void draw(sf::RenderWindow &window) override;

    void collideResponse(GameObject *obj, float time) override;
    void collideResponse(Match *match, float time) override;

    GameObject *shot() override;
    int getLastEnemy();
    float getRecharge();
    float getHealth();
    float getSpeedTower();
    Bullet_t getTypeBullet();
    int getAmmun();
    int getCountAmmun();
    void setTextBoom(const char* address);
    void setSprBoom(int X, int Y, int sizeX, int sizeY);

    void setRecharge(float);
    void updateRecharge(float time);
    void setTextureTower(const char* address);
    void setSpriteTower(int X, int Y, int sizeX_, int sizeY_);
    void setSpeedTower(float angleSpeed);
    void setHealth(float healthScore);
    float checkOrient(float X, float Y, sf::RenderWindow *window);
    void setTypeBullet(Bullet_t);
    void setConfiguration(float iX, float iY, float ihealth, float itowerSpeed, float irecharge, float itowerX,
                          float itowerY, int iammunition, float iRotaton, float iTowerRotation, std::string name);
    float getTowerRotation();
    float getViewCoordX(Match *match);
    float getViewCoordY(Match *match);
};



#endif //TANCKIKI_2D_TANK_H
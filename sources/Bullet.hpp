//
// Created by Apxapa on 31.03.2019.
//

#ifndef TANCKIKI_2D_BULLET_HPP
#define TANCKIKI_2D_BULLET_HPP

#include "GameObject.hpp"

enum Bullet_t {
    ABYSSSHOT = 0,
    LOWSHOT,
    MIDDLESHOT,
    POWERFULLSHOT
};

class Bullet : public GameObject {
protected:

public:
    void update() override;

    Bullet();
    Bullet(GameObject *obj); ///кто порождает пулю

    void draw(sf::RenderWindow* window) override;

    bool collideCheck(GameObject *obj) override;

    void collideResponse(GameObject* obj) override;
};























#endif //TANCKIKI_2D_BULLET_HPP

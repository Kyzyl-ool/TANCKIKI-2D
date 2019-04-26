//
// Created by Apxapa on 26.04.2019.
//

#ifndef TANCHIKI_AMMUNITION_HPP
#define TANCHIKI_AMMUNITION_HPP

#include "GameObject.hpp"


class Ammunition : public GameObject{
private:
    int count;
public:
    Ammunition(int Count);

    void setCount(int);
    int getCount();

    void draw(sf::RenderWindow &window) override;
    void collideResponse(GameObject *obj, float time) override;
};


#endif //TANCHIKI_AMMUNITION_HPP

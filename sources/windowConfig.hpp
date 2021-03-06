//
// Created by Кежик Кызыл-оол on 2019-03-19.
//

#ifndef TANCHIKI_CONFIG_HPP
#define TANCHIKI_CONFIG_HPP


const unsigned int WINDOW_HEIGHT = 700;
const unsigned int WINDOW_WIDTH = 1200;
const unsigned int MAP_HEIGHT = 1600;
const unsigned int MAP_WIDTH = 3000;
const int DEATH_TIME = 30000;  ///Milliseconds
const char WINDOW_NAME[] = "TANCHIKI GAME";
const float SPEED_OF_LOW_BULLET = 0.4;
const float RECHARGE_OF_LOWSHOT = 150;
const int DAMAGE_OF_LOWSHOT = 50;
const int COEF_LOWSHOT = 10;
const float SPEED_OF_MIDDLE_BULLET = 0.28;
const float RECHARGE_OF_MIDDLESHOT = 400;
const int DAMAGE_OF_MIDDLESHOT = 100;
const int COEF_MIDDLESHOT = 5;
const float SPEED_OF_POWERFULLSHOT = 0.14;
const float RECHARGE_OF_POWERFULLSHOT = 2000;
const int DAMAGE_OF_POWERFULLSHOT = 490;
const int COEF_POWERFULLSHOT = 2;
const char IMAGE_FOR_MAP[] = "images/minecraftblocks2.png";
const float TANK_TOWER_SPEED = 0.12;
const float TANK_VELOCITY = 0.12;
const float TANK_ANGLE_SPEED = 0.09;
const float DAMAGE_OF_COLLISION = 0.04;
const float DAMAGE_OF_DEATHTIME = 2;
const char MAP_FILE[] = "./sources/json/map3.txt";
const float TANK_HEALTH = 1000;


#endif //TANCHIKI_CONFIG_HPP
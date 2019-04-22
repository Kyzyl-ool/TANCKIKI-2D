//
// Created by Кежик Кызыл-оол on 2019-03-31.
//

#include <string>
#include <map>

typedef enum gameObject_messages{
    GAMEOBJECT_MESSAGE_APPEAR = 0,
    GAMEOBJECT_MESSAGE_MOVE_RIGHT,
    GAMEOBJECT_MESSAGE_MOVE_LEFT,
    GAMEOBJECT_MESSAGE_MOVE_BRAKE,
    GAMEOBJECT_MESSAGE_MOVE_FORWARD,
    GAMEOBJECT_MESSAGE_NO_ACTION,
    GAMEOBJECT_MESSAGE_NO_ROTATION,
    GAMEOBJECT_MESSAGE_SHOOT,
    GAMEOBJECT_MESSAGE_DESTROY,
    GAMEOBJECT_MESSAGE_ROTATE_TOWER
}gameObject_message_t;

std::map <std::string, gameObject_message_t> gameObjectMessageId = {
        {"moveLeft", GAMEOBJECT_MESSAGE_MOVE_LEFT},
        {"moveDown", GAMEOBJECT_MESSAGE_MOVE_BRAKE},
        {"moveRight", GAMEOBJECT_MESSAGE_MOVE_RIGHT},
        {"moveUp", GAMEOBJECT_MESSAGE_MOVE_FORWARD},
        {"stop", GAMEOBJECT_MESSAGE_NO_ACTION},
        {"shoot", GAMEOBJECT_MESSAGE_SHOOT},
        {"destroy", GAMEOBJECT_MESSAGE_DESTROY},
        {"appear", GAMEOBJECT_MESSAGE_APPEAR},
        {"noRotation", GAMEOBJECT_MESSAGE_NO_ROTATION},
        {"rotateTower", GAMEOBJECT_MESSAGE_ROTATE_TOWER}
};

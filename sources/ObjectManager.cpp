//
// Created by Кежик Кызыл-оол on 2019-02-26.
//

#include "ObjectManager.hpp"

ObjectManager::ObjectManager(sf::RenderWindow &window):
mainWindow(window)
{
    objects = std::vector <GameObject* > ();
    tanks = std::vector <GameObject* > ();
}

const sf::RenderWindow &ObjectManager::getMainWindow() const {
    return mainWindow;
}

void ObjectManager::addGameObject(GameObject *obj) {
    objects.push_back(obj);
    if (obj->getType() == TANK) {
        tanks.push_back(obj);
    }
}

void ObjectManager::removeGameObjectById(int gameObjectId) {
    objects.erase(objects.begin()+gameObjectId);
}

GameObject* ObjectManager::getGameObjectById(int gameObjectId) {
    ///@todo реализовать
    return objects[gameObjectId];
}

const std::vector<GameObject *> &ObjectManager::getObjects() const {
    return objects;
}

const std::vector<GameObject *> &ObjectManager::getTanks() const {
    return tanks;
}

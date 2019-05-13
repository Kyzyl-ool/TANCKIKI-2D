//
// Created by Кежик Кызыл-оол on 2019-02-26.
//

#include "ObjectManager.hpp"

ObjectManager::ObjectManager(sf::RenderWindow &window):
mainWindow(window)
{
    objects = std::vector <GameObject* > ();
    tanks = std::vector <Tank* > ();
}

const sf::RenderWindow &ObjectManager::getMainWindow() const {
    return mainWindow;
}

unsigned long ObjectManager::addGameObject(GameObject *obj) {
    objects.push_back(obj);
    if (obj->getType() == TANK) {
        tanks.push_back((Tank* )obj);
    }
    return tanks.size()-1;
}

void ObjectManager::removeGameObjectById(int gameObjectId) {
    objects.erase(objects.begin()+gameObjectId);
}

GameObject* ObjectManager::getGameObjectById(int gameObjectId) {
    return objects[gameObjectId];
}

const std::vector<GameObject *> &ObjectManager::getObjects() const {
    return objects;
}

const std::vector<Tank *> & ObjectManager::getTanks() const {
    return tanks;
}

ObjectManager::~ObjectManager() {
    for (const auto &item : objects) {
        delete(item);
    }
}

Tank *ObjectManager::getTankById(int tankId) {
    return tanks[tankId];
}

//
// Created by Кежик Кызыл-оол on 2019-02-26.
//

#ifndef TANCHIKI_OBJECTMANAGER_HPP
#define TANCHIKI_OBJECTMANAGER_HPP

#include <SFML/Graphics.hpp>
#include "GameObject.hpp"
#include "Tank.hpp"


/*!
 * Этот менеджер отвечает за хранение игровых объектов.
 */
class ObjectManager
{
private:
    /// \todo Нужно придумать свойство, в котором будут храниться все игровые объекты.
    std::vector<GameObject*> objects;
    std::vector <GameObject*> tanks;
    sf::RenderWindow& mainWindow;
public:
    const std::vector<Tank *> & getTanks() const;

    const std::vector<GameObject *> &getObjects() const;

    ObjectManager(sf::RenderWindow &window);

    virtual ~ObjectManager();

    void addGameObject(GameObject* obj);
    void removeGameObjectById(int gameObjectId);
    GameObject* getGameObjectById(int gameObjectId);
    const sf::RenderWindow &getMainWindow() const;

    ~ObjectManager();
};

#endif //TANCHIKI_OBJECTMANAGER_HPP

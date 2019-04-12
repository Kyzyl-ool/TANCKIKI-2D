//
// Created by Кежик Кызыл-оол on 2019-02-26.
//

#ifndef TANCHIKI_PHYSICSMANAGER_HPP
#define TANCHIKI_PHYSICSMANAGER_HPP

#include "ObjectManager.hpp"

/*!
 * Этот класс отвечает за обработку игровой механики, за взаимодействие игровых объектов между собой.
 */
class PhysicsManager
{
private:
    ObjectManager* objectManager;

public:
    /*!
     * \brief Инициализация менеджета по физике.
     * @param theObjectManager - указатель на менеджера по объектам, откуда будет браться
     * информация об игровых объектах.
     */
    PhysicsManager(ObjectManager* theObjectManager);

    /*!
     * \brief Обновляет все игровые объекты.
     *
     * \details Реализация довольно проста: необходимо вызвать у каждого игрового объекты метод update.
     */
    void updateGameObjects(Match *match);
};

#endif //TANCHIKI_PHYSICSMANAGER_HPP

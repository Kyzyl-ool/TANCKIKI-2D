//
// Created by Кежик Кызыл-оол on 2019-02-26.
//

#ifndef TANCHIKI_GRAPHICSMANAGER_HPP
#define TANCHIKI_GRAPHICSMANAGER_HPP


#include "ObjectManager.hpp"
#include "blocks.hpp"
#include <SFML/Graphics.hpp>

/*!
 * Этот класс отвечает за игровую графику.
 */
class GraphicsManager
{
private:
    ObjectManager* objectManager;           /// указатель на менедера по объектам
    sf::RenderWindow& window;

public:
    /*!
     * \brief Инициализирует менеджера по графике.
     * @param theObjectManager – указатель на менеджеа по обектам, откуда будут браться
     * игровые объекты для прорисовки
     */
    GraphicsManager(ObjectManager *theObjectManager, block_t *blocks, unsigned int amount_of_blocks_y,
                    unsigned int amount_of_blocks_x, sf::RenderWindow &the_window);


    /*!
     * \brief Рисует все игровые объекты на экран.
     *
     * \details Достаточно вызвать у каждого игрового объекта метод draw.
     */
    void drawGameObjects();

    sf::RenderWindow* getWindow();
};


#endif //TANCHIKI_GRAPHICSMANAGER_HPP

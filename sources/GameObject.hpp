//
// Created by Кежик Кызыл-оол on 2019-02-26.
//

#ifndef TANCHIKI_GAMEOBJECT_HPP
#define TANCHIKI_GAMEOBJECT_HPP

#include <SFML/Graphics.hpp>
#include "windowConfig.hpp"


enum gameObject_t {
    ABYSS = 0,
    TANK,
    BULLET,
    GROUND
};


/*!
 *      \brief
 *      Родительский класс для всех игровых объектов
 */
class GameObject
{
protected:
    bool alive;             /// жив ли ещё объект
    float x, y;            /// координаты объекта на экране (центр)
    float sizeX, sizeY;    /// размеры
    float speed;           /// cкорость движения
    sf::Sprite sprite;
    sf::Texture texture;
    int gameObjectId;       ///айди объекта
    int ownerId;            ///айди владельца
    gameObject_t type;
public:
    gameObject_t getType() const;
    /// тип


public:

    GameObject();

    virtual ~GameObject();

    /*!
     * \brief Рисует игровой объект на экране
     *
     * Спрайт тупо рисуется на экране с координатами x, y.
     */
    virtual void draw(sf::RenderWindow &window);

    /*!
     * \brief Обновляет игровой объект. У каждого игрового объекта своя реализация этого метода.
     */
    virtual void update();

    /*!
     * \brief
     * Проверяет, есть ли взаимодействие с игровым объектом obj
     *
     * @param obj - указатель на игровой объект, взаимодействие с которым проверяется
     * @return true, если есть взаимодействие. В противном случае – false
     */
    virtual bool collideCheck(GameObject* obj);

    /*!
     * \brief
     * Выполняет акт взаимодействия с игровым объектом obj
     *
     * @param obj - указатель на игровой объект, с которым будет выполнен акт взаимодействия
     */
    virtual void collideResponse(GameObject* obj);

    float getX() const;

    float getY() const;

    float getSpeed() const;

    float getSizeX() const;

    float getSizeY() const;

    float getRotation() const;

    bool isAlive() const;

    virtual const sf::Sprite &getSprite() const;

    virtual const sf::Texture &getTexture() const;

    void setRotation(int angle);

    void setPosition(float x, float y);

    void setSpeed(float v);

    void setSizeObj(float sizeX, float sizeY);

    void setSizeSprite(float sizeX, float sizeY);

    void setAlive(bool alive);

    void setSprite(sf::Sprite sprite_);
    void setSprite(int X, int Y, int sizeX, int sizeY);

    void setTexture(sf::Texture texture_);
    void setTexture(const char* address);

    void multSize(float k);
};

#endif //TANCHIKI_GAMEOBJECT_HPP


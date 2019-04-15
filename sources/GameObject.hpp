//
// Created by Кежик Кызыл-оол on 2019-02-26.
//

#ifndef TANCHIKI_GAMEOBJECT_HPP
#define TANCHIKI_GAMEOBJECT_HPP

#include <SFML/Graphics.hpp>
#include "windowConfig.hpp"
#include "Collision.hpp"

class Match;


enum gameObject_t {
    ABYSS = 0,
    TANK,
    BULLET,
    GROUND
};

enum Bullet_t {
    ABYSSSHOT = 0,
    LOWSHOT,
    MIDDLESHOT,
    POWERFULLSHOT
};

enum Tank_t {
    TANK1,
    TANK2,
};


/*!
 *      \brief
 *      Родительский класс для всех игровых объектов
 */
class GameObject
{
protected:
    bool alive;            /// жив ли ещё объект
    float x, y;            /// координаты объекта на экране (центр)
    float sizeX, sizeY;    /// размеры
    float speed;           /// cкорость движения
    float speedAngle;      /// угловая скорость в градусах
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
    virtual void update(float time);

    /*!
     * \brief
     * Проверяет, есть ли взаимодействие с игровым объектом obj
     *
     * @param obj - указатель на игровой объект, взаимодействие с которым проверяется
     * @return true, если есть взаимодействие. В противном случае – false
     */
    bool collideCheck(GameObject *obj);

    bool collideCheck(Match *match);
//
//    void collideResponse(Match *match, std::vector<int> vec);

    /*!
     * \brief
     * Выполняет акт взаимодействия с игровым объектом obj
     *
     * @param obj - указатель на игровой объект, с которым будет выполнен акт взаимодействия
     */
    virtual void collideResponse(GameObject *obj, float time);

    virtual void collideResponse(Match *match, float time);

    virtual GameObject * shot(Bullet_t BULLET);

    float getX() const;

    float getY() const;

    float getSpeed() const;

    float getSizeX() const;

    float getSizeY() const;

    float getRotation() const;

    bool isAlive() const;

    int getOwnerId() const;

    int getObjectId() const;

    float getSpeedAngle() const;

    virtual const sf::Sprite &getSprite() const;

    virtual const sf::Texture &getTexture() const;

    void setRotation(float angle);

    void setPosition(float x, float y);

    void setSpeed(float sp);

    void setSizeObj(float sizeX, float sizeY);

    void setSizeSprite(float sizeX, float sizeY); ///задает размеры спрайта, если размеры спрайта и объекта совпадают!!!

    void setAlive(bool alive);

    void setSprite(sf::Sprite sprite_);
    void setSprite(int X, int Y, int sizeX, int sizeY);

    void setTexture(sf::Texture texture_);
    void setTexture(const char* address);

    void multSize(float k);

    void setOwnerId(int pid);

    void setObjectId(int id);

    void setSpeedAngle(float apAngle);

    float checkOrient(float X, float Y); ///определяет синус угла направления минус угол объекта, если положительный, то объект крутить по часовой стрелки

    void rotateLeft();      // задаёт движение в левую сторону, срабатывает при нажатии влево
    void rotateRight();     // задаёт движение в правую сторону, срабатывает при нажатии вправо
    void stopRotate();      // задаёт прекращение поворота, срабатывает при отпускании клавиш влево/вправо
    void go();              // задаёт движение вперёд, срабатывает при нажатии вперёд
    void stop();            // задаёт прекращение движения, срабатывает при отпускании клавиш вперед/назад
};

#endif //TANCHIKI_GAMEOBJECT_HPP


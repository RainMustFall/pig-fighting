#ifndef MOVEOBJECT_H
#define MOVEOBJECT_H
#include "game_object.h"
#include "ground.h"

class MovingObject : public GameObject {
public:
    MovingObject(int x, int y, int width, int height);

    void UpdatePosition();
    virtual void ApplyPhysics();

    // Непосредственно определяет, с какой именно
    // стороны объект коснулся платформы
    utils::HitType CheckHitType(const Ground& ground);

    // Стабилизирует положение в зависимости от типа столкновения
    void StabilizePosition(const Ground& groung);

    // Проверяет, касается ли объект земли, и, если да,
    // стабилизирует его положение. Если ещё и касается сверху,
    // возвращает указатель на платформу, иначе nullptr
    const Ground* HitsGround(const std::vector<Ground>& ground);
    void CheckBoundaries();
    //virtual bool Hits(const GameObject& obj) const;
    utils::Point moveVector_ = {0, 0};


    //показывает, какая сторона объекта повернута к экрану

        void UpdatePlatform(const std::vector<Ground>& ground);
protected:
    double GetMoveVectorX() const;



    // Флажок, показывающий, с какой стороны мы врезались
    // последний раз.
    utils::HitType last_hit;
    utils::Side current_side = utils::Side::LEFT;

    // Суть в том, что какую-то платформу мы временно
    // игнорируем и столкновения с ней не учитываем.
    // Например, если хотим провалиться сквозь неё вниз
    // или пропрыгуть сквозь неё снизу
    const Ground* ignored_platform = nullptr;
    const Ground* current_platform = nullptr;
};

#endif // MOVEOBJECT_H

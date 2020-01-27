#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <QPainter>
#include <QMouseEvent>
#include "utils.h"

// Абстрактный класс объекта в игре, хранящий самую базовую
// информацию, вроде положения, длины, ширины.
class GameObject
{
public:
    friend class MainWindow;

    GameObject(int x, int y, int width, int height);
    virtual ~GameObject() = default;

    virtual void Draw(QPainter& painter) const = 0;

    // Геттеры (вдруг пригодятся)
    int Width() const;
    int Height() const;
    int xPos() const;
    int yPos() const;

    virtual bool Hits(const GameObject* obj) const;
    void UpdatePosition();
protected:
    utils::Point position_;
    utils::BoundingBox bBox_;
};

#endif // GAMEOBJECT_H

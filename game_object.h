#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <QPainter>
#include <QMouseEvent>
#include "utils.h"

// An abstract class of object in the game that stores
// the most basic information, such as position, length, width.
class GameObject
{
public:
    friend class MainWindow;

    GameObject(int x, int y, int height, int width);
    virtual ~GameObject() = default;

    virtual void Draw(QPainter& painter) const = 0;

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

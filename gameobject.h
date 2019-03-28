#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <QPainter>
#include <QMouseEvent>

struct Point {
    int x;
    int y;
};

struct BoundingBox {
    int height_;
    int width_;
};

// Абстрактный класс объекта в игре, хранящий самую базовую
// информацию, вроде положения, длины, ширины.
class GameObject
{
public:
    friend class MainWindow;

    // Конструктор
    GameObject(int x, int y, int width, int height);
    void Draw(QPainter& painter) const;
    // Геттеры (вдруг пригодятся)
    int Width() const;
    int Height() const;
    int xPos() const;
    int yPos() const;

protected:
    Point position_;
    BoundingBox bBox_;

    Point moveVector_;
};

#endif // GAMEOBJECT_H

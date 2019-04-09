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

    bool Hits(const GameObject& obj) const;
    void UpdatePosition();
protected:
    Point position_;
    BoundingBox bBox_;
    bool is_moving_ = 0; //кажется, что-то такое нужно чтобы запрещать прыжки в падении
                         // заодно, можно с помощью такой штуки каждый тик таймера
                         // обновлять полет запущенной свинюшки. то есть, после ее броска мы ставим
                         // этот флажок в 1, придаем константную скорость и забываем про ее движение.
    bool force_move_;
    Point moveVector_;
};

#endif // GAMEOBJECT_H

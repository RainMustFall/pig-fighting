#ifndef PERSON_H
#define PERSON_H
#include "gameobject.h"
#include "animation.h"
#include "movingobject.h"
#include "freepig.h"

class MainWindow;

class Person: public MovingObject
{
public:

    Person(int x, int y, int height, int width);

    void CatchPressedKey(int key, const int up_key, const int left_key,
                         const int down_key, const int right_key);
    void CatchReleasedKey(int key, const int up_key, const int left_key,
                         const int down_key, const int right_key);
    // Проверяет, какие клавиши нажаты,
    // и обрабатывает все нажатия
    void ProcessKeyboard();
    void CatchPig(FreePig& pig);
    void UpdateAnimation();
    void Draw(QPainter& painter) const override;

    std::list<FreePig>::iterator FindClosestFreePig(MainWindow& w);

    bool armed_ = 0;
    // Флаги, показывающие, какие клавиши зажаты
    // в текущий момент времени
    bool Up_pressed = false;
    bool Left_pressed = false;
    bool Right_pressed = false;
    bool Down_pressed = false;

    // Объекты, отвечающие за проигрывание анимации
    Animation animation_;
};

#endif // PERSON_H

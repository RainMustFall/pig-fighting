#ifndef PERSON_H
#define PERSON_H
#include "gameobject.h"
#include "movingobject.h"

class Person: public MovingObject
{
public:
    Person(int x, int y, int height, int width);

    // Проверяет, какие клавиши нажаты,
    // и обрабатывает все нажатия
    void ProcessKeyboard();

    // Флаги, показывающие, какие клавиши зажаты
    // в текущий момент времени
    bool Up_pressed = false;
    bool Left_pressed = false;
    bool Right_pressed = false;
    bool Down_pressed = false;
};

#endif // PERSON_H

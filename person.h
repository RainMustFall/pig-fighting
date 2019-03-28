#ifndef PERSON_H
#define PERSON_H

#include "gameobject.h"

class Person : public GameObject
{
public:
    Person(int x, int y, int height, int width);

    void UpdatePosition();
    // Проверка на столкновение с другим объектом
    bool Hits(const GameObject& obj) const;
};

#endif // PERSON_H

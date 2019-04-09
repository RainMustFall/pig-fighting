#ifndef PERSON_H
#define PERSON_H

#include "gameobject.h"

class Person : public GameObject
{
public:
    Person(int x, int y, int height, int width);
};

#endif // PERSON_H

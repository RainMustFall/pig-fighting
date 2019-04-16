#ifndef SHOTPIG_H
#define SHOTPIG_H
#include "movingobject.h"
#include "gameobject.h"

class ShotPig : public MovingObject
{
public:
    ShotPig(int height, int width, int direction);

    bool Hits(GameObject& player);
};

#endif // SHOTPIG_H

#ifndef SHOTPIG_H
#define SHOTPIG_H
#include "movingobject.h"
#include "gameobject.h"
#include "person.h"

class ShotPig : public MovingObject
{
public:
    ShotPig(int height, int width, int direction, const Person* shooting_player);
    bool if_Hits(std::vector<Person>& persons,
                 const std::vector<Ground>& ground);
    const Person* shooting_player;
};

#endif // SHOTPIG_H

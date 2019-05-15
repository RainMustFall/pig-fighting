#ifndef SHOTPIG_H
#define SHOTPIG_H
#include "movingobject.h"
#include "gameobject.h"
#include "person.h"


class ShotPig : public MovingObject
{
public:
    ShotPig(int height, int width, int direction, const Person* shooting_player,
            Animation* flying_left, Animation* flying_right);
    const GameObject* Pig_Hits(std::vector<Person>& persons,
                 const std::vector<Ground>& ground);
    const Person* shooting_player;
    void Draw(QPainter& painter) const override;

    const Animation* pig_flying_l;
    const Animation* pig_flying_r;
};

#endif // SHOTPIG_H

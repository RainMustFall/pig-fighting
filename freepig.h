#ifndef FREEPIG_H
#define FREEPIG_H
#include "movingobject.h"
#include "animation.h"

class FreePig : public MovingObject
{
public:
    FreePig(int x, int y, Animation* running_left, Animation* running_right);
    FreePig GeneratePig();
    void setX (double x);
    void setY (double y);
    void PositionGenerate();
    void Draw(QPainter& painter) const;
    void UpdateAnimation();

    const Animation* pig_running_l;
    const Animation* pig_running_r;
};

#endif // FREEPIG_H

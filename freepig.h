#ifndef FREEPIG_H
#define FREEPIG_H
#include "movingobject.h"
#include "resourcestorage.h"

class FreePig : public MovingObject
{
public:
    FreePig(int x, int y, const PigAnimationStorage* animations);
    FreePig GeneratePig();
    void setX (double x);
    void setY (double y);
    void PositionGenerate();
    void Draw(QPainter& painter) const;
    void UpdateAnimation();

    const PigAnimationStorage* animations_;
};

#endif // FREEPIG_H

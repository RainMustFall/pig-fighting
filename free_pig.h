#ifndef FREEPIG_H
#define FREEPIG_H
#include "moving_object.h"
#include "resource_storage.h"

class FreePig : public MovingObject
{
public:
    FreePig(int x, int y, const PigAnimationStorage* animations);
    FreePig GeneratePig();
    void SetX (double x);
    void SetY (double y);
    void PositionGenerate();
    void Draw(QPainter& painter) const;
    void UpdateAnimation();

    const PigAnimationStorage* animations_;
};

#endif // FREEPIG_H

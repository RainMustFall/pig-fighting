#ifndef FREEPIG_H
#define FREEPIG_H
#include "movingobject.h"


class FreePig : public MovingObject
{
public:
    FreePig(int x, int y);
    void setX(double x);
    void setY(double y);
};

#endif // FREEPIG_H

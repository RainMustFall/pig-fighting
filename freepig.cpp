#include "freepig.h"
#include "movingobject.h"
#include "constants.h"

FreePig::FreePig(int x, int y) :
    MovingObject(x, y, kPigSize, kPigSize) {};
void FreePig::setX(double x) {
    position_.x = x;
}
void FreePig::setY(double y) {
    position_.y = y;
}


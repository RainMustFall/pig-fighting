#include "freepig.h"
#include "movingobject.h"

FreePig::FreePig(int x, int y) :
    MovingObject(x, y, 20, 20) {};
void FreePig::setX(double x) {
    position_.x = x;
}
void FreePig::setY(double y) {
    position_.y = y;
}


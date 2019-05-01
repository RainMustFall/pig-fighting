#include "freepig.h"
#include "movingobject.h"
#include "constants.h"
#include <QDebug>

FreePig::FreePig(int x, int y) :
    MovingObject(x, y, kPigSize, kPigSize)
    {
    moveVector_.x = -1.0;
    };
void FreePig::setX(double x) {
    position_.x = x;
}
void FreePig::setY(double y) {
    position_.y = y;
}

void FreePig::PositionGenerate() {
    int random_number = rand() % 1000;
    if (random_number == 0){
        if (GetMoveVectorX() != -2 * kSpeed) { //чтобы свинка не остановилась
        moveVector_.x += 2 * kSpeed;
        qDebug() << GetMoveVectorX();
        }
    }
    if(random_number == 1){
        qDebug() << "change direction";
        moveVector_.x *= -1;
    } else if (random_number == 2){
        if (GetMoveVectorX() != 2 * kSpeed){//чтобы свинка не остановилась
        moveVector_.x -= 2 * kSpeed;
        qDebug() << GetMoveVectorX();
        }
    }
}


#include "freepig.h"
#include "movingobject.h"
#include "constants.h"
#include <QDebug>

FreePig::FreePig(int x, int y, Animation* running_left, Animation* running_right)
    : MovingObject(x, y, kPigSize, kPigSize),
      pig_running_l(running_left),
      pig_running_r(running_right)
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
        }
    }
    if(random_number == 1){
        moveVector_.x *= -1;
    } else if (random_number == 2){
        if (GetMoveVectorX() != 2 * kSpeed){//чтобы свинка не остановилась
        moveVector_.x -= 2 * kSpeed;
        }
    }
}

void FreePig::Draw(QPainter& painter) const {

    if (current_side == Side::LEFT) {
        painter.drawPixmap(position_.x, position_.y,
                           bBox_.width_, bBox_.height_,
                           pig_running_l->CurrentFrame());
    } else {
        painter.drawPixmap(position_.x, position_.y,
                           bBox_.width_, bBox_.height_,
                           pig_running_r->CurrentFrame());
    }
}

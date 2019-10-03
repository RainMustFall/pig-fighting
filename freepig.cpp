#include "freepig.h"
#include "movingobject.h"
#include "constants.h"
#include <QDebug>

FreePig::FreePig(int x, int y, const PigAnimationStorage* animations)
    : MovingObject(x, y, kPigSize, kPigSize),
      animations_(animations) {
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
  if (random_number == 0) {
    // чтобы свинка не остановилась
    if (moveVector_.x + 2 * kSpeed >= 1) {
      moveVector_.x += 2 * kSpeed;
    }
  }
  if (random_number == 1) {
    moveVector_.x *= -1;
  } else if (random_number == 2) {
    // чтобы свинка не остановилась
    if (moveVector_.x - 2 * kSpeed >= 1) {
      moveVector_.x -= 2 * kSpeed;
    }
  }
}

void FreePig::Draw(QPainter& painter) const {
  if (current_side == Side::LEFT) {
    painter.drawPixmap(xPos(), yPos(),
                       bBox_.width_, bBox_.height_,
                       animations_->run_l.CurrentFrame());
  } else {
    painter.drawPixmap(xPos(), yPos(),
                       bBox_.width_, bBox_.height_,
                       animations_->run_r.CurrentFrame());
  }
}

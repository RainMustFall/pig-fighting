#include "./free_pig.h"

#include <QDebug>

#include "./moving_object.h"
#include "./constants.h"

FreePig::FreePig(int x, int y, const PigAnimationStorage* animations)
    : MovingObject(x, y, kPigSize, kPigSize), animations_(animations) {
  move_vector_.x = -1.0;
}

void FreePig::SetX(double x) { position_.x = x; }
void FreePig::SetY(double y) { position_.y = y; }

void FreePig::PositionGenerate() {
  int random_number = rand() % 1000;
  if (random_number == 0) {
    if (move_vector_.x + 2 * kSpeed >= 1) {
      move_vector_.x += 2 * kSpeed;
    }
  }
  if (random_number == 1) {
    move_vector_.x *= -1;
  } else if (random_number == 2) {
    if (move_vector_.x - 2 * kSpeed >= 1) {
      move_vector_.x -= 2 * kSpeed;
    }
  }
}

void FreePig::Draw(QPainter* painter) const {
  if (current_side_ == utils::Side::LEFT) {
    painter->drawPixmap(xPos(), yPos(), bBox_.width_, bBox_.height_,
                       animations_->run_l.CurrentFrame());
  } else {
    painter->drawPixmap(xPos(), yPos(), bBox_.width_, bBox_.height_,
                       animations_->run_r.CurrentFrame());
  }
}

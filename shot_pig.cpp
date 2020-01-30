#include "./shot_pig.h"

#include <vector>

#include "./constants.h"
#include "./person.h"

ShotPig::ShotPig(int x, int y, int direction, const Person* shooting_player,
                 const PigAnimationStorage* animations)
    : MovingObject(x, y, kPigSize, kPigSize),
      shooting_player_(shooting_player),
      animations_(animations) {
  move_vector_.x = direction * kShotSpeed;
  move_vector_.y = 0;
}

const GameObject* ShotPig::PigHits(std::vector<Person>& persons,
                                   const std::vector<Ground>& ground) {
  for (auto& item : persons) {
    if (&item != shooting_player_) {
      if (Hits(&item)) {
        item.AccelerateX(move_vector_.x / 2);
        return &item;
      }
    }
  }

  for (const auto& item : ground) {
    if (Hits(&item)) {
      return &item;
    }
  }
  return nullptr;
}

void ShotPig::Draw(QPainter& painter) const {
  if (current_side_ == utils::Side::LEFT) {
    painter.drawPixmap(xPos(), yPos(), bBox_.width_, bBox_.height_,
                       animations_->fly_l.CurrentFrame());
  } else {
    painter.drawPixmap(xPos(), yPos(), bBox_.width_, bBox_.height_,
                       animations_->fly_r.CurrentFrame());
  }
}

bool ShotPig::IsOutOfScreen() {
  return (position_.x >= kScreenWidth) || (position_.x < -Width());
}

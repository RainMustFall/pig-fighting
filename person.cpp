#include "./person.h"

#include <QDebug>
#include <QSound>

#include <algorithm>

#include "./free_pig.h"
#include "./field_view.h"
#include "./constants.h"

Person::Person(int x, int y, const QString& animation_dir, int id,
               FieldController* controller)
    : MovingObject(x, y, kPersonHeight, kPersonWidth),
      name_(id),
      state_(utils::PersonState::FLYING),
      animations_(animation_dir),
      handle_keys_(id == 1 ? kFirstPlayerKeys : kSecondPlayerKeys),
      controller_(controller) {}

void Person::CatchPressedKey(int key) {
  if (key == handle_keys_.up_key) {
    up_pressed_ = true;
  } else if (key == handle_keys_.left_key) {
    left_pressed_ = true;
  } else if (key == handle_keys_.right_key) {
    right_pressed_ = true;
  } else if (key == handle_keys_.down_key) {
    down_pressed_ = true;
    if (current_platform_ != nullptr) {
      ignored_platform_ = current_platform_;
    } else {
      move_vector_.y += kDownAcceleration;
    }
  } else if (key == handle_keys_.shot_key && can_shoot_) {
    if (armed_) {
      ThrowPig();
    } else {
      controller_->GivePigsToPlayer(this);
    }
    can_shoot_ = false;
  }
}

void Person::CatchReleasedKey(int key) {
  if (key == handle_keys_.left_key) {
    left_pressed_ = false;
  } else if (key == handle_keys_.right_key) {
    right_pressed_ = false;
  } else if (key == handle_keys_.up_key) {
    up_pressed_ = false;
  } else if (key == handle_keys_.down_key) {
    down_pressed_ = false;
  } else if (key == handle_keys_.shot_key) {
    can_shoot_ = true;
  }
}

void Person::ThrowPig() {
  if (current_side_ == utils::Side::LEFT) {
    controller_->OnPigThrown(xPos() - kPigSize - 1,
                             yPos() + Height() - kPigSize - kPigHeight, -1,
                             this);
  } else {
    controller_->OnPigThrown(xPos() + Width() + 1,
                             yPos() + Height() - kPigSize - kPigHeight, 1,
                             this);
  }
  armed_ = false;
}

void Person::ProcessKeyboard() {
  if (left_pressed_) {
    if (last_hit_ != utils::HitType::RIGHT) {
      move_vector_.x -= kSpeed;
      move_vector_.x = std::max(-kSpeedLimit, move_vector_.x);
    }
  }

  if (right_pressed_) {
    if (last_hit_ != utils::HitType::LEFT) {
      move_vector_.x += kSpeed;
      move_vector_.x = std::min(kSpeedLimit, move_vector_.x);
    }
  }

  if (!left_pressed_ && !right_pressed_) {
    if (move_vector_.x < 0) {
      move_vector_.x += kSpeedReduce;
    } else if (move_vector_.x > 0) {
      move_vector_.x -= kSpeedReduce;
    }
  }

  if (up_pressed_) {
    if (current_platform_ != nullptr) {
      position_.y--;
      move_vector_.y = kJumpPower;
    }
  }
}

void Person::CatchPig() { armed_ = true; }

void Person::UpdateAnimation() {
  if (current_platform_ != nullptr) {
    if (left_pressed_ || right_pressed_) {
      state_ = utils::PersonState::RUNNING;
    } else {
      auto& animation = animations_.GetAnimation(armed_, state_, current_side_);
      if (animation.IsOnFirstFrame()) {
        state_ = utils::PersonState::STANDING;
      }
    }
  } else {
    ResetRunAnimation();
    state_ = utils::PersonState::FLYING;
  }

  auto& animation = animations_.GetAnimation(armed_, state_, current_side_);
  animation.NextFrame();
}

void Person::Draw(QPainter* painter) const {
  const auto& animation =
      animations_.GetAnimation(armed_, state_, current_side_);
  painter->drawPixmap(xPos(), yPos(), bBox_.width_, bBox_.height_,
                     animation.CurrentFrame());
}

void Person::DecreaseHealthLevel() {
  if (health_level_ > 1) {
    health_level_ -= kHealthDecrease;
  }

  if (health_level_ <= 0) {
    controller_->PlayerWins(name_);
  }
}

void Person::ResetRunAnimation() {
  animations_.run_l.GoToFirstFrame();
  animations_.run_r.GoToFirstFrame();
  animations_.run_l_pig.GoToFirstFrame();
  animations_.run_r_pig.GoToFirstFrame();
}

void Person::IncreaseHelthLevel() {
  if (health_level_ < kMaxHealthLevel) {
    ++health_level_;
  }

  if (health_level_ <= 0) {
    controller_->PlayerWins(name_);
  }
}

int Person::Health() const { return health_level_; }

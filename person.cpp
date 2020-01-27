#include "person.h"
#include "free_pig.h"
#include "field_view.h"
#include <QDebug>
#include <thread>
#include <QSound>

Person::Person(int x, int y, const QString& animation_dir, int id, FieldController* controller)
    : MovingObject (x, y, kPersonHeight, kPersonWidth),
      state(utils::PersonState::FLYING),
      animations_(animation_dir),
      handle_keys_(id == 1 ? kFirstPlayerKeys : kSecondPlayerKeys),
      name_(id),
      controller_(controller) {}

void Person::CatchPressedKey(int key) {
    if (key == handle_keys_.up_key) {
        Up_pressed = true;
    } else if (key == handle_keys_.left_key) {
        Left_pressed = true;
    } else if (key == handle_keys_.right_key) {
        Right_pressed = true;
    } else if (key == handle_keys_.down_key) {
        Down_pressed = true;
        if (current_platform != nullptr) {
            ignored_platform = current_platform;
        } else {
            moveVector_.y += 10;
        }
    } else if (key == handle_keys_.shot_key && can_shoot_) {
        if (armed_) {
            ThrowPig();
        } else {
            controller_->givePigsToPlayer(this);
        }
        can_shoot_ = false;
    }
}

void Person::CatchReleasedKey(int key) {
    if (key == handle_keys_.left_key) {
        Left_pressed = false;
    } else if (key == handle_keys_.right_key) {
        Right_pressed = false;
    } else if (key == handle_keys_.up_key) {
        Up_pressed = false;
    } else if (key == handle_keys_.down_key) {
        Down_pressed = false;
    } else if (key == handle_keys_.shot_key) {
        can_shoot_ = true;
    }
}

void Person::ThrowPig() {
    if (current_side == utils::Side::LEFT) {
        controller_->onPigThrown(xPos() - kPigSize - 1,
                                 yPos() + Height() - kPigSize - kPigHeight, -1, this);
    } else {
        controller_->onPigThrown(xPos() + Width() + 1,
                                 yPos() + Height() - kPigSize - kPigHeight, 1, this);
    }
    armed_ = 0;
}

void Person::ProcessKeyboard() {
    if (Left_pressed) {
        if (last_hit != utils::HitType::RIGHT) {
            moveVector_.x -= kSpeed;
            moveVector_.x = std::max(-kSpeedLimit, moveVector_.x);
        }
    }

    if (Right_pressed) {
        if (last_hit != utils::HitType::LEFT) {
            moveVector_.x += kSpeed;
            moveVector_.x = std::min(kSpeedLimit, moveVector_.x);
        }
    }

    if (!Left_pressed && !Right_pressed) {
        if (moveVector_.x < 0) {
            moveVector_.x += kSpeedReduce;
        } else if (moveVector_.x > 0) {
            moveVector_.x -= kSpeedReduce;
        }
    }

    if (Up_pressed) {
        if (current_platform != nullptr) {
            position_.y--;
            moveVector_.y = kJumpPower;
        }
    }
}

void Person::CatchPig() {
    armed_ = 1;
}

void Person::UpdateAnimation() {
    if (current_platform != nullptr) {
        if (Left_pressed || Right_pressed) {
            state = utils::PersonState::RUNNING;
        } else {
            auto& animation = animations_.GetAnimation(armed_, state, current_side);
            if (animation.isOnFirstFrame()) {
                state = utils::PersonState::STANDING;
            }
        }
    } else {
        ResetRunAnimation();
        state = utils::PersonState::FLYING;
    }

    auto& animation = animations_.GetAnimation(armed_, state, current_side);
    animation.NextFrame();
}

void Person::Draw(QPainter& painter) const {
    const auto& animation = animations_.GetAnimation(armed_, state, current_side);
    painter.drawPixmap(xPos(), yPos(),
                       bBox_.width_, bBox_.height_,
                       animation.CurrentFrame());
}


void Person::DecreaseHealthLevel(){
    if (health_level_ > 1){
        health_level_ -= kHealthDecrease;
    }

    if (health_level_ <= 0) {
        controller_->PlayerWins(name_);
    }
}

void Person::ResetRunAnimation() {
    animations_.run_l.goToFirstFrame();
    animations_.run_r.goToFirstFrame();
    animations_.run_l_pig.goToFirstFrame();
    animations_.run_r_pig.goToFirstFrame();
}

void Person::IncreaseHelthLevel(){
    if (health_level_ < 100){
        health_level_ += 1;
    }

    if (health_level_ <= 0) {
        controller_->PlayerWins(name_);
    }
}

int Person::Health() const {
    return health_level_;
}

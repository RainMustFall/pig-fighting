#include "person.h"
#include "freepig.h"
#include "mainwindow.h"
#include <QDebug>
#include <thread>
#include <QSound>

Person::Person(int x, int y, const QString& animation_dir, int id, FieldController* controller)
    : MovingObject (x, y, kPersonHeight, kPersonWidth),
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
    if (current_side == Side::LEFT) {
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
        if (last_hit != MovingObject::HitType::RIGHT) {
            moveVector_.x -= kSpeed;
            moveVector_.x = std::max(-kSpeedLimit, moveVector_.x);
        }
    }

    if (Right_pressed) {
        if (last_hit != MovingObject::HitType::LEFT) {
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
    qDebug() << "got it!";
}

void Person::UpdateAnimationUniversal(Animation& run_animation,
                                      Animation& stand_animation,
                                      Animation& fly_animation) {
    switch (state) {
    case utils::PersonState::RUNNING:
        run_animation.NextFrame();
        break;
    case utils::PersonState::STANDING:
        stand_animation.NextFrame();
        break;
    case utils::PersonState::FLYING:
        fly_animation.NextFrame();
        break;
    }
}

void Person::UpdateAnimation() {
    if (current_platform != nullptr) {
        if (Left_pressed || Right_pressed) {
            state = utils::PersonState::RUNNING;
        } else {
            if (current_side == Side::LEFT) {
                if (!armed_ && animations_.run_l.isOnFirstFrame()) {
                    state = utils::PersonState::STANDING;
                }
                if (armed_ && animations_.run_l_pig.isOnFirstFrame()) {
                    state = utils::PersonState::STANDING;
                }
            } else {
                if (!armed_ && animations_.run_r.isOnFirstFrame()) {
                    state = utils::PersonState::STANDING;
                }
                if (armed_ && animations_.run_r_pig.isOnFirstFrame()) {
                    state = utils::PersonState::STANDING;
                }
            }
        }
    } else {
        ResetRunAnimation();
        state = utils::PersonState::FLYING;
    }

    if (current_side == Side::LEFT) {
        if (armed_) {
            UpdateAnimationUniversal(animations_.run_l_pig,
                                     animations_.stand_l_pig,
                                     animations_.fly_l_pig);
        } else {
            UpdateAnimationUniversal(animations_.run_l,
                                     animations_.stand_l,
                                     animations_.fly_l);
        }
    } else {
        if (armed_) {
            UpdateAnimationUniversal(animations_.run_r_pig,
                                     animations_.stand_r_pig,
                                     animations_.fly_r_pig);
        } else {
            UpdateAnimationUniversal(animations_.run_r,
                                     animations_.stand_r,
                                     animations_.fly_r);
        }
    }
}

void Person::DrawUniversal(QPainter& painter,
                           const Animation& run_animation,
                           const Animation& stand_animation,
                           const Animation& fly_animation) const {
    switch (state) {
    case utils::PersonState::RUNNING:
        painter.drawPixmap(xPos(), yPos(),
                           bBox_.width_, bBox_.height_,
                           run_animation.CurrentFrame());
        break;
    case utils::PersonState::STANDING:
        painter.drawPixmap(xPos(), yPos(),
                           bBox_.width_, bBox_.height_,
                           stand_animation.CurrentFrame());
        break;
    case utils::PersonState::FLYING:
        painter.drawPixmap(xPos(), yPos(),
                           bBox_.width_, bBox_.height_,
                           fly_animation.CurrentFrame());
        break;
    }
}

void Person::Draw(QPainter& painter) const {
    if (current_side == Side::LEFT) {
        if (!armed_) {
            DrawUniversal(painter, animations_.run_l,
                          animations_.stand_l, animations_.fly_l);
        } else {
            DrawUniversal(painter, animations_.run_l_pig,
                          animations_.stand_l_pig, animations_.fly_l_pig);
        }
    } else {
        if (!armed_) {
            DrawUniversal(painter, animations_.run_r,
                          animations_.stand_r, animations_.fly_r);
        } else {
            DrawUniversal(painter, animations_.run_r_pig,
                          animations_.stand_r_pig, animations_.fly_r_pig);
        }
    }
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

void Person::PlayMusicHit() {
    auto player = []()
    {
        QSound::play("qrc:resources/sounds/pig_caught.wav");
    };
    std::thread thread(player);
}



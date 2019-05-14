#include "person.h"
#include "constants.h"
#include "freepig.h"
#include "mainwindow.h"
#include <QDebug>

Person::Person(int x, int y)
    : MovingObject (x, y, kPersonHeight, kPersonWidth),
      run_animation_l(":/resources/animations/Run.png", kPersonHeight, kPersonWidth, kPersonWidth, kPersonHeight),
      stand_animation_l(":/resources/animations/Stand.png", kPersonHeight, kPersonWidth, kPersonWidth, kPersonHeight),
      fly_animation_l(":/resources/animations/Fly.png", kPersonHeight, kPersonWidth, kPersonWidth, kPersonHeight),
      run_animation_r(Reflect(run_animation_l)),
      stand_animation_r(Reflect(stand_animation_l)),
      fly_animation_r(Reflect(fly_animation_l))
{
    qDebug() << "PERSON CONSTRUCTOR!";
}

void Person::CatchPressedKey(int key, int up_key, int left_key,
                             int down_key, int right_key) {
    if (key == up_key) {
        Up_pressed = true;
    } else if (key == left_key) {
        Left_pressed = true;
    } else if (key == right_key) {
        Right_pressed = true;
    } else if (key == down_key) {
        Down_pressed = true;
        if (current_platform != nullptr) {
            ignored_platform = current_platform;
        } else {
            moveVector_.y += 10;
        }
    }
}

std::list<FreePig>::iterator Person::HitsPig(std::list<FreePig>& pigs) {
    for ( std::list<FreePig>::iterator i = pigs.begin(); i != pigs.end(); i++ ) {
        auto item_obj = dynamic_cast<const GameObject&>(*i);

        if (Hits(item_obj)) {
            return i;
        }
    }
    return pigs.end();
}

void Person::CatchReleasedKey(int key, int up_key, int left_key,
                             int down_key, int right_key) {
    if (key == left_key) {
        Left_pressed = false;
    } else if (key == right_key) {
        Right_pressed = false;
    } else if (key == up_key) {
        Up_pressed = false;
    } else if (key == down_key) {
        Down_pressed = false;
    }
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

void Person::CatchPig(FreePig &pig) {
    armed_ = 1;
    qDebug() << "got it!";
}

void Person::UpdateAnimationUniversal(Animation& run_animation,
                                      Animation& stand_animation,
                                      Animation& fly_animation) {
    switch (state) {
    case State::RUNNING:
        run_animation.NextFrame();
        break;
    case State::STANDING:
        stand_animation.NextFrame();
        break;
    case State::FLYING:
        fly_animation.NextFrame();
        break;
    }
}

void Person::UpdateAnimation() {
    if (current_platform != nullptr) {
        if (Left_pressed || Right_pressed) {
            state = State::RUNNING;
        } else {
            state = State::STANDING;
        }
    } else {
        state = State::FLYING;
    }

    if (current_side == Side::LEFT) {
        UpdateAnimationUniversal(run_animation_l, stand_animation_l, fly_animation_l);
    } else {
        UpdateAnimationUniversal(run_animation_r, stand_animation_r, fly_animation_r);
    }
}

void Person::DrawUniversal(QPainter& painter,
                           const Animation& run_animation,
                           const Animation& stand_animation,
                           const Animation& fly_animation) const {
    switch (state) {
    case State::RUNNING:
        painter.drawPixmap(position_.x, position_.y,
                           bBox_.width_, bBox_.height_,
                           run_animation.CurrentFrame());
        break;
    case State::STANDING:
        painter.drawPixmap(position_.x, position_.y,
                           bBox_.width_, bBox_.height_,
                           stand_animation.CurrentFrame());
        break;
    case State::FLYING:
        painter.drawPixmap(position_.x, position_.y,
                           bBox_.width_, bBox_.height_,
                           fly_animation.CurrentFrame());
        break;
    }
}

void Person::Draw(QPainter& painter) const {
    if (current_side == Side::LEFT) {
        DrawUniversal(painter, run_animation_l,
                      stand_animation_l, fly_animation_l);
    } else {
        DrawUniversal(painter, run_animation_r,
                      stand_animation_r, fly_animation_r);
    }
}


void Person::DecreaseHealthLevel(){
    health_level -= kHealthDecrease;
    qDebug() << "Health--";
}

std::list<FreePig>::iterator Person::FindClosestFreePig(MainWindow& w) {
    //
    return w.free_pigs.begin();
}

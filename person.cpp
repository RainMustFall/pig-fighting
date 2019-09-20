#include "person.h"
#include "constants.h"
#include "freepig.h"
#include "mainwindow.h"
#include <QDebug>
#include <thread>
#include <QSound>

Person::Person(int x, int y, QString animation_dir)
    : MovingObject (x, y, kPersonHeight, kPersonWidth),
      name_(animation_dir[animation_dir.size()-1] == '1' ? 1 : 2)
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
    for (auto i = pigs.begin(); i != pigs.end(); ++i) {
        auto item_obj = dynamic_cast<const GameObject*>(&(*i));
        if (Hits(*item_obj)) {
            return i;
        }
    }
    return pigs.end();
}

void Person::CatchReleasedKey(int key, int up_key, int left_key,
                             int down_key, int right_key, int shot_key) {
    if (key == left_key) {
        Left_pressed = false;
    } else if (key == right_key) {
        Right_pressed = false;
    } else if (key == up_key) {
        Up_pressed = false;
    } else if (key == down_key) {
        Down_pressed = false;
    } else if (key == shot_key) {
        if (armed_) {
            ThrowPig();
        } else {
            controller_->givePigsToPlayer(this);
        }
    }
}

void Person::ThrowPig() {
    if (current_side == Side::LEFT) {
        ShotPig pig(position_.x - kPigSize - 1,
                    position_.y + Height() - kPigSize - kPigHeight, -1,
                    this, &pig_flying_l, &pig_flying_r);
    } else {
        ShotPig pig(position_.x + Width() + 1,
                    position_.y + Height() - kPigSize - kPigHeight, 1,
                    this, &pig_flying_l, &pig_flying_r);
    }
    controller_->onPigThrown(pig);
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
            if (current_side == Side::LEFT) {
                if (!armed_ && animations_.run_l.isOnFirstFrame()) {
                    state = State::STANDING;
                }
                if (armed_ && animations_.run_l_pig.isOnFirstFrame()) {
                    state = State::STANDING;
                }
            } else {
                if (!armed_ && animations_.run_r.isOnFirstFrame()) {
                    state = State::STANDING;
                }
                if (armed_ && animations_.run_r_pig.isOnFirstFrame()) {
                    state = State::STANDING;
                }
            }
        }
    } else {
        ResetRunAnimation();
        state = State::FLYING;
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
    case State::RUNNING:
        painter.drawPixmap(xPos(), yPos(),
                           bBox_.width_, bBox_.height_,
                           run_animation.CurrentFrame());
        break;
    case State::STANDING:
        painter.drawPixmap(xPos(), yPos(),
                           bBox_.width_, bBox_.height_,
                           stand_animation.CurrentFrame());
        break;
    case State::FLYING:
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
    if (health_level > 1){
        health_level -= kHealthDecrease;
    }
    qDebug() << "down" << health_level;
}

void Person::ResetRunAnimation() {
    animations_.run_l.goToFirstFrame();
    animations_.run_r.goToFirstFrame();
    animations_.run_l_pig.goToFirstFrame();
    animations_.run_r_pig.goToFirstFrame();
}

void Person::IncreaseHelthLevel(){
    if(health_level < 100){
    health_level += 1;
    }

    if (health_level <= 0) {
        emit PlayerWins(name_);
        /*if ( == 1) {
            Pause("Игрок 2 выиграл!");
        } else {
            Pause("Игрок 1 выиграл!");
        }
        killTimer(timer_id);
        is_start = true;*/
    }
}

void Person::PlayMusicHit() {
    //QSound::play("sounds/pig_caught.wav");
    /*auto player = []()
    {
        QSound::play("qrc:resources/sounds/pig_caught.wav");
    };
    std::thread thread(player);*/
    //h_player->play();
}

/*std::list<FreePig>::iterator Person::FindClosestFreePig(MainWindow& w) {
    //
    return w.free_pigs.begin();
}*/


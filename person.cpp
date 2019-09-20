#include "person.h"
#include "constants.h"
#include "freepig.h"
#include "mainwindow.h"
#include <QDebug>
#include <thread>
#include <QSound>

Person::Person(int x, int y, QString animation_dir)
    : MovingObject (x, y, kPersonHeight, kPersonWidth),
      run_animation_r(":/resources/animations/" + animation_dir + "/Run.png", 300, 180, kPersonWidth, kPersonHeight),
      stand_animation_r(":/resources/animations/" + animation_dir + "/Stand.png", 300, 180, kPersonWidth, kPersonHeight),
      fly_animation_r(":/resources/animations/" + animation_dir + "/Fly.png", 300, 180, kPersonWidth, kPersonHeight),
      run_animation_l(run_animation_r.returnReflectedCopy()),
      stand_animation_l(stand_animation_r.returnReflectedCopy()),
      fly_animation_l(fly_animation_r.returnReflectedCopy()),
      run_animation_r_pig(":/resources/animations/" + animation_dir + "/Run_pig.png", 300, 180, kPersonWidth, kPersonHeight),
      stand_animation_r_pig(":/resources/animations/" + animation_dir + "/Stand_pig.png", 300, 180, kPersonWidth, kPersonHeight),
      fly_animation_r_pig(":/resources/animations/" + animation_dir + "/Fly_pig.png", 300, 180, kPersonWidth, kPersonHeight),
      run_animation_l_pig(run_animation_r_pig.returnReflectedCopy()),
      stand_animation_l_pig(stand_animation_r_pig.returnReflectedCopy()),
      fly_animation_l_pig(fly_animation_r_pig.returnReflectedCopy()),
      m_player (new QMediaPlayer),
      m_playlist (new QMediaPlaylist),
      h_player (new QMediaPlayer),
      h_playlist (new QMediaPlaylist),
      name_(animation_dir[animation_dir.size()-1] == '1' ? 1 : 2)
{
    m_player->setVolume(100);
    h_player->setVolume(100);
    h_player->setPlaylist(h_playlist);
    h_playlist->addMedia(QUrl("qrc:resources/sounds/hit.mp3"));
    m_player->setPlaylist(m_playlist);
    m_playlist->addMedia(QUrl("qrc:resources/sounds/pig_caught.mp3"));
    m_playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
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

void Person::CatchPig(std::list<FreePig>& pigs) {
    for (auto pig = pigs.begin(); pig != pigs.end(); ++pig) {
        auto item_obj = dynamic_cast<const GameObject*>(&(*pig));
        if (Hits(*item_obj)) {
            pigs.erase(pig);
            controller_->onPigCaught();
            break;
        }
    }
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
                if (!armed_ && run_animation_l.isOnFirstFrame()) {
                    state = State::STANDING;
                }
                if (armed_ && run_animation_l_pig.isOnFirstFrame()) {
                    state = State::STANDING;
                }
            } else {
                if (!armed_ && run_animation_r.isOnFirstFrame()) {
                    state = State::STANDING;
                }
                if (armed_ && run_animation_r_pig.isOnFirstFrame()) {
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
            UpdateAnimationUniversal(run_animation_l_pig, stand_animation_l_pig, fly_animation_l_pig);
        } else {
            UpdateAnimationUniversal(run_animation_l, stand_animation_l, fly_animation_l);
        }
    } else {
        if (armed_) {
            UpdateAnimationUniversal(run_animation_r_pig, stand_animation_r_pig, fly_animation_r_pig);
        } else {
            UpdateAnimationUniversal(run_animation_r, stand_animation_r, fly_animation_r);
        }
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
        if (!armed_) {
            DrawUniversal(painter, run_animation_l,
                          stand_animation_l, fly_animation_l);
        } else {
            DrawUniversal(painter, run_animation_l_pig,
                          stand_animation_l_pig, fly_animation_l_pig);
        }
    } else {
        if (!armed_) {
            DrawUniversal(painter, run_animation_r,
                          stand_animation_r, fly_animation_r);
        } else {
            DrawUniversal(painter, run_animation_r_pig,
                          stand_animation_r_pig, fly_animation_r_pig);
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
    run_animation_l.goToFirstFrame();
    run_animation_r.goToFirstFrame();
    run_animation_l_pig.goToFirstFrame();
    run_animation_r_pig.goToFirstFrame();
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
void Person::PlayMusic() {
     //m_player->play();
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


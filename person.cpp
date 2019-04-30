#include "person.h"
#include "constants.h"
#include "freepig.h"
#include "mainwindow.h"
#include <QDebug>

Person::Person(int x, int y, int height, int width)
    : MovingObject (x, y, height, width),
      animation_("C:\\Users\\HP\\Desktop\\pig.png", 100, 10)
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

void Person::Draw(QPainter& painter) const {
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.drawPixmap(position_.x, position_.y,
                       bBox_.width_, bBox_.height_, animation_.CurrentFrame());
}

void Person::UpdateAnimation() {
    animation_.NextFrame();
}

std::list<FreePig>::iterator Person::FindClosestFreePig(MainWindow& w) {
    //
    return w.free_pigs.begin();
}

#include "person.h"
#include "constants.h"
#include "freepig.h"
#include "mainwindow.h"
#include <QDebug>

Person::Person(int x, int y, int height, int width)
    : MovingObject (x, y, height, width)

{
    qDebug() << "PERSON CONSTRUCTOR!";
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

std::vector<FreePig>::iterator Person::FindClosestFreePig(MainWindow& w) {
    //
    return w.free_pigs.begin();
}

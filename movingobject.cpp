#include "movingobject.h"
#include "constants.h"
#include <QDebug>

MovingObject::MovingObject(int x, int y, int width, int height)
    : GameObject (x, y, width, height) {}

void MovingObject::UpdatePosition() {
    position_.x += moveVector_.x;
    position_.y += moveVector_.y;
    if (moveVector_.x > 0) {
            current_side = Side::RIGHT;
    }
    if (moveVector_.x < 0) {
    current_side = Side::LEFT;
    }
 }

void MovingObject::ApplyPhysics() {
    if (current_platform != nullptr) {
        moveVector_.y = std::min(0.0, moveVector_.y);
    } else {
        moveVector_.y += kGravitation;
    }
}

void MovingObject::StabilizePosition(const Ground& ground) {
    HitType type = CheckHitType(ground);
    last_hit = type;

    if (type != HitType::UP) {
        qDebug() << static_cast<int>(type);
    }

    switch (type) {
        case HitType::DOWN:
            ignored_platform = &ground;
            break;
        case HitType::UP:
            moveVector_.y = 0;
            position_.y = ground.yPos() - Height();
            break;
        case HitType::LEFT:
            moveVector_.x *= -1;
            position_.x = ground.xPos() - Width();
            break;
        case HitType::RIGHT:
            moveVector_.x *= -1;
            position_.x = ground.xPos() + ground.Width();
            break;
    }
}

const Ground* MovingObject::HitsGround(const std::vector<Ground>& ground) {
    bool hits = false;
    for (const auto& item : ground) {
        auto item_obj = dynamic_cast<const GameObject&>(item);

        if (Hits(item_obj)) {
            hits = true;
            if (ignored_platform != &item) {
                ignored_platform = nullptr;
                StabilizePosition(item);

                // Если мы стоим сверху на платформе, то
                // возвращаем её адрес
                if (CheckHitType(item) == HitType::UP) {
                    return &item;
                } else {
                    return nullptr;
                }
            }
        }
    }

    // Если мы действительно ничего не коснулись,
    // значит, мы висели в воздухе, и
    // игнорируемую платформу можно сбросить.
    //
    // Если же мы дошли до конца цикла, но чего-то коснулись,
    // значит, мы коснулись той платформы, которую должны были
    // проигнорировать

    if (!hits) {
        ignored_platform = nullptr;
    }
    return nullptr;
}

// Лучше это не трогать и не вникать...
MovingObject::HitType MovingObject::CheckHitType(const Ground& ground) {
    if (abs(moveVector_.y) < 1e-5) {
        return HitType::UP;
    }

    if (abs(moveVector_.x) < 1e-5) {
        if (moveVector_.y < 0) {
            return HitType::DOWN;
        } else {
            return HitType::UP;
        }
    }

    double y_hit_time, x_hit_time;
    if (moveVector_.y > 0) {
        y_hit_time = (ground.yPos() - yPos() - Height()) / moveVector_.y;
    } else {
        y_hit_time = (ground.yPos() + ground.Height() - yPos()) / moveVector_.y;
    }

    if (moveVector_.x > 0) {
        x_hit_time = (ground.xPos() - xPos() - Width()) / moveVector_.x;
    } else {
        x_hit_time = (ground.xPos() + ground.Width() - xPos()) / moveVector_.x;
    }

    if (y_hit_time > 0) {
        if (moveVector_.x > 0) {
            return HitType::LEFT;
        } else {
            return HitType::RIGHT;
        }
    }

    if (x_hit_time > 0) {
        if (moveVector_.y > 0) {
            return HitType::UP;
        } else {
            return HitType::DOWN;
        }
    }

    if (y_hit_time > x_hit_time) {
        if (moveVector_.y < 0) {
            return HitType::DOWN;
        } else {
            return HitType::UP;
        }
    } else {
        if (moveVector_.x < 0) {
            return HitType::RIGHT;
        } else {
            return HitType::LEFT;
        }
    }
}


double MovingObject::GetMoveVectorX() const {
    return moveVector_.x;
}

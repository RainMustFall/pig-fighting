#include "./moving_object.h"

#include <QDebug>

#include <vector>
#include <algorithm>

#include "./constants.h"

MovingObject::MovingObject(int x, int y, int width, int height)
    : GameObject(x, y, width, height) {}

void MovingObject::UpdatePosition() {
  position_.x += move_vector_.x;
  position_.y += move_vector_.y;

  if (move_vector_.x > 0) {
    current_side_ = utils::Side::RIGHT;
  } else if (move_vector_.x < 0) {
    current_side_ = utils::Side::LEFT;
  }
}

void MovingObject::ApplyPhysics() {
  if (current_platform_ != nullptr) {
    move_vector_.y = std::min(0.0, move_vector_.y);
  } else {
    move_vector_.y += kGravitation;
  }
}

void MovingObject::StabilizePosition(const Ground& ground) {
  utils::HitType type = CheckHitType(ground);
  last_hit_ = type;

  switch (type) {
    case utils::HitType::DOWN:
      ignored_platform_ = &ground;
      break;
    case utils::HitType::UP:
      move_vector_.y = 0;
      position_.y = ground.yPos() - Height();
      break;
    case utils::HitType::LEFT:
      move_vector_.x *= -1;
      position_.x = ground.xPos() - Width();
      break;
    case utils::HitType::RIGHT:
      move_vector_.x *= -1;
      position_.x = ground.xPos() + ground.Width();
      break;
  }
}

const Ground* MovingObject::HitsGround(const std::vector<Ground>& ground) {
  bool hits = false;
  for (const auto& item : ground) {
    auto item_obj = dynamic_cast<const GameObject*>(&item);

    if (Hits(item_obj)) {
      hits = true;
      if (ignored_platform_ != &item) {
        ignored_platform_ = nullptr;
        StabilizePosition(item);

        if (CheckHitType(item) == utils::HitType::UP) {
          return &item;
        }
        return nullptr;
      }
    }
  }

  // If we really didn't touch anything, it means we
  // were hanging in the air and the platform
  // that was being ignored could be reset.
  //
  // If we have reached the end of the cycle, but have
  // touched something, then we have touched the platform
  // that should have been ignored.

  if (!hits) {
    ignored_platform_ = nullptr;
  }
  return nullptr;
}

utils::HitType MovingObject::CheckHitType(const Ground& ground) {
  if (std::abs(move_vector_.y) < kEps) {
    return utils::HitType::UP;
  }

  if (std::abs(move_vector_.x) < kEps) {
    if (move_vector_.y < 0) {
      return utils::HitType::DOWN;
    }
    return utils::HitType::UP;
  }

  double y_hit_time;
  double x_hit_time;
  if (move_vector_.y > 0) {
    y_hit_time = (ground.yPos() - yPos() - Height()) / move_vector_.y;
  } else {
    y_hit_time = (ground.yPos() + ground.Height() - yPos()) / move_vector_.y;
  }

  if (move_vector_.x > 0) {
    x_hit_time = (ground.xPos() - xPos() - Width()) / move_vector_.x;
  } else {
    x_hit_time = (ground.xPos() + ground.Width() - xPos()) / move_vector_.x;
  }

  if (y_hit_time > 0) {
    if (move_vector_.x > 0) {
      return utils::HitType::LEFT;
    }
    return utils::HitType::RIGHT;
  }

  if (x_hit_time > 0) {
    if (move_vector_.y > 0) {
      return utils::HitType::UP;
    }
    return utils::HitType::DOWN;
  }

  if (y_hit_time > x_hit_time) {
    if (move_vector_.y < 0) {
      return utils::HitType::DOWN;
    }
    return utils::HitType::UP;
  }
  if (move_vector_.x < 0) {
    return utils::HitType::RIGHT;
  }
  return utils::HitType::LEFT;
}

double MovingObject::GetMoveVectorX() const { return move_vector_.x; }

double MovingObject::GetMoveVectorY() const { return move_vector_.y; }

void MovingObject::AccelerateX(double delta) { move_vector_.x += delta; }

void MovingObject::CheckBoundaries() {
  if (position_.x >= kScreenWidth && move_vector_.x > 0) {
    position_.x = -Width();
  } else if (position_.x < -Width() && move_vector_.x < 0) {
    position_.x = kScreenWidth;
  }

  if (position_.y >= kScreenHeight) {
    position_.y = -Height();
  }
}

void MovingObject::UpdatePlatform(const std::vector<Ground>& ground) {
  current_platform_ = HitsGround(ground);
}

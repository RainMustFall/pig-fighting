#include "health_field.h"

HealthField::HealthField(int x, int y, int height, int width)
    : position_{static_cast<double>(x), static_cast<double>(y)},
      bBox_{height, width} {
}

void HealthField::Draw(QPainter& painter) const {
    painter.drawRect(position_.x, position_.y, bBox_.width_, bBox_.height_);
}

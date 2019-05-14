#include "health_field.h"
#include <QColor>
#include <QDebug>

HealthField::HealthField(int x, int y, int level)
    : position_{static_cast<double>(x), static_cast<double>(y)},
      level(level) {
}

void HealthField::Draw(QPainter& painter) const {
    painter.drawRect(position_.x, position_.y, bBox_.width_, bBox_.height_);
    painter.drawRect(position_.x + 1, position_.y + 1, level - 1 ,bBox_.height_ - 1);
    painter.fillRect(position_.x + 1, position_.y + 1,
                     level - 1 ,bBox_.height_ - 1,  Qt::green);
}

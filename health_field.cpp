#include "health_field.h"
#include "person.h"
#include <QColor>
#include <QDebug>

HealthField::HealthField(int x, int y, int level, Person* player)
    : position_{static_cast<double>(x), static_cast<double>(y)},
      level(level),
      player_ptr(player){
}

void HealthField::Draw(QPainter& painter) {

    level = player_ptr->health_level;

    painter.drawRect(position_.x, position_.y, bBox_.width_, bBox_.height_);
    painter.drawRect(position_.x + 1, position_.y + 1, level - 1 ,bBox_.height_ - 1);
    painter.fillRect(position_.x + 1, position_.y + 1,
                     level - 1 ,bBox_.height_ - 1,  Qt::green);
}

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
//    int red = 250 * (100 - level) / 100;
//    int green = 250 - red;
//    QColor color(red, green, 0);
    QColor color;
    if (level > 75){
        color = Qt::green;
    } else if (level > 50) {
        color = Qt::yellow;
    } else if (level > 25) {
        color = QColor(250,100,0);
    }else if (level > 5) {
        color = Qt::red;
    }
    painter.drawRect(position_.x, position_.y, bBox_.width_, bBox_.height_);
    painter.drawRect(position_.x + 1, position_.y + 1, level - 1 ,bBox_.height_ - 1);
    painter.fillRect(position_.x + 1, position_.y + 1,
                     level - 1 ,bBox_.height_ - 1,  color);
}

#include "./health_field.h"

#include <QColor>
#include <QDebug>

#include "./person.h"
#include "source_code/utils/constants.h"

HealthField::HealthField(int x, int y, Person* player)
    : GameObject(x, y, kHealthBarHeight, kMaxHealthLevel),
      player_ptr_(player) {}

void HealthField::Draw(QPainter* painter) const {
  int level = player_ptr_->Health();
  QColor color;
  if (level > kGreenBarThreshold) {
    color = Qt::green;
  } else if (level > kYellowBarThreshold) {
    color = Qt::yellow;
  } else if (level > kOrangeBarThreshold) {
    color = kOrangeColor;
  } else if (level > kRedBarThreshold) {
    color = Qt::red;
  }

  painter->drawRect(GetX(), GetY(), level, bBox_.height_);
  painter->fillRect(GetX(), GetY(), level, bBox_.height_, color);
}

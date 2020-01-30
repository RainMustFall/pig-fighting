#include "./health_field.h"

#include <QColor>
#include <QDebug>

#include "./person.h"

HealthField::HealthField(int x, int y, Person* player)
    : GameObject(x, y, 20, 100), player_ptr_(player) {}

void HealthField::Draw(QPainter* painter) const {
  int level = player_ptr_->Health();
  QColor color;
  if (level > 75) {
    color = Qt::green;
  } else if (level > 50) {
    color = Qt::yellow;
  } else if (level > 25) {
    color = QColor(250, 100, 0);
  } else if (level > 5) {
    color = Qt::red;
  }

  painter->drawRect(xPos(), yPos(), bBox_.width_, bBox_.height_);
  painter->drawRect(xPos() + 1, yPos() + 1, level - 1, bBox_.height_ - 1);
  painter->fillRect(xPos() + 1, yPos() + 1, level - 1, bBox_.height_ - 1, color);
}

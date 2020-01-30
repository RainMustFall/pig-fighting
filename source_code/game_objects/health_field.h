#ifndef HEALTH_FIELD_H_
#define HEALTH_FIELD_H_

#include <QPainter>

#include "./person.h"

class HealthField : public GameObject {
 public:
  HealthField(int x, int y, Person* player);
  void Draw(QPainter* painter) const override;

 private:
  const Person* player_ptr_;
};

#endif  // HEALTH_FIELD_H_

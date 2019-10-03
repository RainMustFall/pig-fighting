#ifndef HEALTH_FIELD_H
#define HEALTH_FIELD_H

#include <QPainter>
#include <person.h>

class HealthField : public GameObject {
public:
    HealthField(int x, int y, int level, Person* player);
    void Draw(QPainter& painter) const override;
private:
    Person* player_ptr;
    int level = 100;
};

#endif // HEALTH_FIELD_H

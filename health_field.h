#ifndef HEALTH_FIELD_H
#define HEALTH_FIELD_H

#include <QPainter>

struct Point_ {
    double x;
    double y;
};

struct BoundingBox_ {
    int height_ = 20;
    int width_ = 100;
};

class HealthField
{
public:
    HealthField(int x, int y, int level);
    Point_ position_;
    BoundingBox_ bBox_;

    void Draw(QPainter& painter) const;

    int level = 100;
};

#endif // HEALTH_FIELD_H

#ifndef HEALTH_FIELD_H
#define HEALTH_FIELD_H

#include <QPainter>

struct Point_ {
    double x;
    double y;
};

struct BoundingBox_ {
    int height_;
    int width_;
};

class HealthField
{
public:
    HealthField(int x, int y, int height, int width);
    Point_ position_;
    BoundingBox_ bBox_;

    void Draw(QPainter& painter) const;
};

#endif // HEALTH_FIELD_H

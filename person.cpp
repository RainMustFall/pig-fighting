#include "person.h"
#include <QDebug>

Person::Person(int x, int y, int height, int width)
    : GameObject (x, y, height, width)

{
    qDebug() << "PERSON CONSTRUCTOR!";
}


void Person::UpdatePosition() {
    position_.x += moveVector_.x;
    position_.y += moveVector_.y;
}

bool Person::Hits(const GameObject& obj) const {
    int max_y = std::max(yPos() + Height(), obj.yPos() + obj.Height());
    int min_y = std::min(yPos(), obj.yPos());
    int max_x = std::max(xPos() + Width(), obj.xPos() + obj.Width());
    int min_x = std::min(xPos(), obj.xPos());

    return (max_y - min_y <= Height() + obj.Height()) &&
           (max_x - min_x <= Width() + obj.Width());
}

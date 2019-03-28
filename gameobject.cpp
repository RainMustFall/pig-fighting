#include "gameobject.h"
#include <QDebug>

GameObject::GameObject(int x, int y, int height, int width)
    : position_{x, y},
      moveVector_{0, 0},
      bBox_{height, width}

{
    qDebug() << "MAIN CONSTRUCTOR!";
}

void GameObject::Draw(QPainter& painter) const {
    painter.drawRect(position_.x, position_.y,
                     bBox_.width_, bBox_.height_);
}

int GameObject::Width() const {
    return bBox_.width_;
}

int GameObject::Height() const {
    return bBox_.height_;
}

int GameObject::xPos() const {
    return position_.x;
}

int GameObject::yPos() const {
    return position_.y;
}



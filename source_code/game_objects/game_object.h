#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#include <QPainter>
#include <QMouseEvent>

#include "source_code/utils/utils.h"

// An abstract class of object in the game that stores
// the most basic information, such as position, length, width.
class GameObject {
 public:
  friend class MainWindow;

  GameObject(int x, int y, int height, int width);
  virtual ~GameObject() = default;

  virtual void Draw(QPainter* painter) const = 0;

  int Width() const;
  int Height() const;
  int GetX() const;
  int GetY() const;

  virtual bool Hits(const GameObject* obj) const;
  void UpdatePosition();

 protected:
  utils::Point position_;
  utils::BoundingBox bBox_;
};

#endif  // GAME_OBJECT_H_

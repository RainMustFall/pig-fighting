#ifndef GROUND_H_
#define GROUND_H_

#include "./game_object.h"

class Ground : public GameObject {
 public:
  Ground(int x, int y, int height, int width,
         utils::TextureType type = utils::TextureType::GRASS);

  void Draw(QPainter* painter) const override;

 private:
  QPixmap texture_;
};

#endif  // GROUND_H_

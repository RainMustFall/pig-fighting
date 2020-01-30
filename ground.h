#ifndef GROUND_H
#define GROUND_H
#include "game_object.h"

class Ground : public GameObject {
public:
    Ground(int x, int y, int height, int width,
           utils::TextureType type = utils::TextureType::GRASS);

    void Draw(QPainter& painter) const override;

private:
    QPixmap texture_;
};

#endif // GROUND_H

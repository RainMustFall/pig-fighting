#ifndef GROUND_H
#define GROUND_H
#include "gameobject.h"

enum class TextureType {
    GRASS = 0,
    SAND = 1,
    CAVE = 2,
    SNOW = 3
};

struct TexturePack {
    TexturePack(const QString path);

    QPixmap left_block;
    QPixmap middle_block;
    QPixmap right_block;
};

class Ground : public GameObject {
public:
    Ground(int x, int y, int height, int width,
           TextureType type = TextureType::GRASS);
    void Draw(QPainter& painter) const override;
    QPixmap texture;
};

#endif // GROUND_H

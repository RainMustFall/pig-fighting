#ifndef UTILS_H
#define UTILS_H

#include "QPixmap"

namespace utils {

struct Point {
    double x;
    double y;
};

struct BoundingBox {
    int height_;
    int width_;
};

enum class PersonState {
    RUNNING = 0,
    STANDING = 1,
    FLYING = 2
};

struct HandleKeys {
    int up_key;
    int left_key;
    int down_key;
    int right_key;
    int shot_key;
};

enum class Sounds {
    Take,
    Throw,
    Hit
};

enum class TextureType {
    GRASS = 0,
    SAND = 1,
    CAVE = 2,
    SNOW = 3
};

struct TexturePack {
    TexturePack(const QString& path);

    QPixmap left_block;
    QPixmap middle_block;
    QPixmap right_block;
};

enum class Side {
    RIGHT = 0,
    LEFT = 1
};

enum class HitType {
    UP,  // Сверху на платформе
    DOWN,  // Снизу под ней
    LEFT,
    RIGHT
};

}

#endif // UTILS_H

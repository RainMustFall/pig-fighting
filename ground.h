#ifndef GROUND_H
#define GROUND_H
#include "gameobject.h"

class Ground : public GameObject {
public:
    Ground(int x, int y, int height, int width);
};

#endif // GROUND_H

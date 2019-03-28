#include "ground.h"
#include <QDebug>

Ground::Ground(int x, int y, int height, int width)
    : GameObject (x, y, height, width)

{
    qDebug() << "GROUND CONSTRUCTOR!";
}

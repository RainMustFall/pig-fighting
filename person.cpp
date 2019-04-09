#include "person.h"
#include <QDebug>

Person::Person(int x, int y, int height, int width)
    : GameObject (x, y, height, width)

{
    qDebug() << "PERSON CONSTRUCTOR!";
}

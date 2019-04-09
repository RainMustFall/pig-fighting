#ifndef CONSTANTS_H
#define CONSTANTS_H

// Все константы лучше хранить в отдельном файле, чтобы, если мы захотим поменять
// какие-то параметры, нам не пришлось просматривать весь код, а можно было менять
// всё в одном месте.

const double kJumpPower = -12;
const double kSPower = 10;  // Сила "рывка" вниз по нажатию S
const double kSpeed = 0.5;
const double kGravitation = 0.4;
const double kSpeedLimit = 5;
const double kSpeedReduce = 0.25;

#endif // CONSTANTS_H
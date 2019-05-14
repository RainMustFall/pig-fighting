#ifndef CONSTANTS_H
#define CONSTANTS_H
#include "animation.h"

// Все константы лучше хранить в отдельном файле, чтобы, если мы захотим поменять
// какие-то параметры, нам не пришлось просматривать весь код, а можно было менять
// всё в одном месте.

const int kScreenWidth = 1440;
const int kScreenHeight = 810;

const int kPersonHeight = 100;
const int kPersonWidth = 60;
const int kPigSize = 70;

const double kJumpPower = -14;
const double kSpeed = 0.5;
const double kGravitation = 0.4;
const double kSpeedLimit = 5;
const double kSpeedReduce = 0.25;
const double kShotSpeed = 10.5;
// Высота полёта свиньи над уровнем земли
const double kPigHeight = 15;

//снижения здоровья
const int kHealthDecrease = 5;

#endif // CONSTANTS_H

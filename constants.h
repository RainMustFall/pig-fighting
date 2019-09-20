#ifndef CONSTANTS_H
#define CONSTANTS_H

// Все константы лучше хранить в отдельном файле, чтобы, если мы захотим поменять
// какие-то параметры, нам не пришлось просматривать весь код, а можно было менять
// всё в одном месте.

const int kScreenWidth = 1440;
const int kScreenHeight = 810;

const int kPigCount = 8;

const int kPersonHeight = 110;
const int kPersonWidth = 66;
const int kPigSize = 55;

const double kJumpPower = -14;
const double kSpeed = 0.5;
const double kGravitation = 0.4;
const double kSpeedLimit = 5;
const double kSpeedReduce = 0.125;
const double kShotSpeed = 10.5;
// Высота полёта свиньи над уровнем земли
const double kPigHeight = 15;

//снижения здоровья
const int kHealthDecrease = 20;
//время, через которое здоровье снижается
const int kTimeHealthUp = 500;

const int kPigGeneraingFrequency = 500;

#endif // CONSTANTS_H

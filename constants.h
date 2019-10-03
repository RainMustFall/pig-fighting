#ifndef CONSTANTS_H
#define CONSTANTS_H

// Все константы лучше хранить в отдельном файле, чтобы, если мы захотим поменять
// какие-то параметры, нам не пришлось просматривать весь код, а можно было менять
// всё в одном месте.

#include <QString>

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
const double kEps = 1e-5;

const QString kAnimationPath = ":/resources/animations/";
const QString kTexturesPath = ":/resources/textures/";

struct HandleKeys {
    int up_key;
    int left_key;
    int down_key;
    int right_key;
    int shot_key;
};

const HandleKeys kFirstPlayerKeys = {Qt::Key_W,
                               Qt::Key_A,
                               Qt::Key_S,
                               Qt::Key_D,
                              Qt::Key_Space};

const HandleKeys kSecondPlayerKeys = {Qt::Key_Up,
                               Qt::Key_Left,
                               Qt::Key_Down,
                               Qt::Key_Right,
                              Qt::Key_Shift};

const QString kBgPath = ":/resources/textures/background.png";

#endif // CONSTANTS_H

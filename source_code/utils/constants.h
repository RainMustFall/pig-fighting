#ifndef CONSTANTS_H_
#define CONSTANTS_H_

// It is better to store all the constants in a separate
// file, so that if we want to change some parameters, we
// do not have to view all the code, but we can change
// everything in one place.

#include <QString>

#include "./utils.h"

const int kTimerInterval = 9;
const int kScreenWidth = 1440;
const int kScreenHeight = 810;
const int kPersonImageHeight = 300;
const int kPersonImageWidth = 180;
const int kPigImageHeight = 400;
const int kPigImageWidth = 400;
const int kHintIndentX = 10;
const int kHintIndentY = kScreenHeight - 180;
const int kHintWidth = 345;
const int kHintHeight = 122;

const int kMaxHealthLevel = 100;
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
const double kDownAcceleration = 10;

// Pig flight altitude
const int kPigHeight = 15;

// Color thresholds for health bars
const int kGreenBarThreshold = 75;
const int kYellowBarThreshold = 50;
const int kOrangeBarThreshold = 25;
const int kRedBarThreshold = 5;

const int kHealthBarIndent = 10;
const int kHealthBarHeight = 20;
const int kHealthDecrease = 20;
const int kTimeHealthUp = 500;

const QColor kOrangeColor = QColor(250, 100, 0);

const int kHintShowThreshold = 200;
const int kPigGeneraingFrequency = 500;
const int kPigTurningFrequency = 1000;
const double kEps = 1e-5;

const QString kAnimationPath = ":/resources/animations/";
const QString kTexturesPath = ":/resources/textures/";
const QString kMapsPath = ":/resources/maps/";
const QString kIconPath = ":/resources/textures/icon.ico";

const utils::HandleKeys kFirstPlayerKeys = {Qt::Key_W, Qt::Key_A, Qt::Key_S,
                                            Qt::Key_D, Qt::Key_Space};

const utils::HandleKeys kSecondPlayerKeys = {
    Qt::Key_Up, Qt::Key_Left, Qt::Key_Down, Qt::Key_Right, Qt::Key_Shift};

const QString kBgPath = ":/resources/textures/background.png";
const QString kDefaultMap = ":/resources/maps/Map 1.json";

#endif  // CONSTANTS_H_

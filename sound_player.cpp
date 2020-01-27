#include "sound_player.h"
#include <QSound>

QSound* SoundPlayer::pig_fly = new QSound(":/resources/sounds/pig_caught.wav");
QSound* SoundPlayer::hit = new QSound(":/resources/sounds/hit2.wav");
QSound* SoundPlayer::take = new QSound(":/resources/sounds/pig_caught.wav");

SoundPlayer::SoundPlayer(utils::Sounds sound)
    : sound_(sound) {}

void SoundPlayer::run() {
  switch (sound_) {
    case utils::Sounds::Hit:
      hit->stop();
      hit->play();
      break;
    case utils::Sounds::Take:
      take->stop();
      take->play();
      break;
    case utils::Sounds::Throw:
      pig_fly->stop();
      pig_fly->play();
      break;
  }

  exec();
}

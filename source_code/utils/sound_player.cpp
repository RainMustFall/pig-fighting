#include "./sound_player.h"

#include <QSound>
#include <QDebug>

SoundPlayer::SoundPlayer(QSound* sound) : sound_(sound) {}

void SoundPlayer::run() {
  sound_->stop();
  sound_->play();
}

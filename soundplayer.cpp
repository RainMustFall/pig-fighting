#include "soundplayer.h"
#include <QSound>

SoundPlayer::SoundPlayer(Sounds sound, QSound* hitp)
    : pig_fly(hitp),
      hit(hitp),
      take(hitp),
      sound_(sound) {}

void SoundPlayer::run() {
  switch (sound_) {
    case Sounds::Hit:
      hit->play();
      break;
    case Sounds::Take:
      take->play();
      break;
    case Sounds::Throw:
      pig_fly->play();
      break;
  }

  exec();
}

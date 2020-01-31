#ifndef SOUND_PLAYER_H_
#define SOUND_PLAYER_H_

#include <QSound>
#include <QThread>

#include "./utils.h"

class SoundPlayer/* : public QThread*/ {
 public:
  static QSound* pig_fly;
  static QSound* hit;
  static QSound* take;
};

#endif  // SOUND_PLAYER_H_

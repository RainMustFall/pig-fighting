#ifndef SOUND_PLAYER_H_
#define SOUND_PLAYER_H_

#include <QSound>
#include <QThread>

#include "./utils.h"

class SoundPlayer : public QThread {
 public:
  explicit SoundPlayer(QSound* sound);

  void run() override;

 private:
  QSound* sound_;
};

#endif  // SOUND_PLAYER_H_

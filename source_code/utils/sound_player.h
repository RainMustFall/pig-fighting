#ifndef SOUND_PLAYER_H_
#define SOUND_PLAYER_H_

#include <QSound>
#include <QThread>

#include "./utils.h"

class SoundPlayer : public QThread {
 public:
  explicit SoundPlayer(utils::Sounds sound);

  void run() override;

  static QSound* pig_fly;
  static QSound* hit;
  static QSound* take;

 private:
  utils::Sounds sound_;
};

#endif  // SOUND_PLAYER_H_

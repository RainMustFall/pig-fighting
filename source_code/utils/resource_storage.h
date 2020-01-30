#ifndef RESOURCE_STORAGE_H_
#define RESOURCE_STORAGE_H_

#include <QSound>

#include "./animation.h"
#include "./utils.h"
#include "source_code/game_objects/moving_object.h"

struct PigAnimationStorage {
  PigAnimationStorage();

  Animation run_l;
  Animation run_r;

  Animation fly_l;
  Animation fly_r;

  QSound* hit_sound{};
};

struct PersonAnimationStorage {
  explicit PersonAnimationStorage(const QString& animation_dir);

  Animation run_r;
  Animation stand_r;
  Animation fly_r;

  Animation run_l;
  Animation stand_l;
  Animation fly_l;

  Animation run_r_pig;
  Animation stand_r_pig;
  Animation fly_r_pig;

  Animation run_l_pig;
  Animation stand_l_pig;
  Animation fly_l_pig;

  Animation& GetAnimation(bool armed, utils::PersonState state,
                          utils::Side side);
  const Animation& GetAnimation(bool armed, utils::PersonState state,
                                utils::Side side) const;
};

#endif  // RESOURCE_STORAGE_H_

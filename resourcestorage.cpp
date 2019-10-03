#include "resourcestorage.h"
#include "constants.h"
#include <QString>

Animation createPersonAnimation(const QString& file) {
    return Animation(kAnimationPath + file,
                     300, 180, kPersonWidth, kPersonHeight);
}

Animation createPigAnimation(const QString& file) {
    return Animation(kAnimationPath + file,
                     400, 400, kPigSize, kPigSize);
}

PigAnimationStorage::PigAnimationStorage()
    : run_l(createPigAnimation("pig_running.png")),
      run_r(run_l.returnReflectedCopy()),
      fly_l(createPigAnimation("pig_flying.png")),
      fly_r(fly_l.returnReflectedCopy()) {}

PersonAnimationStorage::PersonAnimationStorage(const QString& animation_dir)
    : run_r(createPersonAnimation(animation_dir + "/Run.png")),
      stand_r(createPersonAnimation(animation_dir + "/Stand.png")),
      fly_r(createPersonAnimation(animation_dir + "/Fly.png")),

      run_l(run_r.returnReflectedCopy()),
      stand_l(stand_r.returnReflectedCopy()),
      fly_l(fly_r.returnReflectedCopy()),

      run_r_pig(createPersonAnimation(animation_dir + "/Run_pig.png")),
      stand_r_pig(createPersonAnimation(animation_dir + "/Stand_pig.png")),
      fly_r_pig(createPersonAnimation(animation_dir + "/Fly_pig.png")),

      run_l_pig(run_r_pig.returnReflectedCopy()),
      stand_l_pig(stand_r_pig.returnReflectedCopy()),
      fly_l_pig(fly_r_pig.returnReflectedCopy()) {}

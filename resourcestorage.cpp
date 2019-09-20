#include "resourcestorage.h"
#include "constants.h"
#include <QString>

QString animation_dir = "";

ResourceStorage::ResourceStorage()
    : pig_running_l(":/resources/animations/pig_running.png", 400, 400, kPigSize, kPigSize),
      pig_running_r(pig_running_l.returnReflectedCopy()),
      pig_flying_l(":/resources/animations/pig_flying.png", 400, 400, kPigSize, kPigSize),
      pig_flying_r(pig_flying_l.returnReflectedCopy()),
      run_animation_r(":/resources/animations/" + animation_dir + "/Run.png", 300, 180, kPersonWidth, kPersonHeight),
      stand_animation_r(":/resources/animations/" + animation_dir + "/Stand.png", 300, 180, kPersonWidth, kPersonHeight),
      fly_animation_r(":/resources/animations/" + animation_dir + "/Fly.png", 300, 180, kPersonWidth, kPersonHeight),
      run_animation_l(run_animation_r.returnReflectedCopy()),
      stand_animation_l(stand_animation_r.returnReflectedCopy()),
      fly_animation_l(fly_animation_r.returnReflectedCopy()),
      run_animation_r_pig(":/resources/animations/" + animation_dir + "/Run_pig.png", 300, 180, kPersonWidth, kPersonHeight),
      stand_animation_r_pig(":/resources/animations/" + animation_dir + "/Stand_pig.png", 300, 180, kPersonWidth, kPersonHeight),
      fly_animation_r_pig(":/resources/animations/" + animation_dir + "/Fly_pig.png", 300, 180, kPersonWidth, kPersonHeight),
      run_animation_l_pig(run_animation_r_pig.returnReflectedCopy()),
      stand_animation_l_pig(stand_animation_r_pig.returnReflectedCopy()),
      fly_animation_l_pig(fly_animation_r_pig.returnReflectedCopy()) {}

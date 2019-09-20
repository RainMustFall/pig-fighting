#ifndef PIGFACTORY_H
#define PIGFACTORY_H

#include "animation.h"
#include <QSound>

struct PigAnimationStorage {
    PigAnimationStorage();

    Animation pig_running_l;
    Animation pig_running_r;

    Animation pig_flying_l;
    Animation pig_flying_r;

    QSound* hit_sound;
};

struct PersonAnimationStorage {
    PersonAnimationStorage();

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
};



#endif // PIGFACTORY_H

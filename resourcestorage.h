#ifndef PIGFACTORY_H
#define PIGFACTORY_H

#include "animation.h"
#include "movingobject.h"
#include "utils.h"
#include <QSound>

struct PigAnimationStorage {
    PigAnimationStorage();

    Animation run_l;
    Animation run_r;

    Animation fly_l;
    Animation fly_r;

    QSound* hit_sound;
};

struct PersonAnimationStorage {
    PersonAnimationStorage(const QString& animation_dir);

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

    Animation* storage[2][2][3] = {{{&run_r, &stand_r, &fly_r},
                                    {&run_l, &stand_l, &fly_l}},
                                   {{&run_r_pig, &stand_r_pig, &fly_r_pig},
                                    {&run_l_pig, &stand_l_pig, &fly_l_pig}}};

    Animation& GetAnimation(bool armed, utils::PersonState state,
                            MovingObject::Side side);
};



#endif // PIGFACTORY_H

#include "shotpig.h"
#include "constants.h"
#include "person.h"

ShotPig::ShotPig(int x, int y, int direction) : MovingObject(x, y, 20, 20)
{
    moveVector_.x = direction * kShotSpeed;
    moveVector_.y = 0;
}

bool ShotPig::Hits(GameObject& player) {
    if (dynamic_cast<Person*>(&player) != nullptr) {
        return GameObject::Hits(player);
    } else return false;
}

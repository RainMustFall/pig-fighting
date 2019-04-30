#include "shotpig.h"
#include "constants.h"
#include "person.h"

ShotPig::ShotPig(int x, int y, int direction, const Person* shooting_player)
    : MovingObject(x, y, kPigSize, kPigSize),
      shooting_player(shooting_player)
{
    moveVector_.x = direction * kShotSpeed;
    moveVector_.y = 0;
}


bool ShotPig::if_Hits(const std::vector<Person>& persons,
                      const std::vector<Ground>& ground) {
    bool hits = false;
    for (const auto& item : ground) {
        auto item_obj = dynamic_cast<const GameObject&>(item);

        if (Hits(item_obj)) {
            hits = true;
        }
    }
    for (const auto& item : persons) {
        auto item_obj = dynamic_cast<const GameObject&>(item);
        if (&item != shooting_player){
           if (Hits(item_obj)) {
                hits = true;
            }
        }
    }
    return hits;
}

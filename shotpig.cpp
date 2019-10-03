#include "shotpig.h"
#include "constants.h"
#include "person.h"

ShotPig::ShotPig(int x, int y, int direction, const Person* shooting_player,
                 const PigAnimationStorage* animations)
    : MovingObject(x, y, kPigSize, kPigSize),
      shooting_player(shooting_player),
      animations_(animations) {
    moveVector_.x = direction * kShotSpeed;
    moveVector_.y = 0;
}


const GameObject* ShotPig::Pig_Hits(std::vector<Person>& persons,
                      const std::vector<Ground>& ground) {

    for (auto& item : persons) {
        auto item_obj = dynamic_cast<const GameObject*>(&item);
        if (&item != shooting_player){
           if (Hits(item_obj)) {
                item.moveVector_.x += moveVector_.x / 2;
                return &item;
            }
        }
    }

    for (const auto& item : ground) {
        auto item_obj = dynamic_cast<const GameObject*>(&item);
        if (Hits(item_obj)) {
            return &item;
        }
    }
    return nullptr;
}

void ShotPig::PlayMusic(){
    //h_player->play();
}
void ShotPig::PlayMusicFly(){
    //f_player->play();
}

void ShotPig::Draw(QPainter& painter) const {

    if (current_side == Side::LEFT) {
        painter.drawPixmap(xPos(), yPos(),
                           bBox_.width_, bBox_.height_,
                           animations_->fly_l.CurrentFrame());
    } else {
        painter.drawPixmap(xPos(), yPos(),
                           bBox_.width_, bBox_.height_,
                           animations_->fly_r.CurrentFrame());
    }
}

bool ShotPig::isOutOfScreen() {
    return (position_.x >= kScreenWidth) || (position_.x < -Width());
}

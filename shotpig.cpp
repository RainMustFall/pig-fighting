#include "shotpig.h"
#include "constants.h"
#include "person.h"

ShotPig::ShotPig(int x, int y, int direction, const Person* shooting_player,
                 Animation* flying_left, Animation* flying_right)
    : MovingObject(x, y, kPigSize, kPigSize),
      shooting_player(shooting_player),
      pig_flying_l(flying_left),
      pig_flying_r(flying_right),
      h_player (new QMediaPlayer),
      h_playlist (new QMediaPlaylist),
      f_player (new QMediaPlayer),
      f_playlist (new QMediaPlaylist)
{
    f_player->setPlaylist(f_playlist);
    f_playlist->addMedia(QUrl("qrc:resources/sounds/pig_fly.mp3"));
    f_playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
    h_player->setPlaylist(h_playlist);
    h_playlist->addMedia(QUrl("qrc:resources/sounds/hit2.mp3"));
    h_playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
    moveVector_.x = direction * kShotSpeed;
    moveVector_.y = 0;
}


const GameObject* ShotPig::Pig_Hits(std::vector<Person>& persons,
                      const std::vector<Ground>& ground) {

    for (auto& item : persons) {
        auto item_obj = dynamic_cast<const GameObject&>(item);
        if (&item != shooting_player){
           if (Hits(item_obj)) {
                item.moveVector_.x += moveVector_.x / 2;
                return &item;
            }
        }
    }

    for (const auto& item : ground) {
        auto item_obj = dynamic_cast<const GameObject&>(item);

        if (Hits(item_obj)) {

            return &item;
        }
    }
    return nullptr;
}

void ShotPig::PlayMusic(){
    h_player->play();
}

void ShotPig::PlayMusicFly() {
     f_player->play();
}


void ShotPig::Draw(QPainter& painter) const {

    if (current_side == Side::LEFT) {
        painter.drawPixmap(position_.x, position_.y,
                           bBox_.width_, bBox_.height_,
                           pig_flying_l->CurrentFrame());
    } else {
        painter.drawPixmap(position_.x, position_.y,
                           bBox_.width_, bBox_.height_,
                           pig_flying_r->CurrentFrame());
    }
}

#ifndef SHOTPIG_H
#define SHOTPIG_H
#include "moving_object.h"
#include "game_object.h"
#include "person.h"
#include "resource_storage.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>

class ShotPig : public MovingObject
{
public:
    ShotPig(int x, int y, int direction, const Person* shooting_player,
            const PigAnimationStorage* animations);
    const GameObject* Pig_Hits(std::vector<Person>& persons,
                 const std::vector<Ground>& ground);
    const Person* shooting_player;
    void Draw(QPainter& painter) const override;

    const PigAnimationStorage* animations_;

    void PlayMusic();
    void PlayMusicFly();
    bool isOutOfScreen();
};

#endif // SHOTPIG_H

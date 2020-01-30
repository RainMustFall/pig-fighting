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
    ShotPig(int x, int y, int direction, const Person* shooting_player_,
            const PigAnimationStorage* animations);

    const GameObject* PigHits(std::vector<Person>& persons,
                 const std::vector<Ground>& ground);

    void Draw(QPainter& painter) const override;
    bool IsOutOfScreen();

private:
    const Person* shooting_player_;
    const PigAnimationStorage* animations_;
};

#endif // SHOTPIG_H

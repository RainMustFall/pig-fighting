#ifndef PERSON_H
#define PERSON_H
#include "gameobject.h"
#include "animation.h"
#include "movingobject.h"
#include "resourcestorage.h"
#include "freepig.h"
#include "utils.h"
#include <QMediaPlayer>
#include "constants.h"
#include <QMediaPlaylist>

class FieldController;

class Person: public MovingObject
{
public:
    Person(int x, int y, const QString& animation_dir, int id, FieldController* controller);

    void CatchPressedKey(int key);
    void CatchReleasedKey(int key);
    // Проверяет, какие клавиши нажаты,
    // и обрабатывает все нажатия
    void ProcessKeyboard();
    void CatchPig(FreePig& pig);
    void UpdateAnimation();
    void Draw(QPainter& painter) const override;
    void ThrowPig();
    void CatchPig();
    int Health() const;

    // std::list<FreePig>::iterator FindClosestFreePig(MainWindow& w);

    bool armed_ = 0;
    // Флаги, показывающие, какие клавиши зажаты
    // в текущий момент времени
    bool Up_pressed = false;
    bool Left_pressed = false;
    bool Right_pressed = false;
    bool Down_pressed = false;
    bool can_shoot_ = true;

    int health_level_ = 100;

    void DecreaseHealthLevel();
    void IncreaseHelthLevel();
    void ResetRunAnimation();

    utils::PersonState state;
    PersonAnimationStorage animations_;
    const HandleKeys handle_keys_;

    void PlayMusicHit();
    int name_;
    FieldController* controller_;

protected:
    void UpdateAnimationUniversal(Animation& run_animation,
                                  Animation& stand_animation,
                                  Animation& fly_animation);

    void DrawUniversal(QPainter& painter,
                               const Animation& run_animation,
                               const Animation& stand_animation,
                               const Animation& fly_animation) const;
};

#endif // PERSON_H

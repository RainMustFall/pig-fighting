#ifndef PERSON_H
#define PERSON_H
#include "gameobject.h"
#include "animation.h"
#include "movingobject.h"
#include "resourcestorage.h"
#include "freepig.h"
#include <QMediaPlayer>
#include "constants.h"
#include <QMediaPlaylist>

class FieldController;

class Person: public MovingObject
{
public:
    Person(int x, int y, const QString& animation_dir, int id);

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

    // std::list<FreePig>::iterator FindClosestFreePig(MainWindow& w);

    bool armed_ = 0;
    // Флаги, показывающие, какие клавиши зажаты
    // в текущий момент времени
    bool Up_pressed = false;
    bool Left_pressed = false;
    bool Right_pressed = false;
    bool Down_pressed = false;

    std::list<FreePig>::iterator HitsPig(std::list<FreePig>& pigs);

    int health_level = 100;

    void DecreaseHealthLevel();
    void IncreaseHelthLevel();
    void ResetRunAnimation();
    
    enum class State {
        RUNNING,
        STANDING,
        FLYING
    };

    State state;
    PersonAnimationStorage animations_;
    const HandleKeys handle_keys_;

    void PlayMusicHit();
    int name_;
    FieldController* controller_;

signals:
    void PlayerWins(int name);

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

#ifndef SOUNDPLAYER_H
#define SOUNDPLAYER_H

#include <QSound>
#include <QThread>

class SoundPlayer : public QThread
{
public:
    enum class Sounds {
        Take,
        Throw,
        Hit
    };

    SoundPlayer(Sounds sound, QSound*);

    void run() override;
private:
    QSound* pig_fly;
    QSound* hit;
    QSound* take;

    Sounds sound_;
};

#endif // SOUNDPLAYER_H

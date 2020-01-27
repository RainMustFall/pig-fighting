#ifndef SOUNDPLAYER_H
#define SOUNDPLAYER_H

#include <QSound>
#include <QThread>
#include "utils.h"

class SoundPlayer : public QThread
{
public:
    SoundPlayer(utils::Sounds sound);

    void run() override;

    static QSound* pig_fly;
    static QSound* hit;
    static QSound* take;
private:
    utils::Sounds sound_;
};

#endif // SOUNDPLAYER_H

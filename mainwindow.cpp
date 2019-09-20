#include "mainwindow.h"
#include "constants.h"
#include "health_field.h"
#include "themostmainwindow.h"
#include "soundplayer.h"
#include <QPainter>
#include <chrono>
#include <cstdlib>
#include <QMouseEvent>
#include <QDebug>
#include <thread>
#include <QSound>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    pig_running_l(":/resources/animations/pig_running.png", 400, 400, kPigSize, kPigSize),
    pig_running_r(pig_running_l.returnReflectedCopy()),
    pig_flying_l(":/resources/animations/pig_flying.png", 400, 400, kPigSize, kPigSize),
    pig_flying_r(pig_flying_l.returnReflectedCopy()),
    parent_(dynamic_cast<TheMostMainWindow*>(parent)),
    f_player (new QMediaPlayer),
    f_playlist (new QMediaPlaylist),
    cur_theme(TextureType::GRASS),
    hit_sound(new QSound(":/resources/sounds/pig_caught.wav"))
{
    /*f_player->setPlaylist(f_playlist);
    f_playlist->addMedia(QUrl("qrc:resources/sounds/background.mp3"));
    f_playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    f_player->setVolume(15);*/

    DrawBackground();
    setFocus();
    qDebug() << "HERE! ";
    //pig_caught.setSource(QUrl::fromLocalFile(":/resources/sounds/pig_caught.mp3"));
    //pig_caught.setVolume(0.5f);
}

void MainWindow::SetTimer() {
    is_start = true;
    timer_id = startTimer(9);
}

void MainWindow::NewGame(TextureType type) {
    f_player->play();
    cur_theme = type;
    DrawBackground();

    setFocus();
    qDebug() <<"new";
    paused = false;
    players.clear();
    players.push_back({450, 120, "player_1"});
    players.push_back({800, 200, "player_2"});

    free_pigs.clear();
    free_pigs.push_back({100, 10, &pig_running_l, &pig_running_r});
    free_pigs.push_back({400, 10, &pig_running_l, &pig_running_r});

    flying_pigs.clear();
    parent_->ui->label_2->setText("");

    ground.clear();
    ground = {{-146, 160, 30, 420, cur_theme},
              {587, 130, 30, 270, cur_theme},
              {327, 327, 30, 270, cur_theme},
              {935, 327, 30, 270, cur_theme},
              {1193, 160, 30, 270, cur_theme},
              {1068, 486, 30, 270, cur_theme},
              {-52, 486, 30, 270, cur_theme},
              {122, 656, 30, 1200, cur_theme}
             };
    SetTimer();
}

void MainWindow::Pause(const QString &reason) {
    if (!paused) {
        parent_->ui->new_game->setEnabled(true);
        parent_->ui->comboBox->setEnabled(true);
        parent_->ui->pause->setText("Продолжить");
        killTimer(timer_id);
        parent_->ui->label_2->setText(reason);
    } else {
        setFocus();
        parent_->ui->new_game->setEnabled(false);
        parent_->ui->comboBox->setEnabled(false);
        parent_->ui->pause->setText("Пауза");
        parent_->ui->label_2->setText("");
        SetTimer();
    }
    if(reason != "Пауза"){
        parent_->ui->pause->setEnabled(false);
    }

    paused = not(paused);
}

void MainWindow::timerEvent(QTimerEvent *) {

    time++;
    if(time > 200) {
        is_start = false;
    }
    for (Person& player : players) {
        player.ProcessKeyboard();
        player.UpdateAnimation();
        player.current_platform = player.HitsGround(ground);
        player.ApplyPhysics();
        if (time == kTimeHealthUp) {
            time = 0;
            player.IncreaseHelthLevel();
        }
    }

    if (free_pigs.empty()) {
        free_pigs.insert(free_pigs.end(), GeneratePig());
    } else if (rand() % kPigGeneraingFrequency == 0 && free_pigs.size() < kPigCount) {
        free_pigs.insert(free_pigs.end(), GeneratePig());
    }

    pig_running_l.NextFrame();
    pig_running_r.NextFrame();

    for (FreePig& pig : free_pigs) {
        pig.PositionGenerate();
        pig.current_platform = pig.HitsGround(ground);
        pig.ApplyPhysics();
    }

    for (auto item = flying_pigs.begin(); item != flying_pigs.end(); ++item) {
        const GameObject* hitting_object = item->Pig_Hits(players, ground);
        if (hitting_object == nullptr) {
            item->UpdatePosition();
            if ((item->position_.x > kScreenWidth) || (item->position_.x < -item->Width())) {
                item = flying_pigs.erase(item);
            }
        } else if (dynamic_cast<const Person*>(hitting_object) != nullptr){
            QSound::play(":/resources/sounds/hit.mp3");
            players[0].PlayMusicHit();
            players[1].PlayMusicHit();
            item = flying_pigs.erase(item);
            const Person* hitting_person_const = dynamic_cast<const Person*>(hitting_object);
            Person* hitting_person = const_cast<Person*>(hitting_person_const);
            hitting_person->DecreaseHealthLevel();
            if (hitting_person->health_level <= 0) {
                // paused = true;
                if (hitting_person->name_ == 1) {
                    Pause("Игрок 2 выиграл!");
                } else {
                    Pause("Игрок 1 выиграл!");
                }
                killTimer(timer_id);
                is_start = true;

            }


        } else {
            QSound::play(":/resources/sounds/hit2.mp3");
            item->PlayMusic();
            item = flying_pigs.erase(item);
        }
    }

    repaint();
    for (Person& player : players) {
        player.UpdatePosition();
        player.CheckBoundaries();
    }
    for (FreePig& pig : free_pigs) {
        pig.UpdatePosition();
        pig.CheckBoundaries();
    }
}

void MainWindow::paintEvent(QPaintEvent *) {
    QPainter p;
    p.begin(this);

    for (Person& player : players) {
        player.Draw(p);
    }
    for (HealthField& field : health_fields) {
        field.Draw(p);
    }
    for (auto& item:ground) {
        item.Draw(p);
    }
    for (FreePig& item: free_pigs) {
        item.Draw(p);
    }
    for (ShotPig& item: flying_pigs) {
        item.Draw(p);
    }
    if (is_start) {
        DrawHint(p);
    } else if (time == 2000){
       DrawBackground();
    }
    p.end();
}

void MainWindow::DrawHint(QPainter& painter){
    const QRectF rectangle2 = {kScreenWidth- 355,kScreenHeight - 180, 345, 122};
    QImage image2;
    image2.load(":/resources/textures/instruction2.png");
    painter.drawImage(rectangle2,
                      image2);
    const QRectF rectangle1 = {10,kScreenHeight - 180, 345, 122};
    QImage image1;
    image1.load(":/resources/textures/instruction1.png");
    painter.drawImage(rectangle1,
                      image1);
}

void MainWindow::DrawBackground() {
    std::vector<QString>bg_dirs = {"grass", "sand", "cave", "snow"};

    qDebug() << "Drawing background";
    QPixmap bkgnd(":/resources/textures/" + bg_dirs[static_cast<int>(cur_theme)] + "/background.png");
    bkgnd = bkgnd.scaled(kScreenWidth, kScreenHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPalette p(palette());
    p.setBrush(QPalette::Background, bkgnd);
    setAutoFillBackground(true);
    setPalette(p);
}


void MainWindow::ThrowPig(Person& player) {
    if (player.armed_) {

        if (player.current_side == MovingObject::Side::LEFT){
            ShotPig pig(player.position_.x - kPigSize - 1,
                        player.position_.y + player.Height() - kPigSize - kPigHeight, -1,
                        &player, &pig_flying_l, &pig_flying_r);
            flying_pigs.push_back(pig);
             pig.PlayMusicFly();
        } else {
            ShotPig pig(player.position_.x + player.Width() + 1,
                        player.position_.y + player.Height() - kPigSize - kPigHeight, 1,
                        &player, &pig_flying_l, &pig_flying_r);
            flying_pigs.push_back(pig);
             //pig.PlayMusicFly();
        }
        player.armed_ = 0;

        free_pigs.push_back(GeneratePig());
    } else {
        std::list<FreePig>::iterator current_pig = player.HitsPig(free_pigs);
        qDebug() << current_pig->xPos() << ' ' << current_pig->yPos();
        if (current_pig != free_pigs.end()) {
            SoundPlayer* s_player = new SoundPlayer(SoundPlayer::Sounds::Hit, new QSound(":/resources/sounds/pig_caught.wav"));
            s_player->start();

            //QSound::play(":/resources/sounds/hit.wav");
            //pig_caught.play();

            player.CatchPig(*current_pig);
            //player.PlayMusic();
            free_pigs.erase(current_pig);
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_Space:
        ThrowPig(players[0]);
        break;
    case Qt::Key_Shift:
        ThrowPig(players[1]);
        break;
    case Qt::Key_Escape: {

        killTimer(timer_id);
        Pause("Пауза");
    }
        break;
    default:
        // Нажатия клавиш для обоих игроков (передаём в качестве аргумента нажатую клавишу
        // и четыре клавиши, отвечающие у этого игрока за верх, лево, низ, право)
        players[0].CatchPressedKey(event->key(), Qt::Key_W, Qt::Key_A, Qt::Key_S, Qt::Key_D);
        players[1].CatchPressedKey(event->key(), Qt::Key_Up, Qt::Key_Left, Qt::Key_Down, Qt::Key_Right);
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    players[0].CatchReleasedKey(event->key(), Qt::Key_W, Qt::Key_A, Qt::Key_S, Qt::Key_D);
    players[1].CatchReleasedKey(event->key(), Qt::Key_Up, Qt::Key_Left, Qt::Key_Down, Qt::Key_Right);
}

FreePig MainWindow::GeneratePig() {
    FreePig new_pig(10, 10, &pig_running_l, &pig_running_r);
    new_pig.setX(rand() % geometry().width());
    new_pig.setY(rand() % geometry().height());
    return new_pig;
}

MainWindow::~MainWindow()
{

}

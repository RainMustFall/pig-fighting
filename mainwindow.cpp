#include "mainwindow.h"
#include "constants.h"
#include "health_field.h"
#include "secondwindow.h"
#include <QPainter>
#include <chrono>
#include <cstdlib>
#include <QMouseEvent>
#include <QDebug>
#include <QSound>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    pig_running_l(":/resources/animations/pig_running.png", 400, 400, kPigSize, kPigSize),
    pig_running_r(Reflect(pig_running_l)),
    pig_flying_l(":/resources/animations/pig_flying.png", 400, 400, kPigSize, kPigSize),
    pig_flying_r(Reflect(pig_flying_l))
{
    DrawBackground();

    qDebug() << "HERE! ";
    pig_caught.setSource(QUrl::fromLocalFile(":/resources/sounds/pig_caught.mp3"));
    pig_caught.setVolume(0.25f);
    SetTimer();
}

void MainWindow::SetTimer() {
    is_start = true;
    timer_id = startTimer(9);
}
void MainWindow::NewGame(){
    qDebug() <<"new";
    players.clear();
    players.push_back({450, 120, "player_1"});
    players.push_back({800, 200, "player_2"});

    free_pigs.clear();
    free_pigs.push_back({100, 10, &pig_running_l, &pig_running_r});
    free_pigs.push_back({400, 10, &pig_running_l, &pig_running_r});

    flying_pigs.clear();
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
    } else if (rand() % 500 == 0 && free_pigs.size() < kPigCount) {
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
    if (is_start) {
        DrawHint(p);
    } else if (time == 2000){
       DrawBackground();
    }

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
    p.end();
}

void MainWindow::DrawHint(QPainter& painter){
    const QRectF rectangle2 = {kScreenWidth- 355,kScreenHeight - 130, 345, 122};
    QImage image2;
    image2.load(":/resources/textures/instruction2.png");
    painter.drawImage(rectangle2,
                      image2);
    const QRectF rectangle1 = {10,kScreenHeight - 130, 345, 122};
    QImage image1;
    image1.load(":/resources/textures/instruction1.png");
    painter.drawImage(rectangle1,
                      image1);
}

void MainWindow::DrawBackground(){
    QPixmap bkgnd(":/resources/textures/background.png");
    bkgnd = bkgnd.scaled(1440, 810, Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
}

void MainWindow::ThrowPig(Person& player) {
    if (player.armed_) {
        QSound::play(":/resources/sounds/pig_fly.mp3");
        if (player.current_side == MovingObject::Side::LEFT){
            ShotPig pig(player.position_.x - kPigSize - 1,
                        player.position_.y + player.Height() - kPigSize - kPigHeight, -1,
                        &player, &pig_flying_l, &pig_flying_r);
            flying_pigs.push_back(pig);
             player.PlayMusicFly();
        } else {
            ShotPig pig(player.position_.x + player.Width() + 1,
                        player.position_.y + player.Height() - kPigSize - kPigHeight, 1,
                        &player, &pig_flying_l, &pig_flying_r);
            flying_pigs.push_back(pig);
             player.PlayMusicFly();
        }
        player.armed_ = 0;

        player.PlayMusicFly();
        free_pigs.push_back(GeneratePig());
    } else {
        std::list<FreePig>::iterator current_pig = player.HitsPig(free_pigs);
        qDebug() << current_pig->xPos() << ' ' << current_pig->yPos();
        if (current_pig != free_pigs.end()) {
//            QSound::play(":/resources/sounds/pig_caught.mp3");
            pig_caught.play();
            player.CatchPig(*current_pig);
            player.PlayMusic();
            free_pigs.erase(current_pig);
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_Space:
        players[0].PlayMusicFly();
        ThrowPig(players[0]);
        break;
    case Qt::Key_Shift:
        players[1].PlayMusicFly();
        ThrowPig(players[1]);
        break;
    case Qt::Key_Escape: {
        killTimer(timer_id);
        SecondWindow window(this);
        window.setModal(true);
        window.exec();
        SetTimer();
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

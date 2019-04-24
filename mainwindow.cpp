#include "mainwindow.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    qDebug() << "HERE! ";
    startTimer(10);
}

void MainWindow::timerEvent(QTimerEvent *) {
    for (Person& player : players) {
        player.ProcessKeyboard();
        player.current_platform = player.HitsGround(ground);
        player.ApplyPhysics();
    }
        for (FreePig& pig : free_pigs) {
            pig.current_platform = pig.HitsGround(ground);
            pig.ApplyPhysics();
            pig.UpdatePosition();
        }
        for (int i = 0; i < flying_pigs.size(); i++) {
            if (!flying_pigs[i].if_Hits(players, ground)) {
            flying_pigs[i].UpdatePosition();
            if ((flying_pigs[i].position_.x > 1000) || (flying_pigs[i].position_.x < 0)) {
                flying_pigs.erase(flying_pigs.begin() + i);
            }
            } else {
                qDebug() << flying_pigs[i].if_Hits(players, ground);
                flying_pigs.erase(flying_pigs.begin() + i);
            }
        }
        repaint();
        for (Person& player : players) {
            player.UpdatePosition();
    }
}
void MainWindow::paintEvent(QPaintEvent *) {
    QPainter p;
    p.begin(this);
    for (Person& player : players) {
        player.Draw(p);
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

void MainWindow::keyPressEvent(QKeyEvent *event) {
    switch(event->key()) {
    case Qt::Key_A:
        players[0].Left_pressed = true;
        break;
    case Qt::Key_D:
        players[0].Right_pressed = true;
        break;
    case Qt::Key_W:
        players[0].Up_pressed = true;
        break;
    case Qt::Key_S:
        players[0].Down_pressed = true;
        if (players[0].current_platform != nullptr) {
            players[0].ignored_platform = players[0].current_platform;
        } else {
            players[0].moveVector_.y += 10;
        }
        break;
    case Qt::Key_Space :
        if (players[0].armed_) {
            if (players[0].current_side == MovingObject::Side::LEFT){
                ShotPig pig(players[0].position_.x - 20, players[0].position_.y + 20, -1, &players[0]);
                flying_pigs.push_back(pig);
            } else {
                ShotPig pig(players[0].position_.x + 20, players[0].position_.y + 20, 1, &players[0]);
                flying_pigs.push_back(pig);
            }
            players[0].armed_ = 0;
        } else {
            if (!free_pigs.empty()) {
                auto piggo = players[0].FindClosestFreePig(*this);
                players[0].CatchPig(*piggo);
                free_pigs.erase(piggo);
            }
         }
        break;
    case Qt::Key_Left:
        players[1].Left_pressed = true;
        break;
    case Qt::Key_Right:
        players[1].Right_pressed = true;
        break;
    case Qt::Key_Up:
        players[1].Up_pressed = true;
        break;
    case Qt::Key_Down:
        players[1].Down_pressed = true;
        if (players[1].current_platform != nullptr) {
            players[1].ignored_platform = players[1].current_platform;
        } else {
            players[1].moveVector_.y += 10;
        }
        break;
    case Qt::Key_Shift:
        qDebug() << "Shift!";
        if (players[1].armed_) {
            if (players[1].current_side == MovingObject::Side::LEFT){
                ShotPig pig(players[1].position_.x - 20, players[1].position_.y + 20, -1, &players[1]);
                flying_pigs.push_back(pig);
            } else {
                ShotPig pig(players[1].position_.x + 20, players[1].position_.y + 20, 1, &players[1]);
                flying_pigs.push_back(pig);
            }
            players[1].armed_ = 0;
        } else {
            if (!free_pigs.empty()) {
                auto piggo = players[1].FindClosestFreePig(*this);
                players[1].CatchPig(*piggo);
                free_pigs.erase(piggo);
            }
         }
        break;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    switch(event->key()) {
    case Qt::Key_A:
        players[0].Left_pressed = false;
        break;
    case Qt::Key_D:
        players[0].Right_pressed = false;
        break;
    case Qt::Key_W:
        players[0].Up_pressed = false;
        break;
    case Qt::Key_S:
        players[0].Down_pressed = false;
        break;
    case Qt::Key_Left:
        players[1].Left_pressed = false;
        break;
    case Qt::Key_Right:
        players[1].Right_pressed = false;
        break;
    case Qt::Key_Up:
        players[1].Up_pressed = false;
        break;
    case Qt::Key_Down:
        players[1].Down_pressed = false;
        break;
    }
}


MainWindow::~MainWindow()
{

}

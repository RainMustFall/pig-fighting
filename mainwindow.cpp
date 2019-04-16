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
    player.ProcessKeyboard();
    player.current_platform = player.HitsGround(ground);
    player.ApplyPhysics();
    for (FreePig& pig : free_pigs) {
        pig.current_platform = pig.HitsGround(ground);
        pig.ApplyPhysics();
        pig.UpdatePosition();
    }
    for (int i = 0; i < flying_pigs.size(); i++) {
        flying_pigs[i].UpdatePosition();
        if ((flying_pigs[i].position_.x > 1000) || (flying_pigs[i].position_.x < 0)) {
            flying_pigs.erase(flying_pigs.begin() + i);
        }
    }
    repaint();
    player.UpdatePosition();
}

void MainWindow::paintEvent(QPaintEvent *) {
    QPainter p;
    p.begin(this);
    player.Draw(p);
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
        player.Left_pressed = true;
        break;
    case Qt::Key_D:
        player.Right_pressed = true;
        break;
    case Qt::Key_W:
        player.Up_pressed = true;
        break;
    case Qt::Key_S:
        player.Down_pressed = true;

        if (player.current_platform != nullptr) {
            player.ignored_platform = player.current_platform;
        } else {
            player.moveVector_.y += 10;
        }
        break;
    case Qt::Key_C:
        {
        auto piggo = player.FindClosestFreePig(*this);
        player.CatchPig(*piggo);
        free_pigs.erase(piggo);
        break;
    }
    case Qt::Key_Q :
        if (player.armed_) {
        ShotPig pig1(player.position_.x - 20, player.position_.y + 20, -1);
        flying_pigs.push_back(pig1);
        player.armed_ = 0;
        break;
    }
    case Qt::Key_E:
        if (player.armed_) {
        ShotPig pig2(player.position_.x + 20, player.position_.y + 20, 1);
        flying_pigs.push_back(pig2);
        player.armed_ = 0;
        break;
    }
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    switch(event->key()) {
    case Qt::Key_A:
        player.Left_pressed = false;
        break;
    case Qt::Key_D:
        player.Right_pressed = false;
        break;
    case Qt::Key_W:
        player.Up_pressed = false;
        break;
    case Qt::Key_S:
        player.Down_pressed = false;
        break;
    }
}


MainWindow::~MainWindow()
{

}

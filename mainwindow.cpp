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

    if (player.current_platform != nullptr) {
        player.moveVector_.y = std::min(0.0, player.moveVector_.y);
    } else {
        player.moveVector_.y += kGravitation;
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

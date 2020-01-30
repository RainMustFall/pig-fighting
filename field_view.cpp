#include "field_view.h"
#include "constants.h"
#include "health_field.h"
#include "main_window.h"
#include "sound_player.h"
#include <QPainter>
#include <chrono>
#include <cstdlib>
#include <QMouseEvent>
#include <QDebug>
#include <thread>
#include <QSound>

FieldView::FieldView(QWidget *parent)
    : QMainWindow(parent),
      controller_(new FieldController(this)),
      parent_(dynamic_cast<MainWindow*>(parent)),
      cur_theme_(utils::TextureType::GRASS)
{
    DrawBackground();
    setFocus();
}

void FieldView::SetTimer() {
    is_start_ = true;
    timer_id_ = startTimer(9);
}

void FieldView::StopTimer() {
    killTimer(timer_id_);
}

void FieldView::GameOver(int player) {
    parent_->GameOver(player);
}

void FieldView::NewGame(utils::TextureType type) {
    cur_theme_ = type;
    DrawBackground();
    setFocus();
    delete controller_;
    controller_ = new FieldController(this, type);
    SetTimer();
}

void FieldView::timerEvent(QTimerEvent *) {
    controller_->UpdateTimer();
    controller_->UpdatePlayers();
    controller_->AddPigs();
    controller_->UpdateFreePigs();
    controller_->UpdateFlyingPigs();
    repaint();
}

void FieldView::paintEvent(QPaintEvent *) {
    QPainter p;
    p.begin(this);
    controller_->OnPaintingStarted(p);
    p.end();
}

void FieldView::DrawHint(QPainter& painter){
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

void FieldView::DrawBackground() {
    QString bg_dir = background_dirs_[static_cast<unsigned>(cur_theme_)];
    QPixmap bkgnd(kTexturesPath + bg_dir + "/background.png");
    bkgnd = bkgnd.scaled(kScreenWidth, kScreenHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPalette p(palette());
    p.setBrush(QPalette::Background, bkgnd);
    setAutoFillBackground(true);
    setPalette(p);
}

void FieldView::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_Escape) {
      parent_->Pause(false);
    } else {
        controller_->OnKeyPressed(event);
    }
}

void FieldView::keyReleaseEvent(QKeyEvent *event) {
    controller_->OnKeyReleased(event);
}

FieldView::~FieldView()
{

}

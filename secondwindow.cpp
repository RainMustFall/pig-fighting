#include "secondwindow.h"
#include "ui_secondwindow.h"
#include "mainwindow.h"
#include <QDebug>

SecondWindow::SecondWindow(MainWindow *parent, PauseCase type) :
    QDialog(parent),
    parent(parent),
    type(type),
    ui(new Ui::SecondWindow)
{
    ui->setupUi(this);
    if (type == PauseCase::ESCAPE){
        ui->label->setText("Пауза");
    } else if (type == PauseCase::FIRSTWIN){
        ui->label->setText("Игрок 1 победил!");
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_2->setHidden(true);
    } else {
        ui->label->setText("Игрок 2 победил!");
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_2->setHidden(true);
    }
}


SecondWindow::~SecondWindow()
{
    delete ui;
}

void SecondWindow::on_pushButton_clicked()
{
    parent->NewGame();
    hide();
}
void SecondWindow::on_pushButton_2_clicked()
{
    hide();
}

void SecondWindow::on_pushButton_3_clicked()
{
    if (ThirdButtonSoundTurnOn){
        ThirdButtonSoundTurnOn = false;
    } else {
        ThirdButtonSoundTurnOn = true;
    }

    if (ThirdButtonSoundTurnOn) {
        ui->pushButton_3->setText("Включить звук");
    } else {
        ui->pushButton_3->setText("Выключить звук");
    }
}

void SecondWindow::on_pushButton_4_clicked()
{
    QApplication::quit();
}

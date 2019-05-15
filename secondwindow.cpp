#include "secondwindow.h"
#include "ui_secondwindow.h"
#include "mainwindow.h"
#include <QDebug>

SecondWindow::SecondWindow(MainWindow *parent) :
    QDialog(parent),
    parent(parent),
    ui(new Ui::SecondWindow)
{
    ui->setupUi(this);
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

}

void SecondWindow::on_pushButton_4_clicked()
{
    QApplication::quit();
}

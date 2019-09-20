#include "themostmainwindow.h"
#include "mainwindow.h"
#include <QDebug>

TheMostMainWindow::TheMostMainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
        win(new MainWindow(this))
{
    setWindowIcon(QIcon(":/resources/textures/icon.ico"));
    setWindowTitle("Pig Fighting");

    ui->setupUi(this);
    ui->verticalLayout->addWidget(win);
    //connect(ui->new_game, &QPushButton::clicked, this, &TheMostMainWindow::on_new_game_clicked);
    //connect(ui->pause, &QPushButton::clicked, this, &TheMostMainWindow::on_pause_clicked);
    //connect(ui->exit, &QPushButton::clicked, this, &TheMostMainWindow::on_exit_clicked);
    ui->comboBox->addItem("Классический");
    ui->comboBox->addItem("Песчаный");
    ui->comboBox->addItem("Пещера");
    ui->comboBox->addItem("Снежная");
}

void TheMostMainWindow::on_new_game_clicked()
{
//    QPixmap bkgnd(":/resources/textures/background.png");
//    bkgnd = bkgnd.scaled(kScreenWidth, kScreenHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
//    QPalette palette;
//    palette.setBrush(QPalette::Background, bkgnd);
//    win->setPalette(palette);

    win->NewGame(static_cast<TextureType>(ui->comboBox->currentIndex()));
    ui->new_game->setEnabled(false);
    ui->comboBox->setEnabled(false);
    ui->pause->setEnabled(true);
    ui->pause->setText("Пауза");
}

void TheMostMainWindow::on_pause_clicked()
{
    if (!win->paused) {
        ui->new_game->setEnabled(true);
        ui->comboBox->setEnabled(true);
        ui->pause->setText("Продолжить");
        win->killTimer(win->timer_id);
        ui->label_2->setText("Пауза");
    } else {
        win->setFocus();
        ui->new_game->setEnabled(false);
        ui->comboBox->setEnabled(false);
        ui->pause->setText("Пауза");
        ui->label_2->setText("");
        win->SetTimer();
    }

    win->paused = not(win->paused);
}

void TheMostMainWindow::on_exit_clicked()
{
    QApplication::exit(0);
}

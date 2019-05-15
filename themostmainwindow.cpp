#include "themostmainwindow.h"
#include "mainwindow.h"

TheMostMainWindow::TheMostMainWindow(QWidget *parent)
    : QMainWindow(parent),
      win(new MainWindow(this))
{
    ui.setupUi(this);
    ui.verticalLayout->addWidget(win);
}

void TheMostMainWindow::on_new_game_clicked()
{
    auto child = ui.verticalLayout->takeAt(0);
    delete child->widget();
    delete child;
    //win = new MainWindow(this);
}

#include <QApplication>
#include "mainwindow.h"
#include "secondwindow.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    MainWindow w;
    SecondWindow s;
    w.setFixedSize(kScreenWidth, kScreenHeight);
    w.show();
    return app.exec();
}

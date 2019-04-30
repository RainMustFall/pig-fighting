#include <QApplication>
#include "mainwindow.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    MainWindow w;
    w.setFixedSize(kScreenWidth, kScreenHeight);
    w.show();
    return app.exec();
}

#include <QApplication>
#include "mainwindow.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    MainWindow w;
    w.setFixedSize(960, 540);
    w.show();
    return app.exec();
}

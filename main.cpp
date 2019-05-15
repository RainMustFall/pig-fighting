#include <QApplication>
#include "mainwindow.h"
#include "themostmainwindow.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    TheMostMainWindow w;
    w.show();
    return app.exec();
}

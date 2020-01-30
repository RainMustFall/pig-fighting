#include <QApplication>
#include "field_view.h"
#include "main_window.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    MainWindow w;
    w.show();
    return QApplication::exec();
}

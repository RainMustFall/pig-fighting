#include <QApplication>

#include "./view_controller/field_view.h"
#include "./view_controller/main_window.h"

int main(int argc, char **argv) {
  QApplication app(argc, argv);
  MainWindow w;
  w.show();
  return app.exec();
}

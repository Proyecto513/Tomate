#include "trayicon.h"
#include <QCoreApplication>
#include <singleapplication.h>

int main(int argc, char *argv[]) {
  QCoreApplication::setOrganizationName("TomateQt");
  QCoreApplication::setOrganizationDomain("tomate.qt");
  QCoreApplication::setApplicationName("Tomate");
  SingleApplication a(argc, argv);
  TrayIcon t;
  t.show();
  return a.exec();
}

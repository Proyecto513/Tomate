#include "settings.h"
#include <QApplication>
#include <singleapplication.h>

int main(int argc, char *argv[])
{
    SingleApplication a(argc, argv);
    settings w;
    w.show();

    return a.exec();
}

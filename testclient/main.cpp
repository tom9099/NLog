#include "mainwindow.h"
#include <QApplication>
#include "nshared.h"

int main(int argc, char *argv[])
{
    NShared::boostPriority();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

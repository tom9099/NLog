#include "mainwindow.h"
#include <QApplication>
#include <Windows.h>

int main(int argc, char *argv[])
{
    SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

#include "mainwindow.h"
#include <QApplication>
#include "name.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    Name name;
    name.show();

    return a.exec();
}

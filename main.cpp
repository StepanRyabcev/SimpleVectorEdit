#include "mainwindow.h"
#include "graphicsscene.h"

#include <QApplication>

#include <QGraphicsView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

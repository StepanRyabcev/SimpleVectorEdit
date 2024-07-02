#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "graphicsscene.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void save();

    void load();

    void save_quick();

    void clear();

    void undo();

    void rect();

    void diamond();

    void simple();

    void ellipse();

    void on_choosecolor_clicked();

private:
    Ui::MainWindow *ui;
    QColor cl = Qt::blue;
    GraphicsScene *scene;
    QString fileName, fileName_b;
    int primit = 1; //1 - прямоугольник, 2 - ромб
};
#endif // MAINWINDOW_H

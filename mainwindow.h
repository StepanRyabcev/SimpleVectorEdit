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
    void on_white_clicked();

    void on_black_clicked();

    void on_blue_clicked();

    void on_green_clicked();

    void on_yellow_clicked();

    void on_red_clicked();

    void save();

    void load();

    void save_quick();

    void clear();

    void undo();

private:
    Ui::MainWindow *ui;
    QColor cl = Qt::blue;
    GraphicsScene *scene;
    QString fileName, fileName_b;
};
#endif // MAINWINDOW_H

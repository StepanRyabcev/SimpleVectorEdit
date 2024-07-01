#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphicsscene.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new GraphicsScene;
    ui->graphicsView->setScene(scene);
    QObject::connect(ui->save, &QAction::triggered, this, MainWindow::save);
    QObject::connect(ui->load, &QAction::triggered, this, MainWindow::load);
    QObject::connect(ui->savequick, &QAction::triggered, this, MainWindow::save_quick);
    QObject::connect(ui->clear, &QAction::triggered, this, MainWindow::clear);
    QObject::connect(ui->undo, &QAction::triggered, this, MainWindow::undo);
    ui->graphicsView->show();
    QPalette palwhite = ui->white->palette();
    palwhite.setColor(QPalette::Button, QColor(Qt::white));
    ui->white->setAutoFillBackground(true);
    ui->white->setPalette(palwhite);
    ui->white->update();
    QPalette palblack = ui->black->palette();
    palblack.setColor(QPalette::Button, QColor(Qt::black));
    ui->black->setAutoFillBackground(true);
    ui->black->setPalette(palblack);
    ui->black->update();
    QPalette palblue = ui->blue->palette();
    palblue.setColor(QPalette::Button, QColor(Qt::blue));
    ui->blue->setAutoFillBackground(true);
    ui->blue->setPalette(palblue);
    QPalette palgreen = ui->green->palette();
    palgreen.setColor(QPalette::Button, QColor(Qt::green));
    ui->green->setAutoFillBackground(true);
    ui->green->setPalette(palgreen);
    QPalette palyellow = ui->yellow->palette();
    palyellow.setColor(QPalette::Button, QColor(Qt::yellow));
    ui->yellow->setAutoFillBackground(true);
    ui->yellow->setPalette(palyellow);
    QPalette palred = ui->red->palette();
    palred.setColor(QPalette::Button, QColor(Qt::red));
    ui->red->setAutoFillBackground(true);
    ui->red->setPalette(palred);
    ui->savequick->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_white_clicked()
{
    cl = Qt::white;
    scene->ChangeColor(cl);
}


void MainWindow::on_black_clicked()
{
    cl = Qt::black;
    scene->ChangeColor(cl);
}


void MainWindow::on_blue_clicked()
{
    cl = Qt::blue;
    scene->ChangeColor(cl);
}


void MainWindow::on_green_clicked()
{
    cl = Qt::green;
    scene->ChangeColor(cl);
}


void MainWindow::on_yellow_clicked()
{
    cl = Qt::yellow;
    scene->ChangeColor(cl);
}


void MainWindow::on_red_clicked()
{
    cl = Qt::red;
    scene->ChangeColor(cl);
}

void MainWindow::save()
{
    fileName = QFileDialog::getSaveFileName(this, ("Open File"), "/home", ("Some File(*.mgf)"));
    if (!fileName.isEmpty())
    {
        fileName_b = fileName;
        ui->savequick->setEnabled(true);
        scene->saveToFile(fileName);
    }
    else
        fileName = fileName_b;
}

void MainWindow::load()
{
    fileName = QFileDialog::getOpenFileName(this, ("Open File"), "/home", ("Some File(*.mgf)"));
    if (!fileName.isEmpty())
    {
        fileName_b = fileName;
        delete scene;
        scene = new GraphicsScene;
        scene->loadFromFile(fileName);
        ui->savequick->setEnabled(true);
        ui->graphicsView->setScene(scene);
        ui->graphicsView->show();
    }
    else
        fileName = fileName_b;
}

void MainWindow::save_quick()
{
    if (!fileName.isEmpty())
        scene->saveToFile(fileName);
}

void MainWindow::clear()
{
    delete scene;
    scene = new GraphicsScene;
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
}

void MainWindow::undo()
{
    scene->undo();
}

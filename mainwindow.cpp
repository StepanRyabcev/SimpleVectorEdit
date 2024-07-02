#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphicsscene.h"
#include <QFileDialog>
#include <QColorDialog>

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
    QObject::connect(ui->rect, &QAction::triggered, this, MainWindow::rect);
    QObject::connect(ui->diamond, &QAction::triggered, this, MainWindow::diamond);
    QObject::connect(ui->simple, &QAction::triggered, this, MainWindow::simple);
    QObject::connect(ui->ellipse, &QAction::triggered, this, MainWindow::ellipse);
    ui->graphicsView->show();
    QPixmap pixmap(ui->currentcolor->size());
    pixmap.fill(cl);
    ui->currentcolor->setPixmap(pixmap);
    ui->savequick->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
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
    scene->ChangeColor(cl);
    scene->changePrimitive(primit);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
}

void MainWindow::undo()
{
    scene->undo();
}

void MainWindow::rect()
{
    primit = 1;
    scene->changePrimitive(primit);
    ui->primit->setText("Прямоугольник");
}

void MainWindow::diamond()
{
    primit = 2;
    scene->changePrimitive(primit);
    ui->primit->setText("Ромб");
}

void MainWindow::simple()
{
    primit = 3;
    scene->changePrimitive(primit);
    ui->primit->setText("Простое рисование");
}

void MainWindow::ellipse()
{
    primit = 4;
    scene->changePrimitive(primit);
    ui->primit->setText("Овал");
}

void MainWindow::on_choosecolor_clicked()
{
    cl = QColorDialog::getColor(cl, nullptr, "Выберите цвет", QColorDialog::DontUseNativeDialog);
    scene->ChangeColor(cl);
    QPixmap pixmap(ui->currentcolor->size());
    pixmap.fill(cl);
    ui->currentcolor->setPixmap(pixmap);
}


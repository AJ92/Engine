#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Object/object.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    //test

    Object *o1 = new Object();
    qDebug(o1->to_string().toUtf8());

}

MainWindow::~MainWindow()
{
    delete ui;
}

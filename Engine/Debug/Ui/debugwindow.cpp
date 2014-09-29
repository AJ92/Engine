#include "debugwindow.h"
#include "ui_debugwindow.h"


DebugWindow::DebugWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DebugWindow)
{
    ui->setupUi(this);
    ui->fpsGraph->show();
    ui->fpsGraph->setTitle("FPS");

    ui->nsGraph->show();
    ui->nsGraph->setTitle("NS/Frame");

    ui->tsGraph->show();
    ui->tsGraph->setTitle("TimeStep");

    ui->mpfGraph->show();
    ui->mpfGraph->setTitle("Meshs/Frame");

    ui->tpfGraph->show();
    ui->tpfGraph->setTitle("Tris/Frame");

    ui->tbGraph->show();
    ui->tbGraph->setTitle("TexBinds/Frame");

}

DebugWindow::~DebugWindow()
{
    delete ui;
}

void DebugWindow::add_log(QString log_message){

    //qDebug(log_message.toUtf8());

    ui->textEdit->append(log_message);

    // create / set text cursor
    QTextCursor cursor(ui->textEdit->textCursor());
    cursor.movePosition(QTextCursor::End);
    ui->textEdit->setTextCursor(cursor);
    ui->textEdit->ensureCursorVisible();

}

void DebugWindow::add_fps_data(double fps){
    ui->fpsGraph->addData(fps);
}

void DebugWindow::add_ns_data(double ns){
    ui->nsGraph->addData(ns);
}

void DebugWindow::add_ts_data(double ts){
    ui->tsGraph->addData(ts);
}

void DebugWindow::add_mpf_data(double mpf){
    ui->mpfGraph->addData(mpf);
}

void DebugWindow::add_tpf_data(double tpf){
    ui->tpfGraph->addData(tpf);
}

void DebugWindow::add_tb_data(double tb){
    ui->tbGraph->addData(tb);
}

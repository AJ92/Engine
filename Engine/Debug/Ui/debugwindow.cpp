#include "debugwindow.h"
#include "ui_debugwindow.h"

DebugWindow::DebugWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DebugWindow),
    max_log_size(1000)
{
    ui->setupUi(this);
}

DebugWindow::~DebugWindow()
{
    delete ui;
}


void DebugWindow::add_log(QString log_message){
    log.append(log_message+"\n");
    if(log.size() >= max_log_size){
        log = log.right(max_log_size);
    }
    ui->textEdit->setText(log);
    ui->textEdit->ensureCursorVisible();
}

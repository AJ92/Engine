#include "debugwindow.h"
#include "ui_debugwindow.h"

DebugWindow::DebugWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DebugWindow),
    max_log_size(5000)
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


    // create / set text cursor
    QTextCursor cursor(ui->textEdit->textCursor());
    cursor.movePosition(QTextCursor::End);
    ui->textEdit->setTextCursor(cursor);
    ui->textEdit->ensureCursorVisible();

    //ui->textEdit->verticalScrollBar()->setValue(ui->textEdit->verticalScrollBar()->maximum());
}

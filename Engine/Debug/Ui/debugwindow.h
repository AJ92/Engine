#ifndef DEBUGWINDOW_H
#define DEBUGWINDOW_H

#include <QMainWindow>
#include <QTextCursor>
#include <QString>

namespace Ui {
class DebugWindow;
}

class DebugWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit DebugWindow(QWidget *parent = 0);
    ~DebugWindow();

    void add_log(QString log);
    
private:
    Ui::DebugWindow *ui;

    int max_log_size;
    QString log;
};

#endif // DEBUGWINDOW_H

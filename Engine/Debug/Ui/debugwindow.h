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

    void add_fps_data(double fps);
    void add_ns_data(double ns);
    void add_ts_data(double ts);
    void add_mpf_data(double mpf);
    void add_tpf_data(double tpf);

    
private:
    Ui::DebugWindow *ui;

};

#endif // DEBUGWINDOW_H

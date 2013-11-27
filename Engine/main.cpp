#include <QtGui/QApplication>
#include "Debug/Ui/debugwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DebugWindow w;
    w.show();

    w.add_log("Engine started.");
    
    return a.exec();
}

//QT 4.x
//#include <QtGui/QApplication>

//QT 5.x
#include <QApplication>
#include "engine.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Engine e;
    e.setWindowTitle("Engine v0.01");
    e.showDebugWindow();
    e.initialize(argc, argv);
    
    return a.exec();
}

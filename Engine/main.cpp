//QT 4.x
//#include <QtGui/QApplication>

//QT 5.x
#include <QApplication>



#include "engine.h"
#include <qDebug>





int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    Engine e;
    e.setWindowTitle("Engine v0.01");
    e.showDebugWindow();
    e.initialize(argc, argv);


    //IF the debug window should close and terminate programm when openGL window is closed.
    //return 0;
    return a.exec();
}

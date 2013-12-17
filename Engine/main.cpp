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
    e.showDebugWindow();
    e.initialize(argc, argv);
    e.setWindowTitle("Engine v0.01");

    qDebug("back to main.cpp");

    return a.exec();
}

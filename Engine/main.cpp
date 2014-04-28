//QT 4.x
//#include <QtGui/QApplication>

//QT 5.x
#include <QApplication>

#include "engine.h"
#include "test.h"

int main(int argc, char *argv[])
{
    qDebug("main start...");
    QApplication a(argc, argv);


    Test *t = new Test();


    qDebug("main end...");
    return a.exec();
}

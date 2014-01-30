//QT 4.x
//#include <QtGui/QApplication>

//QT 5.x
#include <QApplication>

#include "engine.h"
#include <qDebug>


#include "Graphics/Model/Parser/loader.h"
#include "Graphics/Model/modellibrary.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Engine e;
    e.showDebugWindow();
    e.initialize(argc, argv);
    e.setWindowTitle("Engine v0.001a");

    qDebug("back to main.cpp");


    Model * m = e.loadModel("C://Users//AJ//Desktop//Code//QTProjects//Engine//Engine//misc//models//box.obj");
    e.debugMessage(m->get_path());
    e.debugMessage(QString::number(m->id()));


    /*
    Model * m2 = e.loadModel("C://Users//AJ//Desktop//Code//QTProjects//Engine//Engine//misc//models//kv3.obj");
    e.debugMessage(m2->get_path());
    e.debugMessage(QString::number(m2->id()));
    */

    /*
    Model * mp = &m;

    Model mn = *mp;

    e.debugMessage(mn.get_path());
    e.debugMessage(QString::number(mn.id()));

    */

    return a.exec();
}

//QT 4.x
//#include <QtGui/QApplication>

//QT 5.x
#include <QApplication>

#include "engine.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Engine e;
    e.showDebugWindow();
    e.initialize(argc, argv);
    e.setWindowTitle("Engine v0.001a");

    Camera * cam = new Camera();
    cam->translate(0.0f,0.0f,30.0f);
    e.setCamera(cam);

    Model * m = e.loadModel("C://Users//AJ//Desktop//Code//QTProjects//Engine//Engine//misc//models//kv3.obj");

    return a.exec();
}

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
    e.setWindowSize(600,400);

    Camera * cam = new Camera();
    cam->translate(0.0f,0.0f,100.0f);
    e.setCamera(cam);

    Model * m = e.loadModel("C://Users//AJ//Desktop//Code//QTProjects//Engine//Engine//misc//models//kv3.obj");
    m->set_scale(2.0f,2.0f,2.0f);

    Model * m2 = e.loadModel("C://Users//AJ//Desktop//Code//QTProjects//Engine//Engine//misc//models//box.obj");
    m2->set_position(30.0f,0.0f,0.0f);
    m2->set_scale(0.09f,0.09f,0.09f);

    Model * m3 = e.loadModel("C://Users//AJ//Desktop//Code//QTProjects//Engine//Engine//misc//models//box.obj");
    m3->set_position(-30.0f,0.0f,0.0f);
    m3->set_scale(0.09f,0.09f,0.09f);

    Model * m4 = e.loadModel("C://Users//AJ//Desktop//Code//QTProjects//Engine//Engine//misc//models//kv3.obj");
    m4->set_scale(2.0f,2.0f,2.0f);
    m4->set_position(0.0f,0.0f,-50.0f);


    return a.exec();
}

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
    cam->Z_FAR = 20000.0;
    cam->translate(0.0,50.0,0.0);
    cam->rotate_global_post_x(15.0);
    e.setCamera(cam);

    Model *m = e.loadModel("C://Users//AJ//Desktop//Code//QTProjects//Engine//Engine//misc//models//space_box.obj");
    m->set_scale(1100.0,1100.0,1100.0);
    m->set_rotation(105.0,0.0,0.0);


    Model *m2 = e.loadModel("C://Users//AJ//Desktop//Code//QTProjects//Engine//Engine//misc//models//betty.obj");
    m2->set_scale(0.05,0.05,0.05);
    m2->set_position(200.0,0.0,0.0);

    return a.exec();
}

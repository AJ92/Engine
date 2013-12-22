//QT 4.x
//#include <QtGui/QApplication>

//QT 5.x
#include <QApplication>

#include "engine.h"
#include <qDebug>


#include "Graphics/Model/Parser/loader.h"


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    Engine e;
    e.showDebugWindow();
    e.initialize(argc, argv);
    e.setWindowTitle("Engine v0.001a");

    qDebug("back to main.cpp");

    Loader * l = new Loader();
    Model m = l->import_model("C://Users//AJ//Desktop//Code//QTProjects//Engine//Engine//misc//models//box.obj");
    qDebug(m.to_string().toUtf8());

    return a.exec();
}

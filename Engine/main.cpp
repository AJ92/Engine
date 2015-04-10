//QT 4.x
//#include <QtGui/QApplication>

//QT 5.x
#include <QApplication>

#include "engine.h"
#include "test.h"

////////
// FOR WINDOWS AND NVIDIA OPTIMUS
// FORCE TO USE HIGH PERFORMANCE CARD

#include "windows.h"
extern "C" {
    __declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}

// END WINDOWS ONLY...
///////

///////
/// DWORD substitution actually same as above...
/*
#include "stdint.h"
extern "C" {
    __declspec(dllexport) uint32_t NvOptimusEnablement = 0x00000001;
}
*/
//
///////

int main(int argc, char *argv[])
{
    qDebug("main start...");
    QApplication a(argc, argv);



    Test *t = new Test();



    qDebug("main end...");
    return a.exec();
}

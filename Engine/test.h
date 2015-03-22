#ifndef TEST_H
#define TEST_H

#include "engine.h"
#include <QList>
#include "Object/SmartPointer/smartpointer.h"

class Event;

class Test : public Quark::Engine
{
public:
    Test();


private:

    //some stuff

    //mouse
    double x_angle;
    double y_angle;

    QList<Light*> lights;
    double lighttime;

    void keyFunction();
    void mouseFunction();

    double mPosX;
    double mPosY;

    double mSpeedX;
    double mSpeedY;

    void eventCall();

    int level_loaded;
    bool lvl_loaded;
    int test_amount;
    QList<SP<CompositeObject> > compositeobjecttest;

};

#endif // TEST_H

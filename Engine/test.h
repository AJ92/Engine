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

    QList<SP<CompositeObject> > lights;
    double lighttime;

    void keyFunction(double fs);
    void mouseFunction(double fs);

    double mPosX;
    double mPosY;

    void eventCall(double fs);

    int level_loaded;
    bool lvl_loaded;
    int test_amount;
    QList<SP<CompositeObject> > compositeobjecttest;

};

#endif // TEST_H

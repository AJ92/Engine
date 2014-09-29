#ifndef TEST_H
#define TEST_H

#include "engine.h"
#include <QList>

class Event;

class Test : public Engine
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

    void eventCall();

    //Test octtree
    OctTree * ot;


    bool level_loaded;
    int test_amount;
    QList<CompositeObject *> compositeobjecttest;
};

#endif // TEST_H

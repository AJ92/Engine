#ifndef TEST_H
#define TEST_H

#include "engine.h"

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

    bool level_loaded;

    //Test octtree
    OctTree * ot;
};

#endif // TEST_H

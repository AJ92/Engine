#include "test.h"

#include "Event/event.h"
#include "Object/positation.h"


Test::Test() :
    Engine()
{

    qDebug("1");

    x_angle = 0.0;
    y_angle = 0.0;

    lighttime = 0;

    //init engine
    showDebugWindow();
    initialize(0, 0);

    qDebug("2");

    setClearColor(0.03f,0.02f,0.05f,0.0f);
    //setClearColor(0.3f,0.3f,0.4f,0.0f);

    setWindowTitle("Engine v0.001a");
    setWindowSize(800,600);

    qDebug("3");

    Camera * cam = new Camera();
    cam->setZFAR(5000.0);
    cam->set_position(0.0,-1200.0,650.0);
    cam->set_rotation_local(-50.0,1.0,0.0,0.0);
    setCamera(cam);

    qDebug("4");

    //physics test
    //btDefaultCollisionConfiguration * collisionConfiguration = new btDefaultCollisionConfiguration();

    qDebug("Test constructed...");

    //key J, is the plane created yet ?
    level_loaded = false;

    test_amount = 1000;

    //Octree test

    /*
    ot = new OctTree(1000);
    ot->setDebugMdl(model_library,getApplicationDir() + "//cube.obj");
    */
}

void Test::keyFunction(){
    //ESC
    if(k->isPressed(1)){
        exit(EXIT_SUCCESS);
    }

    //1
    if(k->isPressed(2)){
        Event e1;
        e1.type = Event::EventDebuggerShow;
        this->transmit(e1);
        qDebug("show debugger");
    }

    //2
    if(k->isPressed(3)){
        Event e2;
        e2.type = Event::EventDebuggerHide;
        this->transmit(e2);
        qDebug("hide debugger");
    }

    //3
    if(k->isPressed(4)){
        r->setPolygonMode(Renderer::PolygonModeStandard);
    }
    //4
    if(k->isPressed(5)){
        r->setPolygonMode(Renderer::PolygonModeStandard | Renderer::PolygonModeWireframe);
    }
    //5
    if(k->isPressed(6)){
        r->setPolygonMode(Renderer::PolygonModeStandard | Renderer::PolygonModeVertex);
    }
    //6
    if(k->isPressed(7)){
        r->setPolygonMode(Renderer::PolygonModeStandard | Renderer::PolygonModeVertex | Renderer::PolygonModeWireframe);
    }
    //L
    if(k->isPressed(38))
    {

        int count = 1000;
        for(int i = 0; i < count; i++){
            Positation * posi = new Positation();
            posi->set_position((double)((rand() & 1000)-500),
                              (double)((rand() & 1000)-500),
                              (double)((rand() & 1000)-500));

            posi->set_scale(3.0,3.0,3.0);
            CompositeObject * coTest = loadModelObject("tree", getApplicationDir() + "//tree.obj", posi);
        }
        /*
        model_library->setModelsPerThread(1);
        int count = 10;
        for(int i = 0; i < count; i++){
            Model * m = loadModel(getApplicationDir() + "//tree.obj");



            m->set_scale(5.92f,5.92f,5.92f);

            m->set_position((double)((rand() & 2000)-1000),
                            (double)((rand() & 2000)-1000),
                            10.0);

            m->set_rotation(rand() & 361,0.0,0.0,1.0);

            //ot->addModel(m);
        }
        */

        //debugMessage(ot->debug_string());
    }

    //c
    if(k->isPressed(46))
    {
        model_library->setModelsPerThread(1);

        Model * m = loadModel(getApplicationDir() + "//cube.obj");

    }

    //M
    if(k->isPressed(50))
    {
        /*
        light_library->setLightsPerThread(1);

        int count = 5;
        for(int i = 0; i < count; i++){
            Light * l = loadLight(getApplicationDir() + "//light_sphere.obj");


            double red = ((double)(rand() & 800)+200)* 0.001;
            double green = ((double)(rand() & 800)+200)* 0.001;
            double blue = ((double)(rand() & 800)+200)* 0.001;

            l->setDiffuseColor(red,
                               green,
                               blue);
            l->setSpecularColor(red,
                                green,
                                blue);

            //l->getModel()->set_scale(11.12f,11.12f,11.12f);
            l->getModel()->set_scale(51.12f,51.12f,51.12f);
            l->getModel()->set_position((double)((rand() & 2000)-1000) + (double)((rand() & 1000)-500) * 0.05,
                                        (double)((rand() & 2000)-1000) + (double)((rand() & 1000)-500) * 0.05,
                                        100.0 + (double)((rand() & 100)-50));
            lights.append(l);
        }
        */
    }

    //J
    if(k->isPressed(36))
    {
        if(!level_loaded){
            for(int i = 0; i < test_amount; i++){
                compositeobjecttest.append(loadModelObject("betty",
                                                           getApplicationDir() +
                                                           "//betty.obj"));
            }
            level_loaded = true;
        }
        else{
            for(int i = 0; i < test_amount; i++){
                compositeobjecttest.at(i)->getPositation()->set_position((double)((rand() & 1000)-500),
                                                                         (double)((rand() & 1000)-500),
                                                                         (double)((rand() & 1000)-500));
            }
        }
    }

    //K
    if(k->isPressed(37))
    {
        int count = 100;
        for(int i = 0; i < count; i++){
            Positation * posi = new Positation();
            posi->set_position((double)((rand() & 1000)-500),
                              (double)((rand() & 1000)-500),
                              (double)((rand() & 1000)-500));

            posi->set_scale(3.0,3.0,3.0);
            CompositeObject * coTest = loadModelObject("box", getApplicationDir() + "//box.obj", posi);
        }
        /*
        model_library->setModelsPerThread(1);
        Model * m = loadModel(getApplicationDir() + "//betty.obj");
        m->set_scale(0.92f,0.92f,0.92f);
        m->set_position((double)((rand() & 2000)-1000) + (double)((rand() & 1000)-500) * 0.05,
                        (double)((rand() & 2000)-1000) + (double)((rand() & 1000)-500) * 0.05,
                        35.0);
        m->set_rotation(90.0,1.0,0.0,0.0);
        */
    }

    //0
    if(k->isPressed(11)){
        //glutFullScreenToggle();
    }
    //Scharfes S
    if(k->isPressed(10)){
        model_library->debugModelData();
    }

    if(k->isPressed(24)){
        light_library->debugLightModelData();
    }

    /*
    x_angle += getTimeStep() * 0.2 * double(m->posX());
    y_angle += getTimeStep() * 0.2 * double(m->posY());

    getCamera()->clear_rotation_local();
    //around y axis
    getCamera()->add_rotation_local(x_angle,Vector3(0.0,1.0,0.0));
    //around x axis
    getCamera()->add_rotation_local(y_angle,Vector3(1.0,0.0,0.0));
    */

    double speed_up = 1.0;
    if(k->isPressed(42)){
        speed_up = 10.0;
    }

    //Q W E A S D
    if(k->isPressed(17)){
        Vector3 cam_pos = getCamera()->getPosition();
        getCamera()->set_position(cam_pos.x(),cam_pos.y() + 1.0*getTimeStep()* speed_up,cam_pos.z());
    }

    if(k->isPressed(30)){
        Vector3 cam_pos = getCamera()->getPosition();
        getCamera()->set_position(cam_pos.x() - 1.0*getTimeStep() * speed_up,cam_pos.y(),cam_pos.z());
    }
    if(k->isPressed(31)){
        Vector3 cam_pos = getCamera()->getPosition();
        getCamera()->set_position(cam_pos.x(),cam_pos.y() - 1.0*getTimeStep() * speed_up,cam_pos.z());
    }
    if(k->isPressed(32)){
        Vector3 cam_pos = getCamera()->getPosition();
        getCamera()->set_position(cam_pos.x() + 1.0*getTimeStep() * speed_up,cam_pos.y(),cam_pos.z());
    }

    if(k->isPressed(16)){
        Vector3 cam_pos = getCamera()->getPosition();
        getCamera()->set_position(cam_pos.x(),cam_pos.y(),cam_pos.z() - 1.0*getTimeStep() * speed_up);
    }
    if(k->isPressed(18)){
        Vector3 cam_pos = getCamera()->getPosition();
        getCamera()->set_position(cam_pos.x(),cam_pos.y(),cam_pos.z() + 1.0*getTimeStep() * speed_up);
    }
}

void Test::eventCall(){
    keyFunction();

    /*
    for(int i = 0; i < lights.size(); i++){
        Model *m = lights[i]->getModel();
        m->set_position(m->getPosition().x()+sin(lighttime)*5.0,
                        m->getPosition().y()+cos(lighttime)*5.0,
                        m->getPosition().z());
    }

    lighttime += 0.022 * getTimeStep();
    */

}

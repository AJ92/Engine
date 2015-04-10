//python test
#include <cmath>
#include "Python.h"




#include "test.h"

#include "Event/event.h"
#include "Object/positation.h"



Test::Test() :
    Quark::Engine()
{
    x_angle = 0.0;
    y_angle = 0.0;

    lighttime = 0;

    //init engine
    showDebugWindow();
    initialize(0, 0);


    setWindowTitle("Quark v1.0b");
    setWindowSize(800,600);


    Camera * camera = new Camera();
    camera->setFOV(45.0);
    camera->setZNEAR(1.0);
    camera->setZFAR(100000000.0);
    camera->set_position(0.0,-1200.0,650.0);
    camera->set_rotation_local(-50.0,1.0,0.0,0.0);
    setCamera(camera);

    //physics test
    //btDefaultCollisionConfiguration * collisionConfiguration = new btDefaultCollisionConfiguration();



    qDebug("Test constructed...");

    //key J, is the plane created yet ?
    level_loaded = 0;

    test_amount = 5;

    lvl_loaded = false;

    mPosX = 0;
    mPosY = 0;


    //python test...
    Py_SetProgramName(L"python test");  /* optional but recommended */
    Py_Initialize();
    PyRun_SimpleString("from time import time,ctime\n"
                       "print (ctime(time()))\n");
    Py_Finalize();


}


void Test::mouseFunction(double fs){
    double temp_x = m->posX();
    double temp_y = m->posY();


    if(m->isPressed(0)){
        getCamera()->add_rotation_local((mPosX - temp_x)*0.1*fs ,0.0,1.0,0.0);
        getCamera()->add_rotation_local((mPosY - temp_y)*0.1*fs ,1.0,0.0,0.0);
    }

    mPosX = temp_x;
    mPosY = temp_y;
}


void Test::keyFunction(double fs){
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


    //7
    if(k->isPressed(8)){
        r->setPolygonMode(Renderer::PolygonModeStandard | Renderer::PolygonModeLightVertex);
    }
    //8
    if(k->isPressed(9)){
        r->setPolygonMode(Renderer::PolygonModeStandard | Renderer::PolygonModeLightWireframe);
    }
    //9
    if(k->isPressed(10)){
        r->setPolygonMode(Renderer::PolygonModeStandard | Renderer::PolygonModeOctTreeWireframe);
    }
    //0
    if(k->isPressed(11)){
        r->setPolygonMode(Renderer::PolygonModeStandard | Renderer::PolygonModeOctTreeVertex);
    }


    //F1(59) turn off all PP modes
    if(k->isPressed(59)){
        r->setPostProcessingMode(Renderer::PostProcessingModeNone);
    }
    //F2(60) turn on PostProcessingModeFXAA
    if(k->isPressed(60)){
        r->setPostProcessingMode(Renderer::PostProcessingModeFXAA |
                                 r->getPostProcessingMode());
    }
    //F3(61) turn on PostProcessingModeSharpen
    if(k->isPressed(61)){
        r->setPostProcessingMode(Renderer::PostProcessingModeSharpen |
                                 r->getPostProcessingMode());
    }
    //F4(62) turn on PostProcessingModeSSAO
    if(k->isPressed(62)){
        r->setPostProcessingMode(Renderer::PostProcessingModeSSAO |
                                 r->getPostProcessingMode());
    }
    //F5(63) turn on PostProcessingModeBlurH
    if(k->isPressed(63)){
        r->setPostProcessingMode(Renderer::PostProcessingModeBlurH |
                                 r->getPostProcessingMode());
    }
    //F6(64) turn on PostProcessingModeBlurV
    if(k->isPressed(64)){
        r->setPostProcessingMode(Renderer::PostProcessingModeBlurV |
                                 r->getPostProcessingMode());
    }



    //L
    if(k->isPressed(38))
    {

        int count = 10;
        for(int i = 0; i < count; i++){
            SP<Positation> posi(new Positation());
            posi->set_position((double)((rand() & 2000)-1000),
                              (double)((rand() & 2000)-1000),
                              (double)((rand() & 2000)-1000));

            int rand_rot = (rand() & 2);
            if(rand_rot == 0){
                posi->set_rotation((double) (rand() & 360), 1, 0, 0);
            }
            else if(rand_rot == 1){
                posi->set_rotation((double) (rand() & 360), 0, 1, 0);
            }
            else if(rand_rot == 2){
                posi->set_rotation((double) (rand() & 360), 0, 0, 1);
            }

            posi->set_scale(5.5,5.5,5.5);
            SP<CompositeObject> coTest = loadModelObject("box", getApplicationDir() + "//box.obj", posi);
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


    //OE
    if(k->isPressed(39))
    {
        SP<Positation> posi(new Positation());
        posi->set_position((double)((rand() & 2000)-1000),
                          (double)((rand() & 2000)-1000),
                          (double)((rand() & 2000)-1000));
        posi->set_scale(0.5,0.5,0.5);
        SP<CompositeObject> coTest = loadModelObject("box", getApplicationDir() + "//box.obj", posi);
    }

    //c
    if(k->isPressed(46))
    {
        /*
        model_library->setModelsPerThread(1);

        Model * m = loadModel(getApplicationDir() + "//cube.obj");
        */
    }

    //M
    if(k->isPressed(50))
    {

        int count = 1;
        for(int i = 0; i < count; i++){
            SP<CompositeObject> coTest = loadLightObject("light");
            coTest->getPositation()->set_position((double)((rand() & 2000)-1000),
                                                (double)((rand() & 2000)-1000),
                                                (double)((rand() & 2000)-1000));
            coTest->getPositation()->set_scale(61.12f,61.12f,61.12f);


            SP<Light> l= coTest->getLight();

            double red = ((double)(rand() & 200))* 0.011;
            double green = ((double)(rand() & 200))* 0.011;
            double blue = ((double)(rand() & 200))* 0.011;


            /*
            double red = 0.5;
            double green = 0.5;
            double blue = 0.5;
            */

            l->setDiffuseColor(red,
                               green,
                               blue);
            l->setSpecularColor(red,
                                green,
                                blue);

            lights.append(coTest);
        }
    }

    //J
    if(k->isPressed(36))
    {
        if(level_loaded < 1){
            for(int i = 0; i < test_amount; i++){
                //betty

                compositeobjecttest.append(loadModelObject("betty",
                                                           getApplicationDir() +
                                                           "//betty.obj")); 


                //HN48-flying
                /*
                compositeobjecttest.append(loadModelObject("HN48-flying",
                                                           getApplicationDir() +
                                                           "/HN48/HN48-flying.obj"));
                                                           */

                //sd85
                /*
                compositeobjecttest.append(loadModelObject("sd85",
                                                           getApplicationDir() +
                                                           "/sd85/sd85.obj"));
                                                           */

            }
            level_loaded += 1;
        }
        else{
            for(int i = 0; i < compositeobjecttest.size(); i++){
                SP<CompositeObject> coTest = compositeobjecttest.at(i);
                coTest->getPositation()->set_position(  (double)((rand() & 2000)-1000),
                                                        (double)((rand() & 2000)-1000),
                                                        (double)((rand() & 2000)-1000));


                /*
                int rand_rot = (rand() & 2);
                if(rand_rot == 0){
                    coTest->getPositation()->set_rotation((double) (rand() & 360), 1, 0, 0);
                }
                else if(rand_rot == 1){
                    coTest->getPositation()->set_rotation((double) (rand() & 360), 0, 1, 0);
                }
                else if(rand_rot == 2){
                    coTest->getPositation()->set_rotation((double) (rand() & 360), 0, 0, 1);
                }
                */

                coTest->getPositation()->set_scale(0.3,0.3,0.3);


            }
        }
    }

    //g
    if(k->isPressed(34)){
        if(!lvl_loaded){
            SP<Positation> posi(new Positation());
            posi->set_position(0.0f, 0.0f, 0.0f);

            posi->set_scale(1.0,1.0,1.0);
            posi->set_rotation(90.0f,1.0f,0.0f,0.0f);
            SP<CompositeObject> coTest = loadModelObject("f16model", getApplicationDir() + "//f16//f16.obj", posi);
            //SP<CompositeObject> coTest = loadModelObject("city", getApplicationDir() + "//city2//Organodron City.obj", posi);
            //SP<CompositeObject> coTest = loadModelObject("city", getApplicationDir() + "//sponza//sponzalvl.obj", posi);
            lvl_loaded = true;
        }
    }

    //H
    if(k->isPressed(35)){
        level_loaded = 0;
    }

    //K
    if(k->isPressed(37))
    {
        if(!lvl_loaded){
            SP<Positation> posi(new Positation());
            posi->set_position(0.0f, 0.0f, 0.0f);

            posi->set_scale(1.0,1.0,1.0);
            posi->set_rotation(90.0f,1.0f,0.0f,0.0f);
            SP<CompositeObject> coTest = loadModelObject("city", getApplicationDir() + "//Paris//paris2.obj", posi);
            //SP<CompositeObject> coTest = loadModelObject("city", getApplicationDir() + "//city2//Organodron City.obj", posi);
            //SP<CompositeObject> coTest = loadModelObject("city", getApplicationDir() + "//sponza//sponzalvl.obj", posi);
            lvl_loaded = true;
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



    /*
    x_angle += getTimeStep() * 0.2 * double(m->posX());
    y_angle += getTimeStep() * 0.2 * double(m->posY());

    getCamera()->clear_rotation_local();
    //around y axis
    getCamera()->add_rotation_local(x_angle,Vector3(0.0,1.0,0.0));
    //around x axis
    getCamera()->add_rotation_local(y_angle,Vector3(1.0,0.0,0.0));
    */

    double speed_up = 2.0;
    //left shift
    if(k->isPressed(42)){
        speed_up = 60.0;
    }
    //left ctrl
    if(k->isPressed(29)){
        speed_up = 0.02;
    }



    //Q W E A S D

    double accel =  speed_up * fs;


    //W
    if(k->isPressed(17)){
        Vector3 cam_pos = getCamera()->getPosition();
        Vector3 cam_dir = getCamera()->getDirForward();

        getCamera()->set_position(cam_pos.x() - cam_dir[0] * accel,
                                  cam_pos.y() - cam_dir[1] * accel,
                                  cam_pos.z() - cam_dir[2] * accel);
    }
    //A
    if(k->isPressed(30)){
        Vector3 cam_pos = getCamera()->getPosition();
        Vector3 cam_dir = getCamera()->getDirRight();

        getCamera()->set_position(cam_pos.x() - cam_dir[0] * accel,
                                  cam_pos.y() - cam_dir[1] * accel,
                                  cam_pos.z() - cam_dir[2] * accel);
    }
    //S
    if(k->isPressed(31)){
        Vector3 cam_pos = getCamera()->getPosition();
        Vector3 cam_dir = getCamera()->getDirForward();

        getCamera()->set_position(cam_pos.x() + cam_dir[0] * accel,
                                  cam_pos.y() + cam_dir[1] * accel,
                                  cam_pos.z() + cam_dir[2] * accel);
    }
    //D
    if(k->isPressed(32)){
        Vector3 cam_pos = getCamera()->getPosition();
        Vector3 cam_dir = getCamera()->getDirRight();

        getCamera()->set_position(cam_pos.x() + cam_dir[0] * accel,
                                  cam_pos.y() + cam_dir[1] * accel,
                                  cam_pos.z() + cam_dir[2] * accel);
    }
    //Q
    if(k->isPressed(16)){
        Vector3 cam_pos = getCamera()->getPosition();
        Vector3 cam_dir = getCamera()->getDirUp();

        getCamera()->set_position(cam_pos.x() + cam_dir[0] * accel,
                                  cam_pos.y() + cam_dir[1] * accel,
                                  cam_pos.z() + cam_dir[2] * accel);
    }
    //Y
    if(k->isPressed(44)){
        Vector3 cam_pos = getCamera()->getPosition();
        Vector3 cam_dir = getCamera()->getDirUp();

        getCamera()->set_position(cam_pos.x() - cam_dir[0] * accel,
                                  cam_pos.y() - cam_dir[1] * accel,
                                  cam_pos.z() - cam_dir[2] * accel);
    }

    //X
    if(k->isPressed(45)){
        window->setWindowSize(1920,1080);
    }
}

void Test::eventCall(double fs){
    keyFunction(fs);
    mouseFunction(fs);

    for(int i = 0; i < lights.size(); i++){
        lights[i]->getPositation()->set_position(
                    lights[i]->getPositation()->getPosition().x()+sin(lighttime)*1.0,
                    lights[i]->getPositation()->getPosition().y()+cos(lighttime)*1.0,
                    lights[i]->getPositation()->getPosition().z());
    }

    lighttime += 0.005 * fs;


}

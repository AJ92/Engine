#include "test.h"

#include "Event/event.h"
#include "Object/positation.h"


Test::Test() :
    Engine()
{
    x_angle = 0.0;
    y_angle = 0.0;

    lighttime = 0;

    //init engine
    showDebugWindow();
    initialize(0, 0);

    setWindowTitle("Engine v0.01a");
    setWindowSize(800,600);


    Camera * camera = new Camera();
    camera->setZFAR(15000.0);
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

    mSpeedX = 0.0;
    mSpeedY = 0.0;
}


void Test::mouseFunction(){
    double temp_x = m->posX();
    double temp_y = m->posY();


    double min_speed = 0.2;
    double max_speed = 1.5;


    if(m->isPressed(0)){

        if(abs(mPosX - temp_x)>0.0 || abs(mPosY - temp_y)>0.0){
            if(mSpeedX < max_speed){
                mSpeedX += 0.1;
            }
            if(mSpeedY < max_speed){
                mSpeedY += 0.1;
            }
        }

        mSpeedX -= 0.09;
        if(mSpeedX < min_speed){
            mSpeedX = min_speed;
        }
        mSpeedY -= 0.09;
        if(mSpeedY < min_speed){
            mSpeedY = min_speed;
        }




        getCamera()->add_rotation_local((mPosX - temp_x)/4.0 *getTimeStep()*mSpeedX,0.0,1.0,0.0);
        getCamera()->add_rotation_local((mPosY - temp_y)/4.0 *getTimeStep()*mSpeedY,1.0,0.0,0.0);
    }
    else{
        mSpeedX = min_speed;
        mSpeedY = min_speed;
    }

    mPosX = temp_x;
    mPosY = temp_y;
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

            posi->set_scale(15.5,15.5,15.5);
            SP<CompositeObject> coTest = loadModelObject("tree", getApplicationDir() + "//box.obj", posi);
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
            coTest->getPositation()->set_scale(31.12f,31.12f,31.12f);


            SP<Light> l= coTest->getLight();
            double red = ((double)(rand() & 200))* 0.011;
            double green = ((double)(rand() & 200))* 0.011;
            double blue = ((double)(rand() & 200))* 0.011;

            l->setDiffuseColor(red,
                               green,
                               blue);
            l->setSpecularColor(red,
                                green,
                                blue);
        }
    }

    //J
    if(k->isPressed(36))
    {
        if(level_loaded < 1){
            for(int i = 0; i < test_amount; i++){
                compositeobjecttest.append(loadModelObject("betty",
                                                           getApplicationDir() +
                                                           "//betty.obj"));
            }
            level_loaded += 1;
        }
        else{
            for(int i = 0; i < compositeobjecttest.size(); i++){
                SP<CompositeObject> coTest = compositeobjecttest.at(i);
                coTest->getPositation()->set_position(  (double)((rand() & 2000)-1000),
                                                        (double)((rand() & 2000)-1000),
                                                        (double)((rand() & 2000)-1000));


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

                coTest->getPositation()->set_scale(0.2,0.2,0.2);

            }
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

    double speed_up = 1.0;
    if(k->isPressed(42)){
        speed_up = 10.0;
    }

    //Q W E A S D

    //W
    if(k->isPressed(17)){
        Vector3 cam_pos = getCamera()->getPosition();
        Vector3 cam_dir = getCamera()->getDirForward();

        getCamera()->set_position(cam_pos.x() - cam_dir[0] * getTimeStep()* speed_up,
                                  cam_pos.y() - cam_dir[1] * getTimeStep()* speed_up,
                                  cam_pos.z() - cam_dir[2] * getTimeStep()* speed_up);
    }
    //A
    if(k->isPressed(30)){
        Vector3 cam_pos = getCamera()->getPosition();
        Vector3 cam_dir = getCamera()->getDirRight();

        getCamera()->set_position(cam_pos.x() - cam_dir[0] * getTimeStep()* speed_up,
                                  cam_pos.y() - cam_dir[1] * getTimeStep()* speed_up,
                                  cam_pos.z() - cam_dir[2] * getTimeStep()* speed_up);
    }
    //S
    if(k->isPressed(31)){
        Vector3 cam_pos = getCamera()->getPosition();
        Vector3 cam_dir = getCamera()->getDirForward();

        getCamera()->set_position(cam_pos.x() + cam_dir[0] * getTimeStep()* speed_up,
                                  cam_pos.y() + cam_dir[1] * getTimeStep()* speed_up,
                                  cam_pos.z() + cam_dir[2] * getTimeStep()* speed_up);
    }
    //D
    if(k->isPressed(32)){
        Vector3 cam_pos = getCamera()->getPosition();
        Vector3 cam_dir = getCamera()->getDirRight();

        getCamera()->set_position(cam_pos.x() + cam_dir[0] * getTimeStep()* speed_up,
                                  cam_pos.y() + cam_dir[1] * getTimeStep()* speed_up,
                                  cam_pos.z() + cam_dir[2] * getTimeStep()* speed_up);
    }
    //Q
    if(k->isPressed(16)){
        Vector3 cam_pos = getCamera()->getPosition();
        Vector3 cam_dir = getCamera()->getDirUp();

        getCamera()->set_position(cam_pos.x() + cam_dir[0] * getTimeStep()* speed_up,
                                  cam_pos.y() + cam_dir[1] * getTimeStep()* speed_up,
                                  cam_pos.z() + cam_dir[2] * getTimeStep()* speed_up);
    }
    //Y
    if(k->isPressed(44)){
        Vector3 cam_pos = getCamera()->getPosition();
        Vector3 cam_dir = getCamera()->getDirUp();

        getCamera()->set_position(cam_pos.x() - cam_dir[0] * getTimeStep()* speed_up,
                                  cam_pos.y() - cam_dir[1] * getTimeStep()* speed_up,
                                  cam_pos.z() - cam_dir[2] * getTimeStep()* speed_up);
    }

    if(k->isPressed(45)){
        window->setWindowSize(1920,1080);
    }
}

void Test::eventCall(){
    keyFunction();
    mouseFunction();
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

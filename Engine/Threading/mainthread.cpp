#include "mainthread.h"



// C part
MainThread * ptr_global_mainthread_instance = NULL;

void render_callback(void);
void idle_callback(void);
void timer_callback(int value);
void keyboard_callback(unsigned char key, int x, int y);


void render_callback(void){
    ptr_global_mainthread_instance->render();
}

void idle_callback(void)
{
    ptr_global_mainthread_instance->idle();
}


void timer_callback(int value){
    ptr_global_mainthread_instance->timer(value);
}

void keyboard_callback(unsigned char key, int x, int y){
    ptr_global_mainthread_instance->keyboard(key, x, y);
}
// C part END




//THREAD
MainThread::MainThread(Engine * parent, Window * w) :
    EventListener(),
    EventTransmitter(),
    QThread(),
    running(false),
    abort(false),
    parent(parent),
    w(w)
{
    ptr_global_mainthread_instance = this;
}

void MainThread::init(){
    debugMessage("creating renderer...");
    r = new Renderer();
    r->addListener(this);
    r->initialize();

    r->setPolygonMode(Renderer::PolygonModeFill);
}

MainThread::~MainThread(){
    //destructor: stop thread...
    mutex.lock();
    abort = true;
    running = false;
    mutex.unlock();
    wait();
}

void MainThread::start_mainThread(){
    QMutexLocker locker(&mutex);

    running = true;
    abort = false;

    if (!isRunning()) {
        debugMessage("Starting MainThread...");
        start(LowPriority);
        //start(HighPriority);
    }
    else{
        debugMessage("MainThread already running...");
        qDebug("MainThread already running...");
    }
}

void MainThread::stop_mainThread(){
    QMutexLocker locker(&mutex);
    running = false;
    abort = true;
}

void MainThread::run(){

    //register c function callbacks
    glutDisplayFunc(&render_callback);
    //glutCloseFunc(&close_callback);
    glutIdleFunc(&idle_callback);
    glutTimerFunc(0, &timer_callback, 0);
    glutKeyboardFunc(&keyboard_callback);

    while(w->isOpen()){
        if (abort){
            //debugMessage("Mainthread aborting...");
            qDebug("MainThread aborting...");
            return;
        }

        mutex.lock();
        //copy thread sensitive data...
        mutex.unlock();

        glutMainLoopEvent();

        usleep(50000); // 50000 microseconds sleep (every 2nd frame at ~ 40 fps)

        //work here
    }

    if(!w->isOpen()){
        stop_mainThread();
    }


    //Thread needs to sleep too :D
    mutex.lock();
    if(!running){
        //parent->debugMessage("MainThread stopped.");
        qDebug("MainThread stopped.");
        condition.wait(&mutex);
    }
    mutex.unlock();
}



//CALLBACKS
void MainThread::keyboard(unsigned char key, int x, int y)
{
    debugMessage("Keypress: " + QString(key));
    switch (key)
    {
    case '\x1B':
        exit(EXIT_SUCCESS);
        break;
    case '1':
        {
            Event e1;
            e1.type = Event::EventDebuggerShow;
            this->transmit(e1);
        }
        break;
    case '2':
        {
            Event e2;
            e2.type = Event::EventDebuggerHide;
            this->transmit(e2);
        }
        break;
    }
}

void MainThread::idle(){
    glutPostRedisplay();
}

void MainThread::timer(int value){
    if (0 != value) {
        fps = frame_count * 4;
    }
    frame_count = 0;
    glutTimerFunc(250, &timer_callback, 1);
}


void MainThread::render()
{
    frame_count++;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    r->render();

    glutSwapBuffers();
    glutPostRedisplay();
}

void MainThread::eventRecieved(Event e){
    if(e.type == Event::EventDebuggerMessage){
        debugMessage(e.debugger->getDebugMessage());
        return;
    }
}

void MainThread::debugMessage(QString message){
    Event e;
    e.type = Event::EventDebuggerMessage;
    EventDebugger * ed = new EventDebugger(message);
    e.debugger = ed;
    this->transmit(e);
}

void MainThread::setModels(ModelLibrary modellib){
    mutex.lock();
    //copy thread sensitive data...
    model_library = modellib;
    debugMessage("MainThread has new modellib...");
    //might need to copy model after model so a thread context switch does not happen...

    mutex.unlock();
}

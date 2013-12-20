#include "mainthread.h"



// C part
MainThread * ptr_global_mainthread_instance = NULL;

void render_callback(void);
void idle_callback(void);
void timer_callback(int value);
void keyboard_callback(unsigned char key, int x, int y);


void render_callback(){
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
MainThread::MainThread(QObject *parent) :
    EventListener(),
    EventTransmitter(),
    QThread(parent),
    running(false),
    abort(false)
{
    ptr_global_mainthread_instance = this;
}

void MainThread::init(){
    debugMessage("creating renderer...");
    r = new Renderer();
    r->addListener(this);
    r->initialize();
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
        start(LowPriority);
        //start(HighPriority);
    }
    else{
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

    while(true){
        if (abort){
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


    //Thread needs to sleep too :D
    mutex.lock();
    if(!running){
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
    /* OLD STUFF
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 0.0f, 0.0f);

    glBegin(GL_POLYGON);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f( 0.5f, -0.5f);
    glVertex2f( 0.5f,  0.5f);
    glVertex2f(-0.5f,  0.5f);
    glEnd();

    glFlush();
    */

    frame_count++;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    r->render();

    glutSwapBuffers();
    glutPostRedisplay();

}

void MainThread::eventRecieved(Event e){
    if(e.isType(Event::EventDebuggerMessage)){
        debugMessage(e.getString());
        return;
    }
}

void MainThread::debugMessage(QString message){
    Event e(Event::EventDebuggerMessage);
    e.setString(message);
    this->transmit(e);
}


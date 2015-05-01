#ifndef STREAMER_H
#define STREAMER_H

#include <QObject>
#include <QThread>
#include "Event/eventlistener.h"
#include "Event/eventtransmitter.h"

#include "Graphics/Model/Streamer/streamToDisk.h"
//#include "Graphics/Model/model.h"

#include <QList>
#include <map>

#include <QTimer>

#include "Threading/threadaccountant.h"
#include "Object/SmartPointer/smartpointer.h"

class Event;
class Model;

class Streamer : public QObject, virtual public EventListener, virtual public EventTransmitter
{
    Q_OBJECT
public:
    explicit Streamer(SP<ThreadAccountant> ta, QObject *parent = 0);

    virtual ~Streamer();

    void initialize();

    void streamModelToDisk(SP<Model> m);
    void streamModelFromDisk(SP<Model> m);

    void setModelsPerThread(int model_count);

    
private:
    int models_per_thread;

    void assignModelListToThread(QList<SP<Model> > model_list);

    SP<ThreadAccountant> ta;

    //Timer to check for waiting model loads...
    QTimer * t;

    //model queue for models that wait for a thread
    QList<Model* > model_list;

    //model queue for models that are done and need to load GL DATA
    QList<SP<Model> > finished_model_list;

    //store the model ID  and  the Model pointer
    std::map<unsigned long long, SP<Model> > id_model_map;

public slots:
    void debugMessage(QString message);

    void timerEvent();

    //called by timer to assign model to a thread
    void assignModeltoThread();

    void streamModelToDiskFinished(SP<Model> m, unsigned long long id);
    void streamModelFromDiskFinished(SPModel m, unsigned long long id);

    void streamThreadFinished();
    

    
};

#endif // STREAMER_H

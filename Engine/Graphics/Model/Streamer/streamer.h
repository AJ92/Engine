#ifndef STREAMER_H
#define STREAMER_H

#include <QObject>
#include <QThread>
#include "Event/eventtransmitter.h"

#include "Graphics/Model/Streamer/streamToDisk.h"
#include "Graphics/Model/model.h"

#include <list>
#include <map>

#include <QTimer>

#include "Threading/threadaccountant.h"

class Streamer : public QObject, virtual public EventListener, virtual public EventTransmitter
{
    Q_OBJECT
public:
    explicit Streamer(ThreadAccountant * ta, QObject *parent = 0);

    void initialize();

    void streamModelToDisk(Model * m);
    void streamModelFromDisk(Model * m);
    
private:
    ThreadAccountant * ta;

    //Timer to check for waiting model loads...
    QTimer * t;

    //model queue for models that wait for a thread
    std::queue<Model*> model_queue;

    //model queue for models that are done and need to load GL DATA
    std::queue<Model*> finished_model_queue;

    //store the model ID  and  the Model pointer
    std::map<unsigned long long, Model*> id_model_map;

public slots:
    void debugMessage(QString message);

    //called by timer to assign model to a thread
    void assignModeltoThread();

    void streamModelToDiskFinished(Model * m, unsigned long long id);
    void streamModelFromDiskFinished(Model * m, unsigned long long id);


    

    
};

#endif // STREAMER_H

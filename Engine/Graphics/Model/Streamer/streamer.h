#ifndef STREAMER_H
#define STREAMER_H

#include <QObject>
#include <QThread>
#include "Event/eventtransmitter.h"

#include "Graphics/Model/Streamer/streamToDisk.h"
#include "Graphics/Model/model.h"

#include <list>
#include <map>

class Streamer : public QObject, virtual public EventListener, virtual public EventTransmitter
{
    Q_OBJECT
public:
    explicit Streamer(int maxThreads, QObject *parent = 0);

    void initialize();

    void streamModelToDisk(Model * m);
    void streamModelFromDisk(Model * m);
    
private:
    int maxThreads;
    int threadsInUse;

    //store the model ID  and  the Model pointer
    std::map<unsigned long long, Model*> id_model_map;

public slots:
    void debugMessage(QString message);
    void streamModelToDiskFinished(Model * m, unsigned long long id);
    void streamModelFromDiskFinished(Model * m, unsigned long long id);
    

    
};

#endif // STREAMER_H

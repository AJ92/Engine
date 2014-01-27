#ifndef STREAMTODISK_H
#define STREAMTODISK_H

#include <QThread>
#include <QWaitCondition>
#include <QMutexLocker>
#include <QMutex>
#include <QString>

#include "Graphics/OpenGL/OpenGL.h"

#include "Event/eventtransmitter.h"

#include "Graphics/Model/Parser/loader.h"
#include "Graphics/Model/model.h"

class StreamToDisk : public QObject
{
    Q_OBJECT
public:
    StreamToDisk(Model * mdl, QObject * parent = 0);
    ~StreamToDisk();

public slots:
    void stream();

signals:
    void finished(Model * m, unsigned long long id);
    void error(QString error);

private:
    //internal data storage starts from here...
    Loader model_loader;
    Model * m;
    unsigned long long mdl_id;
};

#endif // STREAMTODISK_H

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

#include <QList>

class StreamToDisk : public QObject
{
    Q_OBJECT
public:
    StreamToDisk(QList<Model*> model_list_for_thread, QObject * parent = 0);
    ~StreamToDisk();

public slots:
    void stream();

signals:
    void loaded(Model* m, unsigned long long id);
    void finished();
    void error(QString error);

private:
    //internal data storage starts from here...
    Loader model_loader;
    QList<Model*> model_list;
    QList<unsigned long long> model_id_list;
};

#endif // STREAMTODISK_H

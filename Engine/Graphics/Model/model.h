#ifndef MODEL_H
#define MODEL_H

#include "Object/object.h"

#include "Event/eventtransmitter.h"

#include <QList>


class Mesh;
class Material;
class Event;

class CompositeObject;

class Model : virtual public EventTransmitter
{
public:
    //create a copy from mdl...
    Model(const Model & mdl);
    //construct empty Model
    Model();

    //override
    void set_data(const Model &mdl);
    void instance_from(const Model &mdl);

    void set_path(QString path);
    QString get_path() const;

    void add_mesh(Mesh* mesh);

    QList<Mesh*> get_meshs();

    void loadGLdata();
    bool isReadyToRender();

    bool equalData(const Model &mdl) const;

    void setParentCompositeObject(CompositeObject * co);
    CompositeObject * getParentCompositeObject();

    //override + overload bam
    bool equal(const Model &mdl) const;

    friend bool operator==(const Model &mdl1, const Model &mdl2);

private:
    bool isReady;

    QString path;

    QList<Mesh*> meshs;

    //a pointer to its compositeObject if it has one..
    //used by the renderer to get to the location data...
    CompositeObject * parent_co;
};

#endif // MODEL_H

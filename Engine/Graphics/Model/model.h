#ifndef MODEL_H
#define MODEL_H

#include "Graphics/Model/entity.h"

#include "Graphics/Model/Components/material.h"
#include "Graphics/Model/Components/mesh.h"

#include <QList>

class Mesh;

class Model : public Entity
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

    //override + overload bam
    bool equal(const Model &mdl) const;

    friend bool operator==(const Model &mdl1, const Model &mdl2);

private:
    bool isReady;

    QString path;

    QList<Mesh*> meshs;
};

#endif // MODEL_H

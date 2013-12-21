#ifndef LOADER_OBJ_H
#define LOADER_OBJ_H


#include "Graphics/OpenGL/OpenGL.h"

#include "Graphics/Model/model.h"


#include "Math/Vector/vector3.h"

#include <QMap>
#include <QVector>

#include <QString>
#include <QStringList>

#include <QList>

#include <QFile>
#include <QTextStream>

class Model;

class Loader_obj
{
public:
    Loader_obj();

    bool load_model_data(Model& mdl, QString path);

};

#endif // LOADER_OBJ_H

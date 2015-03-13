#ifndef LOADER_H
#define LOADER_H

//load files
#include <QString>
#include <QStringList>

#include "Object/SmartPointer/smartpointer.h"

#include "Graphics/Model/model.h"
#include "Graphics/Model/Parser/Format_obj/loader_obj.h"
#include "Graphics/Model/Parser/Format_assimp/loader_assimp.h"


class Model;

class Loader
{
public:
    Loader();
    SP<Model> import_model(QString path);

    //future binary exporter...
    bool export_model_bin(QString path, SP<Model> mdl);

private:
    //future binary model loader
    SP<Model> import_model_format_bin(QString path);

    //kept for backwards reference
    SP<Model> import_model_format_obj(QString path);

    //assimp loader
    SP<Model> import_model_with_assimp(QString path);
};

#endif // LOADER_H

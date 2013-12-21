#ifndef LOADER_H
#define LOADER_H

//load files
#include <QString>
#include <QStringList>

#include "Graphics/Model/model.h"

#include "Graphics/Model/Parser/Format_obj/loader_obj.h"

class Model;

class Loader
{
public:
    Loader();
    Model import_model(QString path);
    bool export_model_bin(QString path, Model mdl);

private:
    Model import_model_format_bin(QString path);
    Model import_model_format_fbx(QString path);
    Model import_model_format_obj(QString path);
};

#endif // LOADER_H

#include "loader.h"

//constructor not needed ... class receives static functions anyways...
Loader::Loader()
{
}

//static
Model * Loader::import_model(QString path){
    QStringList pathlist = path.split(".");
    QString suffix = pathlist.last();

    if(suffix.compare("fbx")==0){
        return import_model_format_fbx(path);
    }
    else if(suffix.compare("bin")==0){
        return import_model_format_bin(path);
    }
    else if(suffix.compare("obj")==0){
        return import_model_format_obj(path);
    }
    qDebug("no suitable format detected...");
    return new Model();
}

//static
bool Loader::export_model_bin(QString path, Model * mdl){
    return true;
}

//static
Model * Loader::import_model_format_bin(QString path){
    return new Model();
}

//static
Model * Loader::import_model_format_fbx(QString path){
    return new Model();
}

//static
Model * Loader::import_model_format_obj(QString path){
    Model * mdl = new Model();

    Loader_obj loader_obj;

    if(!loader_obj.load_model_data(*mdl,path)){
        qDebug("  import of obj mdl FAILED.");
    }
    return mdl;
}

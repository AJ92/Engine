#include "loader.h"

//constructor not needed ... class receives static functions anyways...
Loader::Loader()
{
}

//static
SP<Model> Loader::import_model(QString path){
    QStringList pathlist = path.split(".");
    QString suffix = pathlist.last();

    if(suffix.compare("bin")==0){
        return import_model_format_bin(path);
    }
    /*
    else if(suffix.compare("obj")==0){
        return import_model_format_obj(path);
    }
    */
    else{
        return import_model_with_assimp(path);
    }

    qDebug("no suitable format detected...");
    return new Model();
}

//static
bool Loader::export_model_bin(QString path, SP<Model> mdl){
    return true;
}






//static
SP<Model> Loader::import_model_format_bin(QString path){
    return new Model();
}

//static
SP<Model> Loader::import_model_format_obj(QString path){
    SP<Model> mdl = new Model();

    Loader_obj loader_obj;

    if(!loader_obj.load_model_data(*mdl,path)){
        qDebug("  import of deprecated obj mdl FAILED.");
    }
    return mdl;
}

//static
SP<Model> Loader::import_model_with_assimp(QString path){
    SP<Model> mdl = new Model();

    Loader_assimp loader_assimp;

    if(!loader_assimp.load_model_data(*mdl,path)){
        qDebug("  import of mdl with assimp FAILED.");
    }
    return mdl;

}

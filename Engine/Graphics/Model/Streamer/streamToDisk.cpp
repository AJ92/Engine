#include "streamToDisk.h"

StreamToDisk::StreamToDisk(Model * mdl, QObject * parent) :
    QObject(parent)
{
   m = new Model(*mdl);
   mdl_id = mdl->id();
}

StreamToDisk::~StreamToDisk(){
    //clean up
}


//SLOTS
void StreamToDisk::stream(){
    m = model_loader.import_model(m->get_path());
    emit finished(m, mdl_id);
}


//SIGNALS
void finished(Model * m, unsigned long long id){

}

void error(QString error){

}

#include "streamToDisk.h"

StreamToDisk::StreamToDisk(QList<Model *> model_list_for_thread)
{
    //copy models into thread...
    QList<Model*>::iterator i;
    for (i = model_list_for_thread.begin(); i != model_list_for_thread.end(); ++i){
        Model *m = *i;
        model_list.append(new Model(*m));
        model_id_list.append(m->Entity::id());
    }
}

StreamToDisk::~StreamToDisk(){
    //clean up
}


//SLOTS
void StreamToDisk::stream(){
    for (int i = 0; i < model_list.size(); ++i){
        Model * m = model_list.at(i);
        m = model_loader.import_model(m->get_path());
        emit loaded(m,model_id_list.at(i));
    }
    emit finished();
}


//SIGNALS
void loaded(Model* m, unsigned long long id){

}

void finished(){

}

void error(QString error){

}

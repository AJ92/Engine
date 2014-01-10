#include "modellibrary.h"

ModelLibrary::ModelLibrary() :
    Object()
{
    model_list.reserve(5);
}

ModelLibrary::ModelLibrary(int reserved_space) :
    Object()
{
    //reserve room for models
    model_list.reserve(reserved_space);
}

void ModelLibrary::addModel(Model mdl){
    if(!containsModel(mdl)){
        model_list.push_back(mdl);
    }
}

bool ModelLibrary::containsModel(Model mdl) const{
    unsigned int i;
    for(i=0; i< model_list.size(); i++){
        if(mdl.equal(model_list[i])){
            return true;
        }
    }
    return false;
}

bool ModelLibrary::removeModel(Model mdl){
    unsigned int i;
    for(i=0; i< model_list.size(); i++){
        if(model_list[i] == mdl){
            std::vector<Model>::iterator it = model_list.begin() + i;
            model_list.erase(it);
            break;
        }
    }
    //model not even loaded yet!
    return false;
}

std::vector<Model> ModelLibrary::getModels() const{
    return model_list;
}

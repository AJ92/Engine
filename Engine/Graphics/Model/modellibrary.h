#ifndef MODELLIBRAY_H
#define MODELLIBRAY_H

#include "Object/object.h"
#include <QString>
#include <vector>

#include "Graphics/Model/Streamer/streamer.h"
#include "Graphics/Model/model.h"

class ModelLibrary : public Object
{
public:
    ModelLibrary();
    ModelLibrary(int maxThreads, int reserved_space);

    Model* loadModel(QString path);
    std::vector<Model*> getModels() const;

private:
    Streamer * streamer;
    std::vector<Model*> model_list;


    void addModel(Model * mdl);
    bool containsModel(Model * mdl) const;
    bool removeModel(Model * mdl);
};

#endif // MODELLIBRAY_H

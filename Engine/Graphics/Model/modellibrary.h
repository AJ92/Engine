#ifndef MODELLIBRAY_H
#define MODELLIBRAY_H

#include "Object/object.h"
#include <QString>
#include <vector>

#include "Graphics/Model/model.h"

class ModelLibrary : public Object
{
public:
    ModelLibrary();
    ModelLibrary(int reserved_space);

    void addModel(Model mdl);
    bool containsModel(Model mdl) const;
    bool removeModel(Model mdl);

    std::vector<Model> getModels() const;

private:
    std::vector<Model> model_list;
};

#endif // MODELLIBRAY_H

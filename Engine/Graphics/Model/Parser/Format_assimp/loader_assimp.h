#ifndef LOADER_ASSIMP_H
#define LOADER_ASSIMP_H

#include "Graphics/OpenGL/OpenGL.h"
#include "Vector/vector3.h"
#include <QString>
#include <QStringList>

//assimp includes
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags


class Model;
class Mesh;
class Material;

class Loader_assimp
{
public:
    Loader_assimp();

    bool load_model_data(Model& mdl, QString path);
    float min_value(float x, float y);
    float max_value(float x, float y);
};

#endif // LOADER_ASSIMP_H

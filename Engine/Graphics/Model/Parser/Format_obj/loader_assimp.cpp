#include "loader_assimp.h"

#include "Graphics/Model/model.h"
#include "Graphics/Model/Components/material.h"
#include "Graphics/Model/Components/mesh.h"

Loader_assimp::Loader_assimp()
{
}

bool Loader_assimp::load_model_data(Model& mdl, QString path){
    // Create an instance of the Importer class
    Assimp::Importer importer;
    // And have it read the given file with some example postprocessing
    // Usually - if speed is not the most important aspect for you - you'll
    // propably to request more postprocessing than we do in this example.
    const aiScene* scene = importer.ReadFile( path.toUtf8().constData(),
          aiProcess_CalcTangentSpace       |
          aiProcess_Triangulate            |
          aiProcess_JoinIdenticalVertices  |
          aiProcess_SortByPType);

    if(!scene){
        //couldn't load model
        qDebug("        Assimp Model import: Error 1: Model file could not be loaded...");
        return false;
    }

}

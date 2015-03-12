#include "loader_assimp.h"

#include "Graphics/Model/model.h"
#include "Graphics/Model/Components/material.h"
#include "Graphics/Model/Components/mesh.h"
#include "Graphics/Model/Components/texturemap.h"

Loader_assimp::Loader_assimp()
{
}

float Loader_assimp::min_value(float x, float y){
    if(x > y){
        return y;
    }
    return x;
}

float Loader_assimp::max_value(float x, float y){
    if(x < y){
        return y;
    }
    return x;
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
    qDebug("        Assimp Model import: Model loaded (" + path.toUtf8() + ")...");

    //now lets build a proper model...

    QStringList pathlist = path.split("/",QString::KeepEmptyParts); //KeepEmptyParts

    pathlist.removeAt(pathlist.length()-1);
    QString tex_path = pathlist.join("/") + "/";

    QList< SP<Material> > materials;

    //build the materials
    for(unsigned int i = 0; i < scene->mNumMaterials; i++)
    {
        aiMaterial* mtl = scene->mMaterials[i];
        int texIndex = 0;
        aiString tex_map_path;
        aiReturn texFound = mtl->GetTexture(aiTextureType_DIFFUSE, texIndex, &tex_map_path);
        while(texFound == AI_SUCCESS){
            qDebug(QString(tex_map_path.C_Str()).toUtf8());
            texFound = AI_FAILURE;

            //we found a diffuse tex lets use the first one for now...
            //creating a material

            QString tex_name_with_path(tex_map_path.C_Str());
            QString tex_name = tex_name_with_path.split("\\",QString::SkipEmptyParts).last().toUtf8();

            //TODO: find a better texname otherwise it might get "instanced" even if not desired
            SP<Material> material_done = new Material(tex_name);
            SP<TextureMap> diffuse_tex_map = new TextureMap(tex_path + tex_name,tex_path + tex_name);
            material_done->addTextureMap(diffuse_tex_map, Material::Diffuse);
            materials.append(material_done);

            // more textures?
            //texIndex++;
            //texFound = mtl->GetTexture(aiTextureType_DIFFUSE, texIndex, &tex_map_path);
        }
    }

    //init all materials
    for(int i = 0; i < materials.size(); i++){
        materials[i]->loadData();
    }


    //build the meshes
    for(unsigned int i = 0; i < scene->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[i];
        int numFaces = mesh->mNumFaces;
        int numVerts = numFaces*3;

        //TODO: make sure the meshes are deleting those arrays!
        float * vertexArray     = new float[numFaces*3*3];
        float * normalArray     = new float[numFaces*3*3];
        float * uvwArray         = new float[numFaces*3*3];

        //bounding stuff...
        float v_min_x = 0.0f;
        float v_max_x = 0.0f;
        float v_min_y = 0.0f;
        float v_max_y = 0.0f;
        float v_min_z = 0.0f;
        float v_max_z = 0.0f;

        //iterate trough all mesh faces
        for(unsigned int j=0; j<mesh->mNumFaces; j++)
        {
            const aiFace& face = mesh->mFaces[j];
            for(int k=0;k<3;k++)
            {
                aiVector3D pos = mesh->mVertices[face.mIndices[k]];
                memcpy(vertexArray,&pos,sizeof(float)*3);
                vertexArray+=3;
                //calc bounding vertices
                v_min_x = min_value(v_min_x,pos.x);
                v_min_y = min_value(v_min_y,pos.y);
                v_min_z = min_value(v_min_z,pos.z);

                v_max_x = max_value(v_max_x,pos.x);
                v_max_y = max_value(v_max_y,pos.y);
                v_max_z = max_value(v_max_z,pos.z);

                aiVector3D normal = mesh->mNormals[face.mIndices[k]];
                memcpy(normalArray,&normal,sizeof(float)*3);
                normalArray+=3;

                //we are only copying u and v coord and not w !!!
                //so w coordinate might be anything....
                aiVector3D uvw = mesh->mTextureCoords[0][face.mIndices[k]];
                //flip y coord
                uvw.y = -uvw.y;
                memcpy(uvwArray,&uvw,sizeof(float)*3);
                uvwArray+=3;
            }
        }

        //set the pointer start back to it's start xD
        normalArray -= numFaces*3*3;
        vertexArray -= numFaces*3*3;
        uvwArray    -= numFaces*3*3;


        //create a mesh
        Vector3 vert1(v_min_x, v_min_y, v_min_z);
        Vector3 vert2(v_max_x, v_max_y, v_max_z);

        Vector3 bounding_sphere_pos((v_min_x + v_max_x)/2.0f, (v_min_y + v_max_y)/2.0f, (v_min_z + v_max_z)/2.0f);
        double bounding_sphere_radius = vert1.distance(vert2) / 2.0f;


        //get the proper material

        unsigned int mtl_index = mesh->mMaterialIndex - 1;


        if(materials.length() > mtl_index){
            //load the right material
            SP<Mesh> mesh_done = new Mesh("mesh_name" + QString::number(rand() & 2000), numFaces, vertexArray, uvwArray, normalArray, materials[mtl_index]);
            mesh_done->setBoundingSpherePos(bounding_sphere_pos);
            mesh_done->setBoundingSphereRadius(bounding_sphere_radius);
            mdl.add_mesh(mesh_done);
        }
        else{
            //construct a default material, that atleast has a diffuse map...
            SP<Material> material_default = new Material("empty_default_material");
            SP<TextureMap> diffuse_tex_map = new TextureMap("empty.png","empty.png");
            material_default->addTextureMap(diffuse_tex_map, Material::Diffuse);
            SP<Mesh> mesh_done = new Mesh("mesh_name" + QString::number(rand() & 2000), numFaces, vertexArray, uvwArray, normalArray, material_default);
            mesh_done->setBoundingSpherePos(bounding_sphere_pos);
            mesh_done->setBoundingSphereRadius(bounding_sphere_radius);
            mdl.add_mesh(mesh_done);
        }

        //TODO: change to proper mat


    }


    mdl.set_path(path);
    return true;
}

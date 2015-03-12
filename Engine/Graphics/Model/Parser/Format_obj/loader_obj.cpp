#include "loader_obj.h"

#include "Graphics/Model/model.h"
#include "Graphics/Model/Components/material.h"
#include "Graphics/Model/Components/mesh.h"

Loader_obj::Loader_obj()
{

}

GLfloat Loader_obj::min_value(GLfloat x, GLfloat y){
    if(x > y){
        return y;
    }
    return x;
}

GLfloat Loader_obj::max_value(GLfloat x, GLfloat y){
    if(x < y){
        return y;
    }
    return x;
}

bool Loader_obj::load_model_data(Model& mdl, QString path){

    /*
    QStringList pathlist = path.split("/",QString::KeepEmptyParts); //KeepEmptyParts
    QString model_name = pathlist.last();

    //LOAD MESH DATA
    QFile file(path);
    if (!file.open (QIODevice::ReadOnly))
    {
        qDebug("        Model import: Error 1: Model file could not be loaded...");
        return false;
    }
    QTextStream stream ( &file );
    QString line;

    QString mtllib;


    QString current_mesh;
    QMap<QString,QVector<int> >mesh_faces;
    QMap<QString,QString> mesh_mtl;
    QMap<QString,Material* > mtln_mtl;
    QVector<Vector3> model_vertices;
    QVector<Vector3> model_vertex_normals;
    QVector<Vector3> model_vertex_texture_coordinates;

    while( !stream.atEnd() ) {
        line = stream.readLine();
        QStringList list = line.split(QRegExp("\\s+"),QString::SkipEmptyParts); //SkipEmptyParts

        if(!list.empty()){
            if(list.first() == "mtllib"){
                mtllib = list.last();
            }

            else if(list.first() == "v"){
                model_vertices.append(Vector3(  list.value(1).toFloat(),
                                                  list.value(2).toFloat(),
                                                  list.value(3).toFloat()));
            }
            else if(list.first() == "vn"){
                model_vertex_normals.append(Vector3(  list.value(1).toFloat(),
                                                        list.value(2).toFloat(),
                                                        list.value(3).toFloat()));
            }
            else if(list.first() == "vt"){
                model_vertex_texture_coordinates.append(Vector3(  list.value(1).toFloat(),
                                                                    list.value(2).toFloat(),
                                                                    list.value(3).toFloat()));
            }
            else if(list.first() == "g"){
                current_mesh = list.value(1);
            }
            else if(list.first() == "usemtl"){
                mesh_mtl[current_mesh] = list.value(1);
            }
            else if(list.first() == "f"){
                QStringList face_part_1_list = list.value(1).split("/",QString::SkipEmptyParts); //SkipEmptyParts
                QStringList face_part_2_list = list.value(2).split("/",QString::SkipEmptyParts); //SkipEmptyParts
                QStringList face_part_3_list = list.value(3).split("/",QString::SkipEmptyParts); //SkipEmptyParts
                mesh_faces[current_mesh].append(face_part_1_list.value(0).toInt());
                mesh_faces[current_mesh].append(face_part_1_list.value(1).toInt());
                mesh_faces[current_mesh].append(face_part_1_list.value(2).toInt());

                mesh_faces[current_mesh].append(face_part_2_list.value(0).toInt());
                mesh_faces[current_mesh].append(face_part_2_list.value(1).toInt());
                mesh_faces[current_mesh].append(face_part_2_list.value(2).toInt());

                mesh_faces[current_mesh].append(face_part_3_list.value(0).toInt());
                mesh_faces[current_mesh].append(face_part_3_list.value(1).toInt());
                mesh_faces[current_mesh].append(face_part_3_list.value(2).toInt());

            }
        }

    }
    file.close();


    //LOAD MTL DATA

    pathlist.removeAt(pathlist.length()-1);
    QString mtl_path = pathlist.join("/") + "/" + mtllib;
    QString tex_path = pathlist.join("/") + "/";

    QFile mtlfile(mtl_path);
    if (!mtlfile.open (QIODevice::ReadOnly))
    {
        qDebug("        Model import: Error 2: Model material file could not be loaded...");
        return false;
    }
    QTextStream mtlstream ( &mtlfile );
    QString mtlline;


    QString current_mtl;
    QMap<QString,Vector3> mtl_ambient_c;          //Ka
    QMap<QString,Vector3> mtl_diffuse_c;          //Kd
    QMap<QString,Vector3> mtl_specular_c;         //Ks
    QMap<QString,float>     mtl_specular_ns;        //Ns
    QMap<QString,float>     mtl_transparency_d;     //d
    QMap<QString,float>     mtl_transparency_tr;    //Tr
    QMap<QString,Vector3> mtl_transparency_tf;    //Tf
    QMap<QString,QString>   mtl_ambient_map;        //map_Ka
    QMap<QString,QString>   mtl_diffuse_map;        //map_Kd
    QMap<QString,QString>   mtl_specular_map;       //map_Ks
    QMap<QString,QString>   mtl_bump_map;           //map_bump
    QMap<QString,int>       mtl_illumination;       //illum

    //stream
    while( !mtlstream.atEnd() ) {
        mtlline = mtlstream.readLine();
        QStringList list = mtlline.split(QRegExp("\\s+"),QString::SkipEmptyParts); //SkipEmptyParts
        if(!list.empty()){
            if(list.first() == "newmtl"){
                current_mtl = list.last();
            }
            else if(list.first() == "Ka"){
                mtl_ambient_c[current_mtl] = Vector3(list.value(1).toFloat(),
                                                       list.value(2).toFloat(),
                                                       list.value(3).toFloat());
            }
            else if(list.first() == "Kd"){
                mtl_diffuse_c[current_mtl] = Vector3(list.value(1).toFloat(),
                                                       list.value(2).toFloat(),
                                                       list.value(3).toFloat());
            }
            else if(list.first() == "Ks"){
                mtl_specular_c[current_mtl] = Vector3(list.value(1).toFloat(),
                                                        list.value(2).toFloat(),
                                                        list.value(3).toFloat());
            }
            else if(list.first() == "Ns"){
                mtl_specular_ns[current_mtl] = list.value(1).toFloat();

            }
            else if(list.first() == "d"){
                mtl_transparency_d[current_mtl] = list.value(1).toFloat();

            }
            else if(list.first() == "Tr"){
                mtl_transparency_tr[current_mtl] = list.value(1).toFloat();

            }
            else if(list.first() == "Tf"){
                mtl_transparency_tf[current_mtl] = Vector3(list.value(1).toFloat(),
                                                             list.value(2).toFloat(),
                                                             list.value(3).toFloat());
            }
            else if(list.first() == "map_Ka"){
                mtl_ambient_map[current_mtl] = list.value(1).split("\\",QString::SkipEmptyParts).last().toUtf8();
            }
            else if(list.first() == "map_Kd"){
                mtl_diffuse_map[current_mtl] = list.value(1).split("\\",QString::SkipEmptyParts).last().toUtf8();
            }
            else if(list.first() == "map_Ks"){
                mtl_specular_map[current_mtl] = list.value(1).split("\\",QString::SkipEmptyParts).last().toUtf8();
            }
            else if((list.first() == "map_bump") || (list.first() == "bump")){
                mtl_bump_map[current_mtl] = list.value(1).split("\\",QString::SkipEmptyParts).last().toUtf8();
            }
            else if(list.first() == "illum"){
                mtl_illumination[current_mtl] = list.value(1).toInt();
            }
        }
    }
    //stream end



    //CREATE MTLS (if needed...)

    //using diffues mat cause its the major map used (other maps are optional)...

    QList<QString> mtl_names = mtl_diffuse_c.keys();
    for(int i = 0; i < mtl_names.length(); i++){
        Material* mtl = new Material(mtl_names.value(i),tex_path);
        mtl->set_ambient_c(mtl_ambient_c[mtl_names.value(i)]);
        mtl->set_diffuse_c(mtl_diffuse_c[mtl_names.value(i)]);
        mtl->set_specular_c(mtl_specular_c[mtl_names.value(i)]);
        mtl->set_specular_ns(mtl_specular_ns[mtl_names.value(i)]);
        mtl->set_transparency_d(mtl_transparency_d[mtl_names.value(i)]);
        mtl->set_transparency_tr(mtl_transparency_tr[mtl_names.value(i)]);
        mtl->set_transparency_tf(mtl_transparency_tf[mtl_names.value(i)]);
        mtl->set_ambient_map_name(mtl_ambient_map[mtl_names.value(i)]);
        mtl->set_diffuse_map_name(mtl_diffuse_map[mtl_names.value(i)]);
        mtl->set_specular_map_name(mtl_specular_map[mtl_names.value(i)]);
        mtl->set_bump_map_name(mtl_bump_map[mtl_names.value(i)]);
        mtl->set_illumination(mtl_illumination[mtl_names.value(i)]);

        //init texture maps
        mtl->set_ambient_map_path(tex_path + mtl_ambient_map[mtl_names.value(i)]);
        mtl->set_diffuse_map_path(tex_path + mtl_diffuse_map[mtl_names.value(i)]);
        mtl->set_specular_map_path(tex_path + mtl_specular_map[mtl_names.value(i)]);
        mtl->set_bump_map_path(tex_path + mtl_bump_map[mtl_names.value(i)]);

        mtl->loadData();


        mtln_mtl[mtl_names.value(i)] = mtl;
    }



    //CREATE MESHS (if needed...)
    //QMap<QString,QVector<QVector3D> > mesh_faces;
    //QMap<QString,QString> mesh_mtl;
    //QVector<QVector3D> model_vertices;
    //QVector<QVector3D> model_vertex_normals;
    //QVector<QVector3D> model_vertex_texture_coordinates;

    //using mesh_mtl to iterate ...
    QList<QString> mesh_names = mesh_mtl.keys();
    for(int i = 0; i < mesh_names.length(); i++){

        //min/max vertex pos on all 3 axis
        GLfloat v_min_x = 0.0f;
        GLfloat v_max_x = 0.0f;

        GLfloat v_min_y = 0.0f;
        GLfloat v_max_y = 0.0f;

        GLfloat v_min_z = 0.0f;
        GLfloat v_max_z = 0.0f;


        int triangle_count = mesh_faces[mesh_names.value(i)].size() / 3 / 3;
        //qDebug("        Triangles: %i",triangle_count);
        GLfloat* vertices = new GLfloat[mesh_faces[mesh_names.value(i)].size()];
        GLfloat* texcoords = new GLfloat[mesh_faces[mesh_names.value(i)].size()]; //should be wrong ... 108/3*2 is right ...
        GLfloat* normals = new GLfloat[mesh_faces[mesh_names.value(i)].size()];

        //qDebug("Mesh...");

        for(int j = 0; j < mesh_faces[mesh_names.value(i)].size(); j+=9){
            //  1 v/vt/vn   2 v/vt/vn   3 v/vt/vn

            //  v
            Vector3 vertex1 =  model_vertices.value(mesh_faces[mesh_names.value(i)].value(j)  -1);
            vertices[j]     = (GLfloat) vertex1.x();
            vertices[j+1]   = (GLfloat) vertex1.y();
            vertices[j+2]   = (GLfloat) vertex1.z();

            Vector3 vertex2 =  model_vertices.value(mesh_faces[mesh_names.value(i)].value(j+3)-1);
            vertices[3+j]   = (GLfloat) vertex2.x();
            vertices[3+j+1] = (GLfloat) vertex2.y();
            vertices[3+j+2] = (GLfloat) vertex2.z();

            Vector3 vertex3 =  model_vertices.value(mesh_faces[mesh_names.value(i)].value(j+6)-1);
            vertices[6+j]   = (GLfloat) vertex3.x();
            vertices[6+j+1] = (GLfloat) vertex3.y();
            vertices[6+j+2] = (GLfloat) vertex3.z();

            //get the min/max vertex pos on all 3 axis
            //x axis
            v_min_x = min_value(v_min_x,vertex1.x());
            v_min_x = min_value(v_min_x,vertex2.x());
            v_min_x = min_value(v_min_x,vertex3.x());

            v_max_x = max_value(v_max_x,vertex1.x());
            v_max_x = max_value(v_max_x,vertex2.x());
            v_max_x = max_value(v_max_x,vertex3.x());

            //y axis
            v_min_y = min_value(v_min_y,vertex1.y());
            v_min_y = min_value(v_min_y,vertex2.y());
            v_min_y = min_value(v_min_y,vertex3.y());

            v_max_y = max_value(v_max_y,vertex1.y());
            v_max_y = max_value(v_max_y,vertex2.y());
            v_max_y = max_value(v_max_y,vertex3.y());

            //z axis
            v_min_z = min_value(v_min_z,vertex1.z());
            v_min_z = min_value(v_min_z,vertex2.z());
            v_min_z = min_value(v_min_z,vertex3.z());

            v_max_z = max_value(v_max_z,vertex1.z());
            v_max_z = max_value(v_max_z,vertex2.z());
            v_max_z = max_value(v_max_z,vertex3.z());




            //  vt  (t value inverted)
            Vector3 texcoord1 = model_vertex_texture_coordinates.value(mesh_faces[mesh_names.value(i)].value(j+1)-1);
            texcoords[j]     = (GLfloat) texcoord1.x();
            texcoords[j+1]   = (GLfloat) -texcoord1.y();
            texcoords[j+2]   = (GLfloat) texcoord1.z();

            Vector3 texcoord2 = model_vertex_texture_coordinates.value(mesh_faces[mesh_names.value(i)].value(j+4)-1);
            texcoords[3+j]   = (GLfloat) texcoord2.x();
            texcoords[3+j+1] = (GLfloat) -texcoord2.y();
            texcoords[3+j+2] = (GLfloat) texcoord2.z();

            Vector3 texcoord3 = model_vertex_texture_coordinates.value(mesh_faces[mesh_names.value(i)].value(j+7)-1);
            texcoords[6+j]   = (GLfloat) texcoord3.x();
            texcoords[6+j+1] = (GLfloat) -texcoord3.y();
            texcoords[6+j+2] = (GLfloat) texcoord3.z();


            //  vn
            Vector3 normal1 = model_vertex_normals.value(mesh_faces[mesh_names.value(i)].value(j+2)-1);
            normal1.normalize();

            //normalize
            normals[j]     = (GLfloat) normal1.x();
            normals[j+1]   = (GLfloat) normal1.y();
            normals[j+2]   = (GLfloat) normal1.z();


            Vector3 normal2 = model_vertex_normals.value(mesh_faces[mesh_names.value(i)].value(j+5)-1);
            normal2.normalize();

            //normalize
            normals[3+j]   = (GLfloat) normal2.x();
            normals[3+j+1] = (GLfloat) normal2.y();
            normals[3+j+2] = (GLfloat) normal2.z();


            Vector3 normal3 = model_vertex_normals.value(mesh_faces[mesh_names.value(i)].value(j+8)-1);
            normal3.normalize();

            //normalize
            normals[6+j]   = (GLfloat) normal3.x();
            normals[6+j+1] = (GLfloat) normal3.y();
            normals[6+j+2] = (GLfloat) normal3.z();


        }



        Vector3 vert1(v_min_x, v_min_y, v_min_z);
        Vector3 vert2(v_max_x, v_max_y, v_max_z);

        Vector3 bounding_sphere_pos((v_min_x + v_max_x)/2.0f, (v_min_y + v_max_y)/2.0f, (v_min_z + v_max_z)/2.0f);
        double bounding_sphere_radius = vert1.distance(vert2) / 2.0f;


        //bounding_sphere_radius = 10.0;

        //Create Mesh and add it to the Mesh-list of the model.
        Mesh* mesh = new Mesh(mesh_names.value(i), triangle_count, vertices, texcoords, normals,
                              mtln_mtl.value(mesh_mtl.value(mesh_names.value(i))));

        mesh->setBoundingSpherePos(bounding_sphere_pos);
        mesh->setBoundingSphereRadius(bounding_sphere_radius);

        //meshs.append(mesh);
        mdl.add_mesh(mesh);

    }

    mdl.set_path(path);
    */
    return true;
}

#include "loader_obj.h"

Loader_obj::Loader_obj()
{

}

bool Loader_obj::load_model_data(Model& mdl, QString path){
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

        //as this function gets called in a thread we need to do this in main...
        /*
        mtl->load_ambient_map(tex_path + mtl_ambient_map[mtl_names.value(i)]);
        mtl->load_diffuse_map(tex_path + mtl_diffuse_map[mtl_names.value(i)]);
        mtl->load_specular_map(tex_path + mtl_specular_map[mtl_names.value(i)]);
        mtl->load_bump_map(tex_path + mtl_bump_map[mtl_names.value(i)]);
        */

        mtl->set_ambient_map_path(tex_path + mtl_ambient_map[mtl_names.value(i)]);
        mtl->set_diffuse_map_path(tex_path + mtl_diffuse_map[mtl_names.value(i)]);
        mtl->set_specular_map_path(tex_path + mtl_specular_map[mtl_names.value(i)]);
        mtl->set_bump_map_path(tex_path + mtl_bump_map[mtl_names.value(i)]);

        mtl->loadData();

        /*
        qDebug("        MTL ambient m:   " + mtl->get_ambient_map_name().toUtf8());
        qDebug("        MTL diffuse m:   " + mtl->get_diffuse_map_name().toUtf8());
        qDebug("        MTL specular m:  " + mtl->get_specular_map_name().toUtf8());
        qDebug("        MTL bump m:      " + mtl->get_bump_map_name().toUtf8());
        */

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
        //needs .constData() every render pass in future...
        //QVector<QVector3D> vertices;
        //QVector<QVector2D> texcoords;
        //QVector<QVector3D> normals;
        //should be constant data and no need to convert...
        //qDebug(QString::number(mesh_faces[mesh_names.value(i)].size()).toUtf8());
        //qDebug(QString::number(mesh_faces[mesh_names.value(i)].size()*3).toUtf8());


        int triangle_count = mesh_faces[mesh_names.value(i)].size() / 3 / 3;
        //qDebug("        Triangles: %i",triangle_count);
        GLfloat* vertices = new GLfloat[mesh_faces[mesh_names.value(i)].size()];
        GLfloat* texcoords = new GLfloat[mesh_faces[mesh_names.value(i)].size()]; //should be wrong ... 108/3*2 is right ...
        GLfloat* normals = new GLfloat[mesh_faces[mesh_names.value(i)].size()];

        GLfloat* tangents = new GLfloat[mesh_faces[mesh_names.value(i)].size()];
        GLfloat* binormals = new GLfloat[mesh_faces[mesh_names.value(i)].size()];

        //VAO and VBOs

        /*
        GLuint vao;

        GLuint vertex_vbo;
        GLuint texcoord_vbo;
        GLuint normal_vbo;

        GLuint tangent_vbo;
        GLuint binormal_vbo;
        */


        //qDebug("Mesh...");

        for(int j = 0; j < mesh_faces[mesh_names.value(i)].size(); j+=9){
            //  1 v/vt/vn   2 v/vt/vn   3 v/vt/vn

            //  v
            vertices[j]     = (GLfloat) model_vertices.value(mesh_faces[mesh_names.value(i)].value(j)  -1).x();
            vertices[j+1]   = (GLfloat) model_vertices.value(mesh_faces[mesh_names.value(i)].value(j)  -1).y();
            vertices[j+2]   = (GLfloat) model_vertices.value(mesh_faces[mesh_names.value(i)].value(j)  -1).z();

            vertices[3+j]   = (GLfloat) model_vertices.value(mesh_faces[mesh_names.value(i)].value(j+3)-1).x();
            vertices[3+j+1] = (GLfloat) model_vertices.value(mesh_faces[mesh_names.value(i)].value(j+3)-1).y();
            vertices[3+j+2] = (GLfloat) model_vertices.value(mesh_faces[mesh_names.value(i)].value(j+3)-1).z();

            vertices[6+j]   = (GLfloat) model_vertices.value(mesh_faces[mesh_names.value(i)].value(j+6)-1).x();
            vertices[6+j+1] = (GLfloat) model_vertices.value(mesh_faces[mesh_names.value(i)].value(j+6)-1).y();
            vertices[6+j+2] = (GLfloat) model_vertices.value(mesh_faces[mesh_names.value(i)].value(j+6)-1).z();

            /*
                qDebug(QString::number(vertices[j]));
                qDebug(QString::number(vertices[j+1]));
                qDebug(QString::number(vertices[j+2]));

                qDebug(QString::number(vertices[j+3]));
                qDebug(QString::number(vertices[j+4]));
                qDebug(QString::number(vertices[j+5]));

                qDebug(QString::number(vertices[j+6]));
                qDebug(QString::number(vertices[j+7]));
                qDebug(QString::number(vertices[j+8]));

                qDebug("\n");
                */

            //  vt
            texcoords[j]     = (GLfloat) model_vertex_texture_coordinates.value(mesh_faces[mesh_names.value(i)].value(j+1)-1).x();
            texcoords[j+1]   = (GLfloat) -model_vertex_texture_coordinates.value(mesh_faces[mesh_names.value(i)].value(j+1)-1).y();
            texcoords[j+2]   = (GLfloat) model_vertex_texture_coordinates.value(mesh_faces[mesh_names.value(i)].value(j+1)-1).z();

            texcoords[3+j]   = (GLfloat) model_vertex_texture_coordinates.value(mesh_faces[mesh_names.value(i)].value(j+4)-1).x();
            texcoords[3+j+1] = (GLfloat) -model_vertex_texture_coordinates.value(mesh_faces[mesh_names.value(i)].value(j+4)-1).y();
            texcoords[3+j+2] = (GLfloat) model_vertex_texture_coordinates.value(mesh_faces[mesh_names.value(i)].value(j+4)-1).z();

            texcoords[6+j]   = (GLfloat) model_vertex_texture_coordinates.value(mesh_faces[mesh_names.value(i)].value(j+7)-1).x();
            texcoords[6+j+1] = (GLfloat) -model_vertex_texture_coordinates.value(mesh_faces[mesh_names.value(i)].value(j+7)-1).y();
            texcoords[6+j+2] = (GLfloat) model_vertex_texture_coordinates.value(mesh_faces[mesh_names.value(i)].value(j+7)-1).z();

            /*

                qDebug(QString::number(texcoords[j]));
                qDebug(QString::number(texcoords[j+1]));
                qDebug(QString::number(texcoords[j+2]));

                qDebug(QString::number(texcoords[j+3]));
                qDebug(QString::number(texcoords[j+4]));
                qDebug(QString::number(texcoords[j+5]));

                qDebug(QString::number(texcoords[j+6]));
                qDebug(QString::number(texcoords[j+7]));
                qDebug(QString::number(texcoords[j+8]));

                qDebug("\n");

                */
            //  vn
            normals[j]     = (GLfloat) model_vertex_normals.value(mesh_faces[mesh_names.value(i)].value(j+2)-1).x();
            normals[j+1]   = (GLfloat) model_vertex_normals.value(mesh_faces[mesh_names.value(i)].value(j+2)-1).y();
            normals[j+2]   = (GLfloat) model_vertex_normals.value(mesh_faces[mesh_names.value(i)].value(j+2)-1).z();

            normals[3+j]   = (GLfloat) model_vertex_normals.value(mesh_faces[mesh_names.value(i)].value(j+5)-1).x();
            normals[3+j+1] = (GLfloat) model_vertex_normals.value(mesh_faces[mesh_names.value(i)].value(j+5)-1).y();
            normals[3+j+2] = (GLfloat) model_vertex_normals.value(mesh_faces[mesh_names.value(i)].value(j+5)-1).z();

            normals[6+j]   = (GLfloat) model_vertex_normals.value(mesh_faces[mesh_names.value(i)].value(j+8)-1).x();
            normals[6+j+1] = (GLfloat) model_vertex_normals.value(mesh_faces[mesh_names.value(i)].value(j+8)-1).y();
            normals[6+j+2] = (GLfloat) model_vertex_normals.value(mesh_faces[mesh_names.value(i)].value(j+8)-1).z();

            // v1 tc u          v2 tc v           v2 tc u           v1 tc v
            GLfloat coef = 1.0 / (texcoords[j] * texcoords[3+j+1] - texcoords[3+j] * texcoords[j+1]);

            GLfloat* tangent = new GLfloat[3];
            //v1.x              v2 tc v               v2.x              v1 tc v
            tangent[0] = coef * ((vertices[j] * texcoords[3+j+1])  + (vertices[3+j] * -texcoords[j+1]));
            //v1.y              v2 tc v                 v2.y            v1 tc v
            tangent[1] = coef * ((vertices[j+1] * texcoords[3+j+1])  + (vertices[3+j+1] * -texcoords[j+1]));
            //v1.z              v2 tc v                 v2.z            v1 tc v
            tangent[2] = coef * ((vertices[j+2] * texcoords[3+j+1])  + (vertices[3+j+2] * -texcoords[j+1]));


            tangents[j]     = tangent[0];
            tangents[j+1]   = tangent[1];
            tangents[j+2]   = tangent[2];

            tangents[3+j]   = tangent[0];
            tangents[3+j+1] = tangent[1];
            tangents[3+j+2] = tangent[2];

            tangents[6+j]   = tangent[0];
            tangents[6+j+1] = tangent[1];
            tangents[6+j+2] = tangent[2];

            /*
                qDebug("Tangents:");

                qDebug(QString::number(tangents[j]).toUtf8());
                qDebug(QString::number(tangents[j+1]).toUtf8());
                qDebug(QString::number(tangents[j+2]).toUtf8());

                qDebug(QString::number(tangents[j+3]).toUtf8());
                qDebug(QString::number(tangents[j+4]).toUtf8());
                qDebug(QString::number(tangents[j+5]).toUtf8());

                qDebug(QString::number(tangents[j+6]).toUtf8());
                qDebug(QString::number(tangents[j+7]).toUtf8());
                qDebug(QString::number(tangents[j+8]).toUtf8());

                qDebug("\n");
                */


            //float3 binormal = normal.crossProduct(tangent);

            binormals[j]     = normals[j+1]  *tangents[j+2] - normals[j+2]  *tangents[j+1];
            binormals[j+1]   = normals[j+2]  *tangents[j]   - normals[j]    *tangents[j+2];
            binormals[j+2]   = normals[j]    *tangents[j+1] - normals[j+1]  *tangents[j];

            binormals[3+j]     = normals[3+j+1]  *tangents[3+j+2] - normals[3+j+2]  *tangents[3+j+1];
            binormals[3+j+1]   = normals[3+j+2]  *tangents[3+j]   - normals[3+j]    *tangents[3+j+2];
            binormals[3+j+2]   = normals[3+j]    *tangents[3+j+1] - normals[3+j+1]  *tangents[3+j];

            binormals[6+j]     = normals[6+j+1]  *tangents[6+j+2] - normals[6+j+2]  *tangents[6+j+1];
            binormals[6+j+1]   = normals[6+j+2]  *tangents[6+j]   - normals[6+j]    *tangents[6+j+2];
            binormals[6+j+2]   = normals[6+j]    *tangents[6+j+1] - normals[6+j+1]  *tangents[6+j];

            /*
                qDebug("Binormals:");

                qDebug(QString::number(binormals[j]).toUtf8());
                qDebug(QString::number(binormals[j+1]).toUtf8());
                qDebug(QString::number(binormals[j+2]).toUtf8());

                qDebug(QString::number(binormals[j+3]).toUtf8());
                qDebug(QString::number(binormals[j+4]).toUtf8());
                qDebug(QString::number(binormals[j+5]).toUtf8());

                qDebug(QString::number(binormals[j+6]).toUtf8());
                qDebug(QString::number(binormals[j+7]).toUtf8());
                qDebug(QString::number(binormals[j+8]).toUtf8());

                qDebug("\n");
                */
        }


        //moved to main thread, more specificly: Mesh::load_data and Material::load_xxxx and streamer
        /*
        glGenVertexArrays(1, &vao);

        glBindVertexArray(vao);

        glGenBuffers(1, &vertex_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo);
        glBufferData(GL_ARRAY_BUFFER, triangle_count * 3* 3 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);


        glGenBuffers(1, &texcoord_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, texcoord_vbo);
        glBufferData(GL_ARRAY_BUFFER, triangle_count * 3 * 3 * sizeof(GLfloat), texcoords, GL_STATIC_DRAW);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(1);


        glGenBuffers(1, &normal_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, normal_vbo);
        glBufferData(GL_ARRAY_BUFFER, triangle_count * 3 * 3 * sizeof(GLfloat), normals, GL_STATIC_DRAW);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(2);
        */

        //Create Mesh and add it to the Mesh-list of the model.
        Mesh* mesh = new Mesh(mesh_names.value(i), triangle_count, vertices, texcoords, normals,
                              mtln_mtl.value(mesh_mtl.value(mesh_names.value(i))));

        //meshs.append(mesh);
        mdl.add_mesh(mesh);

    }

    mdl.set_path(path);
    return true;
}

#include "renderer.h"
#include "Graphics/Model/model.h"
#include "Graphics/Model/Components/material.h"
#include "Graphics/Model/Components/mesh.h"
#include "Graphics/Model/light.h"

#include "Event/event.h"

#include "Object/positation.h"
#include "Object/compositeobject.h"
#include "Graphics/World/objectworld.h"

Renderer::Renderer() :
    EventTransmitter()
{
    shadersAndBuffersCreated = false;
    firstTextureIndex = 2;
    secondTextureIndex = 4;
    thirdTextureIndex = 8;
    fourthTextureIndex = 16;

    mdllib = 0;
    lightlib = 0;
    objectworld = 0;

    meshPerFrameCount = 0;
    trianglesPerFrameCount = 0;
    texBindsPerFrameCount = 0;
}

void Renderer::initialize(){
    debugMessage("initialising renderer ...");
    mdllib = 0;

    //default render mode
    renderMode = PolygonModeStandard;

    //init fsq
    triangle_count = 2;

    fsq_vertices = new GLfloat[18];
    fsq_texcoords = new GLfloat[18];
    fsq_normals = new GLfloat[18];

    //vertices
    fsq_vertices[0] = -1.0f;
    fsq_vertices[1] = -1.0f;
    fsq_vertices[2] = 0.5f;

    fsq_vertices[3] = 1.0f;
    fsq_vertices[4] = -1.0f;
    fsq_vertices[5] = 0.5f;

    fsq_vertices[6] = -1.0f;
    fsq_vertices[7] = 1.0f;
    fsq_vertices[8] = 0.5f;

    fsq_vertices[9] = -1.0f;
    fsq_vertices[10] = 1.0f;
    fsq_vertices[11] = 0.5f;

    fsq_vertices[12] = 1.0f;
    fsq_vertices[13] = -1.0f;
    fsq_vertices[14] = 0.5f;

    fsq_vertices[15] = 1.0f;
    fsq_vertices[16] = 1.0f;
    fsq_vertices[17] = 0.5f;

    //texcoords
    fsq_texcoords[0] = 0.0f;
    fsq_texcoords[1] = 0.0f;
    fsq_texcoords[2] = 1.0f;

    fsq_texcoords[3] = 1.0f;
    fsq_texcoords[4] = 0.0f;
    fsq_texcoords[5] = 1.0f;

    fsq_texcoords[6] = 0.0f;
    fsq_texcoords[7] = 1.0f;
    fsq_texcoords[8] = 1.0f;

    fsq_texcoords[9] = 0.0f;
    fsq_texcoords[10] = 1.0f;
    fsq_texcoords[11] = 1.0f;

    fsq_texcoords[12] = 1.0f;
    fsq_texcoords[13] = 0.0f;
    fsq_texcoords[14] = 1.0f;

    fsq_texcoords[15] = 1.0f;
    fsq_texcoords[16] = 1.0f;
    fsq_texcoords[17] = 1.0f;

    //normals
    fsq_normals[0] = 0.0f;
    fsq_normals[1] = 0.0f;
    fsq_normals[2] = 1.0f;

    fsq_normals[3] = 0.0f;
    fsq_normals[4] = 0.0f;
    fsq_normals[5] = 1.0f;

    fsq_normals[6] = 0.0f;
    fsq_normals[7] = 0.0f;
    fsq_normals[8] = 1.0f;

    fsq_normals[9] = 0.0f;
    fsq_normals[10] = 0.0f;
    fsq_normals[11] = 1.0f;

    fsq_normals[12] = 0.0f;
    fsq_normals[13] = 0.0f;
    fsq_normals[14] = 1.0f;

    fsq_normals[15] = 0.0f;
    fsq_normals[16] = 0.0f;
    fsq_normals[17] = 1.0f;

    //////////////////////////////
    // FULLSCREEN QUAD VAO and VBOs
    debugMessage("creating fullscreenquad");

    glGenVertexArrays(1, &fsq_vertex_array_object);

    glBindVertexArray(fsq_vertex_array_object);

    glGenBuffers(1, &fsq_vertex_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, fsq_vertex_vbo);
    glBufferData(GL_ARRAY_BUFFER, triangle_count * 3* 3 * sizeof(GLfloat), fsq_vertices, GL_STATIC_DRAW);



    glGenBuffers(1, &fsq_texcoord_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, fsq_texcoord_vbo);
    glBufferData(GL_ARRAY_BUFFER, triangle_count * 3 * 3 * sizeof(GLfloat), fsq_texcoords, GL_STATIC_DRAW);



    glGenBuffers(1, &fsq_normal_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, fsq_normal_vbo);
    glBufferData(GL_ARRAY_BUFFER, triangle_count * 3 * 3 * sizeof(GLfloat), fsq_normals, GL_STATIC_DRAW);


    debugMessage("created fullscreenquad!");
    //
    //////////////////////////////


    if(createShaders() && createBuffers()){
        shadersAndBuffersCreated = true;
        debugMessage("renderer seems to be ok.");
        debugMessage("initialised renderer.");
    }
    else{
        debugMessage("renderer failed to initialise...");
    }
}

Renderer::~Renderer(){
    //destructor:
    destroyShaders();
    //destroyVBO();
}

void Renderer::setModelLibrary(ModelLibrary * mdllib){
    this->mdllib = mdllib;
}

void Renderer::setLightLibrary(LightLibrary * lightlib){
    this->lightlib = lightlib;
}

void Renderer::setObjectWorld(ObjectWorld * objectworld){
    this->objectworld = objectworld;
}

void Renderer::setCamera(Camera * cam){
    this->cam = cam;
}

void Renderer::setWindow(Window * win){
    this->win = win;
    this->win->addListener(this);
}

bool Renderer::meshInFrustum(Frustum f, Model * mdl, Mesh * mesh, Matrix4x4 &pvm_mat){
    //get the spherical bounds

    Positation * posi = mdl->getParentCompositeObject()->getPositation();

    Vector3 mdl_pos = posi->getPosition();

    //Vector3 mdl_pos = pvm_mat * mesh->getBoundingSpherePos();


    double rad = mesh->getBoundingSphereRadius();
    double max_rad = 0.0;
    if(posi->get_scale()[0]*rad > max_rad){
        max_rad = posi->get_scale()[0]*rad;
    }
    if(posi->get_scale()[1]*rad > max_rad){
        max_rad = posi->get_scale()[1]*rad;
    }
    if(posi->get_scale()[2]*rad > max_rad){
        max_rad = posi->get_scale()[2]*rad;
    }

    int type = f.sphereInFrustum(mdl_pos,max_rad);

    //int type = f.pointInFrustum(spherical_bound_pos_model_view_space);

    if(type != Frustum::Outside){
        return true;
    }
    return false;
}


//NEW RENDERING CRAP

void Renderer::render_v2(){

    meshPerFrameCount = 0;
    trianglesPerFrameCount = 0;
    texBindsPerFrameCount = 0;

    //check if the mdllib is ready
    if(objectworld!=0){

        //camera matrix
        p_m.set_to_identity();
        p_m.perspective(cam->getFOV(), float(win->getWindowWidth()) / float(win->getWindowHeight()),
                        cam->getZNEAR(), cam->getZFAR());

        v_m = cam->get_view_matrix();//.inverted();



        double near_ = cam->getZNEAR();
        double far_ = cam->getZFAR();

        Frustum frustum;
        //setting up the clipping points/planes...
        frustum.setPoints(cam->getPosition() - touch_to_space(0,0)*near_,
                          cam->getPosition() - touch_to_space(win->getWindowWidth(),0)*near_,
                          cam->getPosition() - touch_to_space(0,win->getWindowHeight())*near_,
                          cam->getPosition() - touch_to_space(win->getWindowWidth(),win->getWindowHeight())*near_,
                          cam->getPosition() - touch_to_space(0,0)*far_,
                          cam->getPosition() - touch_to_space(win->getWindowWidth(),0)*far_,
                          cam->getPosition() - touch_to_space(0,win->getWindowHeight())*far_,
                          cam->getPosition() - touch_to_space(win->getWindowWidth(),win->getWindowHeight())*far_);


        //setup the octtree stuff so we cen loop trough the octtree nodes...
        OctTree * ot = objectworld->getOctTree();
        OctTreeFast * ot_dynamic_models = objectworld->getOctTreeFastDynamicModels();
        OctTreeFast * ot_dynamic_lights = objectworld->getOctTreeFastDynamicLights();


        QList<OctTree*> ot_nodes = ot->getNodesInFrustum(&frustum);
        QList<OctTreeFast*> ot_dynamic_models_nodes = ot_dynamic_models->getNodesInFrustum(&frustum);
        QList<OctTreeFast*> ot_dynamic_lights_nodes = ot_dynamic_lights->getNodesInFrustum(&frustum);

        //debugMessage("Nodes: " + QString::number(ot_nodes.size()));

        //we have the octTree nodes which are in the frustum...
        //lets loop trough them and render the models inside of each node...

        ////////////////////////////////////////////////////////////////////////////////////
        // visual render mode (solid objects)


        if((renderMode & PolygonModeStandard) == PolygonModeStandard){


            ////////////////////////////////////////////////////////////////////////////////////
            // FIRST PASS of DEFERED RENDERER... fill the buffers

            //set up framebuffer

            // bind framebuffer
            glBindFramebuffer(GL_FRAMEBUFFER, fb);
            //glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
            glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


            glUseProgram(DR_FirstPassProgramIdId);

            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


            //STATIC MODELS
            for(int i = 0; i < ot_nodes.size(); i++){
                //render one node...

                //copy the lists so we can itterate through them
                QList<QList<CompositeObject*> > compositeobject_mesh_list = ot_nodes.at(i)->getModelLibrary()->getCompositeobjectMeshList();
                QList<QList<Mesh*> > mesh_model_list = ot_nodes.at(i)->getModelLibrary()->getMeshModelList();
                QList<QList<Model*> > model_mesh_list = ot_nodes.at(i)->getModelLibrary()->getModelMeshList();
                QList<Material*> material_mesh_list = ot_nodes.at(i)->getModelLibrary()->getMaterialMeshList();

                //loop trough the material_mesh_list
                for(int index = 0; index < material_mesh_list.size(); index++){

                    //check if material was loaded...
                    if(material_mesh_list[index]->isLoaded()){
                        //now set up the material and mesh

                        //tex
                        glActiveTexture (GL_TEXTURE0+firstTextureIndex);
                        glBindTexture(GL_TEXTURE_2D, material_mesh_list[index]->get_diffuse_map_texture());
                        glUniform1i(glGetUniformLocation(DR_FirstPassProgramIdId, "sampler1"), firstTextureIndex);

                        texBindsPerFrameCount += 1;


                        ///////////////////////////////////////////////////////////////////////////////////
                        ///
                        /// TODO:
                        ///
                        /// WE NEED TO CHECK IF THE MESH DATA IS UNIQUE..
                        /// BUT AT THIS POINt WE ASUME IT's ALLWAYS THE SAME
                        ///
                        ///////

                        if(mesh_model_list[index].size()>0){
                            Mesh * mesh = mesh_model_list[index].at(0);

                            //VAO

                            glBindVertexArray(mesh->get_vertex_array_object());

                            //VBOs
                            glBindBuffer(GL_ARRAY_BUFFER, mesh->get_vertex_vbo());
                            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
                            glEnableVertexAttribArray(0);

                            glBindBuffer(GL_ARRAY_BUFFER, mesh->get_texcoord_vbo());
                            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
                            glEnableVertexAttribArray(1);

                            glBindBuffer(GL_ARRAY_BUFFER, mesh->get_normal_vbo());
                            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
                            glEnableVertexAttribArray(2);

                            //now lets draw for every model it's meshs

                            //draw
                            int rendered = 0;
                            for(int mdl_index = 0; mdl_index < model_mesh_list[index].size(); mdl_index++){

                                //calculate if we need to draw the model
                                Model * mdl =  model_mesh_list[index].at(mdl_index);

                                Positation * posi = compositeobject_mesh_list[index].at(mdl_index)->getPositation();

                                m_m = posi->get_model_matrix();
                                vm_m = v_m * m_m;
                                pvm_m = p_m * v_m * m_m;


                                // don't need to check every mesh now if it is in the frustum yay....

                                //TRANSPOSE
                                for (int f = 0; f < 4; f++) {
                                    for (int g = 0; g < 4; g++) {
                                        p_mat[f * 4 + g] = (GLfloat) (p_m[f*4+g]);
                                        v_mat[f * 4 + g] = (GLfloat) (v_m[f*4+g]);
                                        m_mat[f * 4 + g] = (GLfloat) (m_m[f*4+g]);
                                        vm_mat[f * 4 + g] = (GLfloat) (vm_m[f*4+g]);
                                    }
                                }




                                glUniformMatrix4fv(p_mat_loc_firtpass, 1, GL_FALSE, p_mat);
                                glUniformMatrix4fv(v_mat_loc_firtpass, 1, GL_FALSE, v_mat);
                                glUniformMatrix4fv(m_mat_loc_firtpass, 1, GL_FALSE, m_mat);
                                glUniformMatrix4fv(vm_mat_loc_firtpass, 1, GL_FALSE, vm_mat);



                                //draw
                                glDrawArrays(GL_TRIANGLES, 0, mesh->get_triangle_count()*3);
                                rendered += 1;
                                meshPerFrameCount +=1;
                                trianglesPerFrameCount += mesh->get_triangle_count();
                            }

                            //debugMessage("Rendered: " + QString::number(rendered));
                        }
                    }
                }
            }

            //DYNAMIC MODELS
            for(int i = 0; i < ot_dynamic_models_nodes.size(); i++){
                //render one node...

                //copy the lists so we can itterate through them
                QList<CompositeObject*> compositeobject_list = ot_dynamic_models_nodes.at(i)->getCompositeObjects();

                //loop trough the material_mesh_list
                for(int index = 0; index < compositeobject_list.size(); index++){

                    CompositeObject * compobj = compositeobject_list.at(index);
                    Positation * posi = compobj->getPositation();
                    QList<Mesh*> mesh_list = compobj->getModel()->get_meshs();

                    //loop trough mesh...
                    for(int meshs = 0; meshs < mesh_list.size(); meshs++){

                        Mesh * mesh = mesh_list[meshs];

                        //now set up the material and mesh

                        //tex
                        glActiveTexture (GL_TEXTURE0+firstTextureIndex);
                        glBindTexture(GL_TEXTURE_2D, mesh->get_material()->get_diffuse_map_texture());
                        glUniform1i(glGetUniformLocation(DR_FirstPassProgramIdId, "sampler1"), firstTextureIndex);

                        texBindsPerFrameCount += 1;


                        ///////////////////////////////////////////////////////////////////////////////////
                        ///
                        /// TODO:
                        ///
                        /// WE NEED TO CHECK IF THE MESH DATA IS UNIQUE..
                        /// BUT AT THIS POINt WE ASUME IT's ALLWAYS THE SAME
                        ///
                        ///////


                        //VAO

                        glBindVertexArray(mesh->get_vertex_array_object());

                        //VBOs
                        glBindBuffer(GL_ARRAY_BUFFER, mesh->get_vertex_vbo());
                        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
                        glEnableVertexAttribArray(0);

                        glBindBuffer(GL_ARRAY_BUFFER, mesh->get_texcoord_vbo());
                        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
                        glEnableVertexAttribArray(1);

                        glBindBuffer(GL_ARRAY_BUFFER, mesh->get_normal_vbo());
                        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
                        glEnableVertexAttribArray(2);

                        //now lets draw for every model it's meshs

                        //draw


                        m_m = posi->get_model_matrix();
                        vm_m = v_m * m_m;
                        pvm_m = p_m * v_m * m_m;


                        // don't need to check every mesh now if it is in the frustum yay....

                        //TRANSPOSE
                        for (int f = 0; f < 4; f++) {
                            for (int g = 0; g < 4; g++) {
                                p_mat[f * 4 + g] = (GLfloat) (p_m[f*4+g]);
                                v_mat[f * 4 + g] = (GLfloat) (v_m[f*4+g]);
                                m_mat[f * 4 + g] = (GLfloat) (m_m[f*4+g]);
                                vm_mat[f * 4 + g] = (GLfloat) (vm_m[f*4+g]);
                            }
                        }




                        glUniformMatrix4fv(p_mat_loc_firtpass, 1, GL_FALSE, p_mat);
                        glUniformMatrix4fv(v_mat_loc_firtpass, 1, GL_FALSE, v_mat);
                        glUniformMatrix4fv(m_mat_loc_firtpass, 1, GL_FALSE, m_mat);
                        glUniformMatrix4fv(vm_mat_loc_firtpass, 1, GL_FALSE, vm_mat);



                        //draw
                        glDrawArrays(GL_TRIANGLES, 0, mesh->get_triangle_count()*3);
                        meshPerFrameCount +=1;
                        trianglesPerFrameCount += mesh->get_triangle_count();
                    }

                    //debugMessage("Rendered: " + QString::number(rendered));

                }
            }


            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, 0);


            ////////////////////////////////////////////////////////////////////////////////////
            // SECOND PASS of DEFERED RENDERER... take the filled buffers and ...
            // add some sexyness to them :P


            glBindFramebuffer (GL_FRAMEBUFFER, 0);
            //glDrawBuffer(GL_BACK);
            glClearColor (0.0, 0.0, 0.0, 1.0f); // no ambient... we add it later...
            glClear (GL_COLOR_BUFFER_BIT);

            glEnable (GL_BLEND); // --- could reject background frags!
            glBlendEquation (GL_FUNC_ADD);
            glBlendFunc (GL_ONE, GL_ONE); // addition each time

            glDisable (GL_DEPTH_TEST);
            glDepthMask (GL_FALSE);

            glActiveTexture (GL_TEXTURE0);
            glBindTexture (GL_TEXTURE_2D, fb_tex_p);

            glActiveTexture (GL_TEXTURE1);
            glBindTexture (GL_TEXTURE_2D, fb_tex_n);

            glActiveTexture (GL_TEXTURE2);
            glBindTexture (GL_TEXTURE_2D, fb_tex_c);

            glUseProgram (DR_SecondPassProgramIdId);

            glPolygonMode(GL_FRONT, GL_FILL);

            glUniform2f (win_size_loc_secondpass, win->getWindowWidth(), win->getWindowHeight());

            for(int i = 0; i < ot_nodes.size(); i++){
                //render one node...


                //copy the lists so we can itterate through them
                QList<QList<Mesh*> > l_mesh_model_list = lightlib->getMeshModelList();
                QList<QList<Model*> > l_model_mesh_list = lightlib->getModelMeshList();
                QList<QList<Light*> > l_light_mesh_list = lightlib->getLightMeshList();
                QList<Material*> l_material_mesh_list = lightlib->getMaterialMeshList();


                //loop trough the material_mesh_list
                for(int index = 0; index < l_material_mesh_list.size(); index++){
                    ///////////////////////////////////////////////////////////////////////////////////
                    ///
                    /// TODO:
                    ///
                    /// WE NEED TO CHECK IF THE MESH DATA IS UNIQUE..
                    /// BUT AT THIS POINt WE ASUME IT's ALLWAYS THE SAME
                    ///
                    ///////

                    if(l_mesh_model_list[index].size()>0){


                        Mesh * mesh = l_mesh_model_list[index].at(0);

                        //VAO

                        glBindVertexArray(mesh->get_vertex_array_object());

                        //VBOs
                        glBindBuffer(GL_ARRAY_BUFFER, mesh->get_vertex_vbo());
                        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
                        glEnableVertexAttribArray(0);

                        //tex coords actually not needed!!!
                        glBindBuffer(GL_ARRAY_BUFFER, mesh->get_texcoord_vbo());
                        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
                        glEnableVertexAttribArray(1);

                        glBindBuffer(GL_ARRAY_BUFFER, mesh->get_normal_vbo());
                        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
                        glEnableVertexAttribArray(2);



                        //draw
                        int rendered = 0;
                        for(int mdl_index = 0; mdl_index < l_model_mesh_list[index].size(); mdl_index++){
                            Model * mdl =  l_model_mesh_list[index].at(mdl_index);

                            Positation * posi = mdl->getParentCompositeObject()->getPositation();

                            vm_m = v_m * m_m;
                            pvm_m = p_m * v_m * m_m;


                            if(meshInFrustum(frustum, mdl, mesh, pvm_m)){

                                Light * light =  l_light_mesh_list[index].at(mdl_index);

                                /*
                                Indizes
                                |    0        4        8        12   |
                                |                                    |
                                |    1        5        9        13   |
                                |                                    |
                                |    2        6        10       14   |
                                |                                    |
                                |    3        7        11       15   |
                                */

                                //set the mesh to a billboard like position (give it the cam's rotation)
                                m_m = posi->get_model_matrix();


                                pvm_m = p_m * v_m * m_m;

                                for (int f = 0; f < 4; f++) {
                                    for (int g = 0; g < 4; g++) {
                                        p_mat[f * 4 + g] = (GLfloat) (p_m[f*4+g]);
                                        v_mat[f * 4 + g] = (GLfloat) (v_m[f*4+g]);
                                        m_mat[f * 4 + g] = (GLfloat) (m_m[f*4+g]);
                                        pvm_mat[f * 4 + g] = (GLfloat) (pvm_m[f*4+g]);
                                    }
                                }


                                glUniformMatrix4fv(p_mat_loc_secondpass, 1, GL_FALSE, p_mat);
                                glUniformMatrix4fv(v_mat_loc_secondpass, 1, GL_FALSE, v_mat);
                                glUniformMatrix4fv(m_mat_loc_secondpass, 1, GL_FALSE, m_mat);
                                glUniformMatrix4fv(pvm_mat_loc_secondpass, 1, GL_FALSE, pvm_mat);

                                glUniform3f (lp_loc_secondpass, posi->getPosition().x(),
                                                                posi->getPosition().y(),
                                                                posi->getPosition().z()); // world position
                                glUniform3f (ld_loc_secondpass, light->getDiffuseColor().x(),
                                                                light->getDiffuseColor().y(),
                                                                light->getDiffuseColor().z()); // diffuse colour
                                glUniform3f (ls_loc_secondpass, light->getSpecularColor().x(),
                                                                light->getSpecularColor().y(),
                                                                light->getSpecularColor().z()); // specular colour

                                //draw
                                glDrawArrays(GL_TRIANGLES, 0, mesh->get_triangle_count()*3);
                                rendered += 1;
                            }
                        }
                    }
                }
            }


        }










        //disable stuff so the gl_VertexID var works in GLSL
        /*
            glBindVertexArray(0);

            //VBOs
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glDisableVertexAttribArray(0);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glDisableVertexAttribArray(1);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glDisableVertexAttribArray(2);
            */


        //glBindFramebuffer (GL_FRAMEBUFFER, 0);





        /////////////////////////////////////////////////////////////////////////////////
        ///
        /// AMBIENT LIGHT PASS
        ///
        ///

        glBindVertexArray(fsq_vertex_array_object);

        //VBOs
        glBindBuffer(GL_ARRAY_BUFFER, fsq_vertex_vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);

        //tex coords actually not needed!!!
        glBindBuffer(GL_ARRAY_BUFFER, fsq_texcoord_vbo);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, fsq_normal_vbo);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(2);

        glUseProgram (DR_AmbientPassProgramIdId);

        glPolygonMode(GL_FRONT_AND_BACK, GL_POLYGON);

        glUniform2f (win_size_loc_ambientpass, win->getWindowWidth(), win->getWindowHeight());

        glUniform3f (color_loc_ambientpass,
                     0.110,
                     0.110,
                     0.108); // ambient color

        //glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glDrawArrays(GL_TRIANGLES, 0, triangle_count*3);







        /////////////////////////////////////////////////////////////////////////////////
        ///
        /// DIRECTIONAL AMBIENT LIGHT PASS
        ///


        glBindVertexArray(fsq_vertex_array_object);

        //VBOs
        glBindBuffer(GL_ARRAY_BUFFER, fsq_vertex_vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);

        //tex coords actually not needed!!!
        glBindBuffer(GL_ARRAY_BUFFER, fsq_texcoord_vbo);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, fsq_normal_vbo);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(2);

        glUseProgram (DR_DirectionalAmbientPassProgramIdId);

        glPolygonMode(GL_FRONT_AND_BACK, GL_POLYGON);

        glUniform2f (win_size_loc_directionalambientpass, win->getWindowWidth(), win->getWindowHeight());

        glUniform3f (dir_loc_directionalambientpass,    0.5,
                     -1.0,
                     0.5); // ambient light direction

        glUniform3f (color_loc_directionalambientpass,  0.150,
                     0.150,
                     0.148); // ambient color


        for (int f = 0; f < 4; f++) {
            for (int g = 0; g < 4; g++) {
                v_mat[f * 4 + g] = (GLfloat) (v_m[f*4+g]);
            }
        }


        glUniformMatrix4fv(v_mat_loc_directionalambientpass, 1, GL_FALSE, v_mat);

        //glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glDrawArrays(GL_TRIANGLES, 0, triangle_count*3);


        //
        // DRAWING FINISHED
        //////////////////////////////////////////////////////////////////////////////////////////


        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, 0);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, 0);

        glEnable (GL_DEPTH_TEST);
        glDepthMask (GL_TRUE);
        glDisable (GL_BLEND);

    }//end of PolygonModeStandard



    /*


        if((renderMode & PolygonModeWireframe) == PolygonModeWireframe){

            glUseProgram (DR_DebugPassProgramIdId);

            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

            glClear(GL_DEPTH_BUFFER_BIT);


            //the color we want to render in...
            glUniform3f (color_loc_debugpass, 1.0, 1.0, 1.0);


            //copy the lists so we can itterate through them
            QList<QList<Mesh*> > mesh_model_list = mdllib->getMeshModelList();
            QList<QList<Model*> > model_mesh_list = mdllib->getModelMeshList();
            //QList<QList<Light*> > light_mesh_list = mdllib->getLightMeshList();
            QList<Material*> material_mesh_list = mdllib->getMaterialMeshList();



            //loop trough the material_mesh_list
            for(int index = 0; index < material_mesh_list.size(); index++){

                if(mesh_model_list[index].size()>0){


                    Mesh * mesh = mesh_model_list[index].at(0);

                    //VAO

                    glBindVertexArray(mesh->get_vertex_array_object());

                    //VBOs
                    glBindBuffer(GL_ARRAY_BUFFER, mesh->get_vertex_vbo());
                    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
                    glEnableVertexAttribArray(0);


                    //draw

                    for(int mdl_index = 0; mdl_index < model_mesh_list[index].size(); mdl_index++){
                        Model * mdl =  model_mesh_list[index].at(mdl_index);

                        Positation * posi = mdl->getParentCompositeObject()->getPositation();

                        if(true){
                            m_m = posi->get_model_matrix();

                            pvm_m = p_m * v_m * m_m;

                            for (int f = 0; f < 4; f++) {
                                for (int g = 0; g < 4; g++) {
                                    pvm_mat[f * 4 + g] = (GLfloat) (pvm_m[f*4+g]);
                                }
                            }


                            glUniformMatrix4fv(pvm_mat_loc_debugpass, 1, GL_FALSE, pvm_mat);

                            //draw
                            glDrawArrays(GL_TRIANGLES, 0, mesh->get_triangle_count()*3);
                        }
                    }
                }
            }
        }//end of PolygonModeWirframe








        if((renderMode & PolygonModeVertex) == PolygonModeVertex){

            glUseProgram (DR_DebugPassProgramIdId);

            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

            glClear(GL_DEPTH_BUFFER_BIT);


            //the color we want to render in...
            glUniform3f (color_loc_debugpass, 1.0, 0.0, 0.0);


            //copy the lists so we can itterate through them
            QList<QList<Mesh*> > mesh_model_list = mdllib->getMeshModelList();
            QList<QList<Model*> > model_mesh_list = mdllib->getModelMeshList();
            //QList<QList<Light*> > light_mesh_list = mdllib->getLightMeshList();
            QList<Material*> material_mesh_list = mdllib->getMaterialMeshList();



            //loop trough the material_mesh_list
            for(int index = 0; index < material_mesh_list.size(); index++){

                if(mesh_model_list[index].size()>0){


                    Mesh * mesh = mesh_model_list[index].at(0);

                    //VAO

                    glBindVertexArray(mesh->get_vertex_array_object());

                    //VBOs
                    glBindBuffer(GL_ARRAY_BUFFER, mesh->get_vertex_vbo());
                    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
                    glEnableVertexAttribArray(0);

                    //draw

                    for(int mdl_index = 0; mdl_index < model_mesh_list[index].size(); mdl_index++){
                        Model * mdl =  model_mesh_list[index].at(mdl_index);

                        Positation * posi = mdl->getParentCompositeObject()->getPositation();

                        if(true){

                            m_m = posi->get_model_matrix();

                            pvm_m = p_m * v_m * m_m;

                            for (int f = 0; f < 4; f++) {
                                for (int g = 0; g < 4; g++) {
                                    pvm_mat[f * 4 + g] = (GLfloat) (pvm_m[f*4+g]);
                                }
                            }


                            glUniformMatrix4fv(pvm_mat_loc_debugpass, 1, GL_FALSE, pvm_mat);

                            //draw
                            glDrawArrays(GL_TRIANGLES, 0, mesh->get_triangle_count()*3);
                        }
                    }
                }
            }
        }//end of PolygonModeVertex

        */
}















//OLD RENDERING CRAP







void Renderer::render(){

    int step = 1;

    //check if the mdllib is ready
    if(mdllib!=0 && lightlib!=0){


        //get the shader to work...


        //glClearColor (0.0f, 0.0f, 0.0f, 0.0f);

        //camera matrix
        p_m.set_to_identity();
        p_m.perspective(cam->getFOV(), float(win->getWindowWidth()) / float(win->getWindowHeight()),
                        cam->getZNEAR(), cam->getZFAR());

        v_m = cam->get_view_matrix();//.inverted();



        double near_ = cam->getZNEAR();
        double far_ = cam->getZFAR();

        Frustum frustum;
        //setting up the clipping points/planes...
        frustum.setPoints(cam->getPosition() - touch_to_space(0,0)*near_,
                          cam->getPosition() - touch_to_space(win->getWindowWidth(),0)*near_,
                          cam->getPosition() - touch_to_space(0,win->getWindowHeight())*near_,
                          cam->getPosition() - touch_to_space(win->getWindowWidth(),win->getWindowHeight())*near_,
                          cam->getPosition() - touch_to_space(0,0)*far_,
                          cam->getPosition() - touch_to_space(win->getWindowWidth(),0)*far_,
                          cam->getPosition() - touch_to_space(0,win->getWindowHeight())*far_,
                          cam->getPosition() - touch_to_space(win->getWindowWidth(),win->getWindowHeight())*far_);




        if((renderMode & PolygonModeStandard) == PolygonModeStandard){

            //set up framebuffer

            // bind framebuffer
            glBindFramebuffer(GL_FRAMEBUFFER, fb);
            //glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
            glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


            glUseProgram(DR_FirstPassProgramIdId);

            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

            /////////////////////////////////////////////////////////////////////////////////
            //first pass
            //

            //copy the lists so we can itterate through them
            QList<QList<Mesh*> > mesh_model_list = mdllib->getMeshModelList();
            QList<QList<Model*> > model_mesh_list = mdllib->getModelMeshList();
            QList<Material*> material_mesh_list = mdllib->getMaterialMeshList();

            //loop trough the material_mesh_list
            for(int index = 0; index < material_mesh_list.size(); index++){
                //now set up the material and mesh

                //tex
                glActiveTexture (GL_TEXTURE0+firstTextureIndex);
                glBindTexture(GL_TEXTURE_2D, material_mesh_list[index]->get_diffuse_map_texture());
                glUniform1i(glGetUniformLocation(DR_FirstPassProgramIdId, "sampler1"), firstTextureIndex);

                ///////////////////////////////////////////////////////////////////////////////////
                ///
                /// TODO:
                ///
                /// WE NEED TO CHECK IF THE MESH DATA IS UNIQUE..
                /// BUT AT THIS POINt WE ASUME IT's ALLWAYS THE SAME
                ///
                ///////

                if(mesh_model_list[index].size()>0){
                    Mesh * mesh = mesh_model_list[index].at(0);

                    //VAO

                    glBindVertexArray(mesh->get_vertex_array_object());

                    //VBOs
                    glBindBuffer(GL_ARRAY_BUFFER, mesh->get_vertex_vbo());
                    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
                    glEnableVertexAttribArray(0);

                    glBindBuffer(GL_ARRAY_BUFFER, mesh->get_texcoord_vbo());
                    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
                    glEnableVertexAttribArray(1);

                    glBindBuffer(GL_ARRAY_BUFFER, mesh->get_normal_vbo());
                    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
                    glEnableVertexAttribArray(2);

                    //now lets draw for every model it's meshs


                    //old stuff
                    /*
                    m_p.set_to_identity();
                    m_p.perspective(cam->FOV, float(win->getWindowWidth()) / float(win->getWindowHeight()),
                                    cam->Z_NEAR, cam->Z_FAR);

                    for(int mdl_index = 0; mdl_index < model_mesh_list[index].size(); mdl_index++){
                        Model * mdl =  model_mesh_list[index].at(mdl_index);

                        m_mvp =cam->M_camera_view.inverted() * mdl->get_model_matrix();
                        m_norm = m_mvp.inverted();
                        m_mvp = m_p * m_mvp;

                        for (int f = 0; f < 4; f++) {
                            for (int g = 0; g < 4; g++) {
                                mvp_mat[f * 4 + g] = (GLfloat) (m_mvp[f*4+g]);
                                norm_mat[f * 4 + g] = (GLfloat) (m_norm[f*4+g]);
                            }
                        }


                        glUniformMatrix4fv(mvp_mat_loc, 1, GL_FALSE, mvp_mat);
                        glUniformMatrix4fv(norm_mat_loc, 1, GL_FALSE, norm_mat);


                        glUniformMatrix4fv(mvp_mat_loc, 1, GL_FALSE, mvp_mat);
                        glUniformMatrix4fv(norm_mat_loc, 1, GL_FALSE, norm_mat);


                        //draw
                        glDrawArrays(GL_TRIANGLES, 0, mesh->get_triangle_count()*3);
                    }
                    */

                    //new stuff


                    //draw
                    int rendered = 0;
                    for(int mdl_index = 0; mdl_index < model_mesh_list[index].size(); mdl_index++){

                        //calculate if we need to draw the model
                        Model * mdl =  model_mesh_list[index].at(mdl_index);

                        Positation * posi = mdl->getParentCompositeObject()->getPositation();

                        m_m = posi->get_model_matrix();
                        vm_m = v_m * m_m;
                        pvm_m = p_m * v_m * m_m;




                        if(meshInFrustum(frustum, mdl, mesh, pvm_m)){


                            //TRANSPOSE
                            for (int f = 0; f < 4; f++) {
                                for (int g = 0; g < 4; g++) {
                                    p_mat[f * 4 + g] = (GLfloat) (p_m[f*4+g]);
                                    v_mat[f * 4 + g] = (GLfloat) (v_m[f*4+g]);
                                    m_mat[f * 4 + g] = (GLfloat) (m_m[f*4+g]);
                                    vm_mat[f * 4 + g] = (GLfloat) (vm_m[f*4+g]);
                                }
                            }




                            glUniformMatrix4fv(p_mat_loc_firtpass, 1, GL_FALSE, p_mat);
                            glUniformMatrix4fv(v_mat_loc_firtpass, 1, GL_FALSE, v_mat);
                            glUniformMatrix4fv(m_mat_loc_firtpass, 1, GL_FALSE, m_mat);
                            glUniformMatrix4fv(vm_mat_loc_firtpass, 1, GL_FALSE, vm_mat);



                            //draw
                            glDrawArrays(GL_TRIANGLES, 0, mesh->get_triangle_count()*3);
                            rendered += 1;
                        }
                    }

                    /*
                    debugMessage("Rendered: " +
                                 QString::number(rendered) + " / " +
                                 QString::number(model_mesh_list[index].size()) + " models.");
                    */
                }
            }



            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, 0);



            ////////////////////////////////////////////////////////////////////////
            //  second pass
            //

            glBindFramebuffer (GL_FRAMEBUFFER, 0);
            //glDrawBuffer(GL_BACK);
            glClearColor (0.0, 0.0, 0.0, 1.0f); // added ambient light here
            glClear (GL_COLOR_BUFFER_BIT);

            glEnable (GL_BLEND); // --- could reject background frags!
            glBlendEquation (GL_FUNC_ADD);
            glBlendFunc (GL_ONE, GL_ONE); // addition each time

            glDisable (GL_DEPTH_TEST);
            glDepthMask (GL_FALSE);


            glActiveTexture (GL_TEXTURE0);
            glBindTexture (GL_TEXTURE_2D, fb_tex_p);



            glActiveTexture (GL_TEXTURE1);
            glBindTexture (GL_TEXTURE_2D, fb_tex_n);



            glActiveTexture (GL_TEXTURE2);
            glBindTexture (GL_TEXTURE_2D, fb_tex_c);


            glUseProgram (DR_SecondPassProgramIdId);


            glPolygonMode(GL_FRONT, GL_FILL);

            glUniform2f (win_size_loc_secondpass, win->getWindowWidth(), win->getWindowHeight());


            //copy the lists so we can itterate through them
            QList<QList<Mesh*> > l_mesh_model_list = lightlib->getMeshModelList();
            QList<QList<Model*> > l_model_mesh_list = lightlib->getModelMeshList();
            QList<QList<Light*> > l_light_mesh_list = lightlib->getLightMeshList();
            QList<Material*> l_material_mesh_list = lightlib->getMaterialMeshList();



            //loop trough the material_mesh_list
            for(int index = 0; index < l_material_mesh_list.size(); index++){
                ///////////////////////////////////////////////////////////////////////////////////
                ///
                /// TODO:
                ///
                /// WE NEED TO CHECK IF THE MESH DATA IS UNIQUE..
                /// BUT AT THIS POINt WE ASUME IT's ALLWAYS THE SAME
                ///
                ///////

                if(l_mesh_model_list[index].size()>0){


                    Mesh * mesh = l_mesh_model_list[index].at(0);

                    //VAO

                    glBindVertexArray(mesh->get_vertex_array_object());

                    //VBOs
                    glBindBuffer(GL_ARRAY_BUFFER, mesh->get_vertex_vbo());
                    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
                    glEnableVertexAttribArray(0);

                    //tex coords actually not needed!!!
                    glBindBuffer(GL_ARRAY_BUFFER, mesh->get_texcoord_vbo());
                    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
                    glEnableVertexAttribArray(1);

                    glBindBuffer(GL_ARRAY_BUFFER, mesh->get_normal_vbo());
                    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
                    glEnableVertexAttribArray(2);



                    //draw
                    int rendered = 0;
                    for(int mdl_index = 0; mdl_index < l_model_mesh_list[index].size(); mdl_index++){
                        Model * mdl =  l_model_mesh_list[index].at(mdl_index);

                        Positation * posi = mdl->getParentCompositeObject()->getPositation();

                        vm_m = v_m * m_m;
                        pvm_m = p_m * v_m * m_m;


                        if(meshInFrustum(frustum, mdl, mesh, pvm_m)){

                            Light * light =  l_light_mesh_list[index].at(mdl_index);

                      /*
                            Indizes
                            |    0        4        8        12   |
                            |                                    |
                            |    1        5        9        13   |
                            |                                    |
                            |    2        6        10       14   |
                            |                                    |
                            |    3        7        11       15   |
                        */

                            //set the mesh to a billboard like position (give it the cam's rotation)
                            m_m = posi->get_model_matrix();
                            /*
                            Vector3 scale_vec = m_m.get_vector_scale();
                            m_m[0] = v_m[0];
                            m_m[1] = v_m[1];
                            m_m[2] = v_m[2];
                            m_m[4] = v_m[4];
                            m_m[5] = v_m[5];
                            m_m[6] = v_m[6];
                            m_m[8] = v_m[8];
                            m_m[9] = v_m[9];
                            m_m[10] = v_m[10];

                            m_m.scale(scale_vec);
                            */

                            pvm_m = p_m * v_m * m_m;

                            for (int f = 0; f < 4; f++) {
                                for (int g = 0; g < 4; g++) {
                                    p_mat[f * 4 + g] = (GLfloat) (p_m[f*4+g]);
                                    v_mat[f * 4 + g] = (GLfloat) (v_m[f*4+g]);
                                    m_mat[f * 4 + g] = (GLfloat) (m_m[f*4+g]);
                                    pvm_mat[f * 4 + g] = (GLfloat) (pvm_m[f*4+g]);
                                }
                            }


                            glUniformMatrix4fv(p_mat_loc_secondpass, 1, GL_FALSE, p_mat);
                            glUniformMatrix4fv(v_mat_loc_secondpass, 1, GL_FALSE, v_mat);
                            glUniformMatrix4fv(m_mat_loc_secondpass, 1, GL_FALSE, m_mat);
                            glUniformMatrix4fv(pvm_mat_loc_secondpass, 1, GL_FALSE, pvm_mat);

                            glUniform3f (lp_loc_secondpass, posi->getPosition().x(),
                                                            posi->getPosition().y(),
                                                            posi->getPosition().z()); // world position
                            glUniform3f (ld_loc_secondpass, light->getDiffuseColor().x(),
                                                            light->getDiffuseColor().y(),
                                                            light->getDiffuseColor().z()); // diffuse colour
                            glUniform3f (ls_loc_secondpass, light->getSpecularColor().x(),
                                                            light->getSpecularColor().y(),
                                                            light->getSpecularColor().z()); // specular colour

                            //draw
                            glDrawArrays(GL_TRIANGLES, 0, mesh->get_triangle_count()*3);
                            rendered += 1;
                        }
                    }
                    /*
                    debugMessage("Rendered: " +
                                 QString::number(rendered) + " / " +
                                 QString::number(l_model_mesh_list[index].size()) + " lights.");
                    */
                }
            }




            //disable stuff so the gl_VertexID var works in GLSL
            /*
            glBindVertexArray(0);

            //VBOs
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glDisableVertexAttribArray(0);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glDisableVertexAttribArray(1);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glDisableVertexAttribArray(2);
            */


            //glBindFramebuffer (GL_FRAMEBUFFER, 0);





            /////////////////////////////////////////////////////////////////////////////////
            ///
            /// AMBIENT LIGHT PASS
            ///
            ///

            glBindVertexArray(fsq_vertex_array_object);

            //VBOs
            glBindBuffer(GL_ARRAY_BUFFER, fsq_vertex_vbo);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
            glEnableVertexAttribArray(0);

            //tex coords actually not needed!!!
            glBindBuffer(GL_ARRAY_BUFFER, fsq_texcoord_vbo);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
            glEnableVertexAttribArray(1);

            glBindBuffer(GL_ARRAY_BUFFER, fsq_normal_vbo);
            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
            glEnableVertexAttribArray(2);

            glUseProgram (DR_AmbientPassProgramIdId);

            glPolygonMode(GL_FRONT_AND_BACK, GL_POLYGON);

            glUniform2f (win_size_loc_ambientpass, win->getWindowWidth(), win->getWindowHeight());

            glUniform3f (color_loc_ambientpass, 0.010,
                                                0.010,
                                                0.008); // ambient color

            //glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
            glDrawArrays(GL_TRIANGLES, 0, triangle_count*3);







            /////////////////////////////////////////////////////////////////////////////////
            ///
            /// DIRECTIONAL AMBIENT LIGHT PASS
            ///


            glBindVertexArray(fsq_vertex_array_object);

            //VBOs
            glBindBuffer(GL_ARRAY_BUFFER, fsq_vertex_vbo);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
            glEnableVertexAttribArray(0);

            //tex coords actually not needed!!!
            glBindBuffer(GL_ARRAY_BUFFER, fsq_texcoord_vbo);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
            glEnableVertexAttribArray(1);

            glBindBuffer(GL_ARRAY_BUFFER, fsq_normal_vbo);
            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
            glEnableVertexAttribArray(2);

            glUseProgram (DR_DirectionalAmbientPassProgramIdId);

            glPolygonMode(GL_FRONT_AND_BACK, GL_POLYGON);

            glUniform2f (win_size_loc_directionalambientpass, win->getWindowWidth(), win->getWindowHeight());

            glUniform3f (dir_loc_directionalambientpass,    0.5,
                                                            -1.0,
                                                            0.5); // ambient light direction

            glUniform3f (color_loc_directionalambientpass,  0.050,
                                                            0.050,
                                                            0.048); // ambient color


            for (int f = 0; f < 4; f++) {
                for (int g = 0; g < 4; g++) {
                    v_mat[f * 4 + g] = (GLfloat) (v_m[f*4+g]);
                }
            }


            glUniformMatrix4fv(v_mat_loc_directionalambientpass, 1, GL_FALSE, v_mat);

            //glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
            glDrawArrays(GL_TRIANGLES, 0, triangle_count*3);


            //
            // DRAWING FINISHED
            //////////////////////////////////////////////////////////////////////////////////////////


            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, 0);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, 0);
            glActiveTexture(GL_TEXTURE2);
            glBindTexture(GL_TEXTURE_2D, 0);

            glEnable (GL_DEPTH_TEST);
            glDepthMask (GL_TRUE);
            glDisable (GL_BLEND);

        }//end of PolygonModeStandard





        if((renderMode & PolygonModeWireframe) == PolygonModeWireframe){

            glUseProgram (DR_DebugPassProgramIdId);

            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

            glClear(GL_DEPTH_BUFFER_BIT);


            //the color we want to render in...
            glUniform3f (color_loc_debugpass, 1.0, 1.0, 1.0);


            //copy the lists so we can itterate through them
            QList<QList<Mesh*> > mesh_model_list = mdllib->getMeshModelList();
            QList<QList<Model*> > model_mesh_list = mdllib->getModelMeshList();
            //QList<QList<Light*> > light_mesh_list = mdllib->getLightMeshList();
            QList<Material*> material_mesh_list = mdllib->getMaterialMeshList();



            //loop trough the material_mesh_list
            for(int index = 0; index < material_mesh_list.size(); index++){

                if(mesh_model_list[index].size()>0){


                    Mesh * mesh = mesh_model_list[index].at(0);

                    //VAO

                    glBindVertexArray(mesh->get_vertex_array_object());

                    //VBOs
                    glBindBuffer(GL_ARRAY_BUFFER, mesh->get_vertex_vbo());
                    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
                    glEnableVertexAttribArray(0);

                    /*
                    //tex coords actually not needed!!!
                    glBindBuffer(GL_ARRAY_BUFFER, mesh->get_texcoord_vbo());
                    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
                    glEnableVertexAttribArray(1);

                    glBindBuffer(GL_ARRAY_BUFFER, mesh->get_normal_vbo());
                    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
                    glEnableVertexAttribArray(2);
                    */


                    //draw

                    for(int mdl_index = 0; mdl_index < model_mesh_list[index].size(); mdl_index++){
                        Model * mdl =  model_mesh_list[index].at(mdl_index);

                        Positation * posi = mdl->getParentCompositeObject()->getPositation();

                        if(true){
                            m_m = posi->get_model_matrix();

                            pvm_m = p_m * v_m * m_m;

                            for (int f = 0; f < 4; f++) {
                                for (int g = 0; g < 4; g++) {
                                    pvm_mat[f * 4 + g] = (GLfloat) (pvm_m[f*4+g]);
                                }
                            }


                            glUniformMatrix4fv(pvm_mat_loc_debugpass, 1, GL_FALSE, pvm_mat);

                            //draw
                            glDrawArrays(GL_TRIANGLES, 0, mesh->get_triangle_count()*3);
                        }
                    }
                }
            }
        }//end of PolygonModeWirframe








        if((renderMode & PolygonModeVertex) == PolygonModeVertex){

            glUseProgram (DR_DebugPassProgramIdId);

            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

            glClear(GL_DEPTH_BUFFER_BIT);


            //the color we want to render in...
            glUniform3f (color_loc_debugpass, 1.0, 0.0, 0.0);


            //copy the lists so we can itterate through them
            QList<QList<Mesh*> > mesh_model_list = mdllib->getMeshModelList();
            QList<QList<Model*> > model_mesh_list = mdllib->getModelMeshList();
            //QList<QList<Light*> > light_mesh_list = mdllib->getLightMeshList();
            QList<Material*> material_mesh_list = mdllib->getMaterialMeshList();



            //loop trough the material_mesh_list
            for(int index = 0; index < material_mesh_list.size(); index++){

                if(mesh_model_list[index].size()>0){


                    Mesh * mesh = mesh_model_list[index].at(0);

                    //VAO

                    glBindVertexArray(mesh->get_vertex_array_object());

                    //VBOs
                    glBindBuffer(GL_ARRAY_BUFFER, mesh->get_vertex_vbo());
                    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
                    glEnableVertexAttribArray(0);

                    /*
                    //tex coords actually not needed!!!
                    glBindBuffer(GL_ARRAY_BUFFER, mesh->get_texcoord_vbo());
                    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
                    glEnableVertexAttribArray(1);

                    glBindBuffer(GL_ARRAY_BUFFER, mesh->get_normal_vbo());
                    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
                    glEnableVertexAttribArray(2);
                    */


                    //draw

                    for(int mdl_index = 0; mdl_index < model_mesh_list[index].size(); mdl_index++){
                        Model * mdl =  model_mesh_list[index].at(mdl_index);

                        Positation * posi = mdl->getParentCompositeObject()->getPositation();

                        if(true){

                            m_m = posi->get_model_matrix();

                            pvm_m = p_m * v_m * m_m;

                            for (int f = 0; f < 4; f++) {
                                for (int g = 0; g < 4; g++) {
                                    pvm_mat[f * 4 + g] = (GLfloat) (pvm_m[f*4+g]);
                                }
                            }


                            glUniformMatrix4fv(pvm_mat_loc_debugpass, 1, GL_FALSE, pvm_mat);

                            //draw
                            glDrawArrays(GL_TRIANGLES, 0, mesh->get_triangle_count()*3);
                        }
                    }
                }
            }
        }//end of PolygonModeVertex



    }
    else{
        debugMessage("ERROR during rendering: The ModelLibrary isn't set yet!");
    }
}

void Renderer::render(Model * m){

    /*
    if(m->isReadyToRender()){
        GLenum ErrorCheckValue = glGetError();
        if (ErrorCheckValue != GL_NO_ERROR)
        {
            debugMessage("ERROR before rendering: " + QString::fromLatin1((char*) gluErrorString(ErrorCheckValue)));
        }


        QList<Mesh*> meshs = m->get_meshs();

        m_p.set_to_identity();
        m_p.perspective(cam->getFOV(), float(win->getWindowWidth()) / float(win->getWindowHeight()),
                        cam->getZNEAR(), cam->getZFAR());

        m_mvp =cam->get_view_matrix().inverted() * m->get_model_matrix();
        m_norm = m_mvp.inverted();
        m_mvp = m_p * m_mvp;

        for (int f = 0; f < 4; f++) {
            for (int g = 0; g < 4; g++) {
                mvp_mat[f * 4 + g] = (GLfloat) (m_mvp[f*4+g]);
                norm_mat[f * 4 + g] = (GLfloat) (m_norm[f*4+g]);
            }
        }


        glUniformMatrix4fv(mvp_mat_loc, 1, GL_FALSE, mvp_mat);
        glUniformMatrix4fv(norm_mat_loc, 1, GL_FALSE, norm_mat);



        for(int i = 0; i < meshs.size(); i++){

            Mesh * mesh = meshs.at(i);


            //tex
            glBindTexture(GL_TEXTURE_2D, mesh->get_material()->get_diffuse_map_texture());

            //sample 2d
            glUniform1i(samp2d_loc, 0);


            //VAO

            glBindVertexArray(mesh->get_vertex_array_object());

            //VBOs
            glBindBuffer(GL_ARRAY_BUFFER, mesh->get_vertex_vbo());
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
            glEnableVertexAttribArray(0);

            glBindBuffer(GL_ARRAY_BUFFER, mesh->get_texcoord_vbo());
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
            glEnableVertexAttribArray(1);

            glBindBuffer(GL_ARRAY_BUFFER, mesh->get_normal_vbo());
            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
            glEnableVertexAttribArray(2);

            glDrawArrays(GL_TRIANGLES, 0, mesh->get_triangle_count()*3);
        }

        ErrorCheckValue = glGetError();
        if (ErrorCheckValue != GL_NO_ERROR)
        {
            debugMessage("ERROR after rendering: " + QString::fromLatin1((char*) gluErrorString(ErrorCheckValue)));
        }
    }
    */
}


void Renderer::setPolygonMode(int polygonMode){
    renderMode = polygonMode;
}

Vector3 Renderer::touch_to_space(int x,int y){
    Matrix4x4 M_projection;
    M_projection.perspective(cam->getFOV(),float(win->getWindowWidth()) / float(win->getWindowHeight()),cam->getZNEAR(),cam->getZFAR());

    Matrix4x4 camera_view_projection_m = M_projection * cam->get_view_matrix();

    Matrix4x4 inv_cam_view_projection = camera_view_projection_m.inverted();
    double touch_x = -(double(x)/(double(win->getWindowWidth())*0.5)-1.0);
    double touch_y = (double(y)/(double(win->getWindowHeight())*0.5)-1.0);
    Vector3 projected_pos_near = inv_cam_view_projection * Vector3( cam->getZNEAR() * touch_x, cam->getZNEAR() * touch_y, cam->getZNEAR() );
    Vector3 projected_pos_far  = inv_cam_view_projection * Vector3( cam->getZFAR() * touch_x, cam->getZFAR() * touch_y, cam->getZFAR() );
    Vector3 projected_pos = (projected_pos_far-projected_pos_near);
    return projected_pos.normalized();
}

int Renderer::getMeshPerFrameCount(){
    return meshPerFrameCount;
}

int Renderer::getTrianglesPerFrameCount(){
    return trianglesPerFrameCount;
}

int Renderer::getTexBindsPerFrameCount(){
    return texBindsPerFrameCount;
}


bool Renderer::createShaders(){
    debugMessage("creating shaders...");

    ////////////////////////////////////////////////////////////////
    //FUCK OLD STUFF DR FTW
    /*
    GLenum ErrorCheckValue = glGetError();

    VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(VertexShaderId, 1, &VertexShader, NULL);
    glCompileShader(VertexShaderId);

    GLint compiled;

    glGetShaderiv(VertexShaderId, GL_COMPILE_STATUS, &compiled);
    debugMessage(QString::number(compiled));
    if (compiled){
        debugMessage("vshader compiled");
    }
    else{
        debugMessage("vshader compile failed!!!");
        char messages[256];
        glGetShaderInfoLog(VertexShaderId, sizeof(messages), 0, &messages[0]);
        debugMessage(QString(messages));
    }



    FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(FragmentShaderId, 1, &FragmentShader, NULL);
    glCompileShader(FragmentShaderId);

    glGetShaderiv(FragmentShaderId, GL_COMPILE_STATUS, &compiled);
    debugMessage(QString::number(compiled));
    if (compiled){
        debugMessage("fshader compiled");
    }
    else{
        debugMessage("fshader compile failed!!!");
        char messages[256];
        glGetShaderInfoLog(FragmentShaderId, sizeof(messages), 0, &messages[0]);
        debugMessage(QString(messages));
    }



    ProgramId = glCreateProgram();
    glAttachShader(ProgramId, VertexShaderId);
    glAttachShader(ProgramId, FragmentShaderId);


    // Bind the custom vertex attributes
    glBindAttribLocation(ProgramId, 0, "vertex");
    glBindAttribLocation(ProgramId, 1, "texCoord");
    glBindAttribLocation(ProgramId, 2, "normal");





    glLinkProgram(ProgramId);

    GLint linked;
    glGetProgramiv(ProgramId, GL_LINK_STATUS, &linked);
    debugMessage(QString::number(linked));
    if (linked){
        debugMessage("program linked");
    }
    else{
        debugMessage("program linking failed!!!");
        char messages[256];
        glGetProgramInfoLog(ProgramId, sizeof(messages), 0, &messages[0]);
        debugMessage(QString(messages));
    }

    glUseProgram(ProgramId);

    ErrorCheckValue = glGetError();
    if (ErrorCheckValue != GL_NO_ERROR)
    {
        debugMessage("ERROR(3): Could not create the shaders: " + QString((char*) gluErrorString(ErrorCheckValue)));
        //exit(EXIT_FAILURE);
        return;
    }




    glEnable(GL_DEPTH_TEST);
    //glDepthMask(GL_TRUE);


    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    mvp_mat_loc = glGetUniformLocation(ProgramId, "mvp_matrix");
    norm_mat_loc = glGetUniformLocation(ProgramId, "norm_matrix");
    samp2d_loc = glGetUniformLocation(ProgramId, "sampler1");

    ErrorCheckValue = glGetError();
    if (ErrorCheckValue != GL_NO_ERROR)
    {
        debugMessage("ERROR: after Shader: " + QString((char*) gluErrorString(ErrorCheckValue)));
        //exit(EXIT_FAILURE);
        return;
    }
    */
    //
    // OLD STUFF END
    //////////////////////////////////////////////////////////////


    //////////////////////////////////////////////////////////////
    //NEW DR STUFF
    //

    ////////////////////////////////////////////////////////////////////////////////
    //FIRST SHADER
    GLenum ErrorCheckValue = glGetError();

    //vertex shader
    Shader dr_vertex_firstpass(QApplication::applicationDirPath() +
                               "/shaders/deferred_renderer_first_pass.vsh",
                               GL_VERTEX_SHADER);
    if(dr_vertex_firstpass.isCreated()){
        DR_FirstPassVertexShaderId = dr_vertex_firstpass.getShaderId();
        debugMessage("Deferred Renderer first pass vertex shader compiled successful.");
    }
    else{
        debugMessage("Deferred Renderer first pass vertex shader compiled failed!");
        debugMessage(dr_vertex_firstpass.getError());
        return false;
    }

    //fragment shader
    Shader dr_fragment_firstpass(QApplication::applicationDirPath() +
                               "/shaders/deferred_renderer_first_pass.fsh",
                               GL_FRAGMENT_SHADER);
    if(dr_fragment_firstpass.isCreated()){
        DR_FirstPassFragmentShaderId = dr_fragment_firstpass.getShaderId();
        debugMessage("Deferred Renderer first pass fragment shader compiled successful.");
    }
    else{
        debugMessage("Deferred Renderer first pass fragment shader compiled failed!");
        debugMessage(dr_fragment_firstpass.getError());
        return false;
    }


    //create program, link it and bind locs
    DR_FirstPassProgramIdId = glCreateProgram();
    glAttachShader(DR_FirstPassProgramIdId, DR_FirstPassVertexShaderId);
    glAttachShader(DR_FirstPassProgramIdId, DR_FirstPassFragmentShaderId);


    // Bind the custom vertex attributes
    glBindAttribLocation(DR_FirstPassProgramIdId, 0, "vp");
    glBindAttribLocation(DR_FirstPassProgramIdId, 1, "vt");
    glBindAttribLocation(DR_FirstPassProgramIdId, 2, "vn");


    glLinkProgram(DR_FirstPassProgramIdId);

    GLint linked;
    glGetProgramiv(DR_FirstPassProgramIdId, GL_LINK_STATUS, &linked);
    if (linked){
        debugMessage("deferred renderer program pass one linked");
    }
    else{
        debugMessage("deferred renderer program pass one linking failed!!!");
        char messages[256];
        glGetProgramInfoLog(DR_FirstPassProgramIdId, sizeof(messages), 0, &messages[0]);
        debugMessage(QString(messages));
        return false;
    }

    glUseProgram(DR_FirstPassProgramIdId);

    ErrorCheckValue = glGetError();
    if (ErrorCheckValue != GL_NO_ERROR)
    {
        debugMessage("ERROR(3): Could not create the shaders: " + QString((char*) gluErrorString(ErrorCheckValue)));
        //exit(EXIT_FAILURE);
        return false;
    }

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    p_mat_loc_firtpass = glGetUniformLocation(DR_FirstPassProgramIdId, "P");
    v_mat_loc_firtpass = glGetUniformLocation(DR_FirstPassProgramIdId, "V");
    m_mat_loc_firtpass = glGetUniformLocation(DR_FirstPassProgramIdId, "M");
    vm_mat_loc_firtpass = glGetUniformLocation(DR_FirstPassProgramIdId, "VM");

    glUniform1i(glGetUniformLocation(DR_FirstPassProgramIdId, "sampler1"), 0);


    ErrorCheckValue = glGetError();
    if (ErrorCheckValue != GL_NO_ERROR)
    {
        debugMessage("ERROR: after Shader: " + QString((char*) gluErrorString(ErrorCheckValue)));
        //exit(EXIT_FAILURE);
        return false;
    }
    //first pass end
    ////////////////////////////////////////////////////////////////////////////////////////////



    ///////////////////////////////////////////////////////////////////////////
    //SECOND SHADER

    //vertex shader
    Shader dr_vertex_secondpass(QApplication::applicationDirPath() +
                               "/shaders/deferred_renderer_second_pass.vsh",
                               GL_VERTEX_SHADER);
    if(dr_vertex_secondpass.isCreated()){
        DR_SecondPassVertexShaderId = dr_vertex_secondpass.getShaderId();
        debugMessage("Deferred Renderer second pass vertex shader compiled successful.");
    }
    else{
        debugMessage("Deferred Renderer second pass vertex shader compiled failed!");
        debugMessage(dr_vertex_secondpass.getError());
        return false;
    }


    //fragment shader
    Shader dr_fragment_secondpass(QApplication::applicationDirPath() +
                               "/shaders/deferred_renderer_second_pass.fsh",
                               GL_FRAGMENT_SHADER);
    if(dr_fragment_secondpass.isCreated()){
        DR_SecondPassFragmentShaderId = dr_fragment_secondpass.getShaderId();
        debugMessage("Deferred Renderer second pass fragment shader compiled successful.");
    }
    else{
        debugMessage("Deferred Renderer second pass fragment shader compiled failed!");
        debugMessage(dr_fragment_secondpass.getError());
        return false;
    }





    //create program, link it and bind locs
    DR_SecondPassProgramIdId = glCreateProgram();
    glAttachShader(DR_SecondPassProgramIdId, DR_SecondPassVertexShaderId);
    glAttachShader(DR_SecondPassProgramIdId, DR_SecondPassFragmentShaderId);

    // Bind the custom vertex attributes
    glBindAttribLocation(DR_SecondPassProgramIdId, 0, "vp");


    glLinkProgram(DR_SecondPassProgramIdId);

    //GLint linked;
    glGetProgramiv(DR_SecondPassProgramIdId, GL_LINK_STATUS, &linked);
    if (linked){
        debugMessage("deferred renderer program pass two linked");
    }
    else{
        debugMessage("deferred renderer program pass two linking failed!!!");
        char messages[256];
        glGetProgramInfoLog(DR_SecondPassProgramIdId, sizeof(messages), 0, &messages[0]);
        debugMessage(QString(messages));
        return false;
    }

    glUseProgram(DR_SecondPassProgramIdId);

    ErrorCheckValue = glGetError();
    if (ErrorCheckValue != GL_NO_ERROR)
    {
        debugMessage("ERROR(3): Could not create the shaders: " + QString((char*) gluErrorString(ErrorCheckValue)));
        //exit(EXIT_FAILURE);
        return false;
    }

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    p_mat_loc_secondpass = glGetUniformLocation(DR_SecondPassProgramIdId, "P");
    v_mat_loc_secondpass = glGetUniformLocation(DR_SecondPassProgramIdId, "V");
    m_mat_loc_secondpass = glGetUniformLocation(DR_SecondPassProgramIdId, "M");
    pvm_mat_loc_secondpass = glGetUniformLocation(DR_SecondPassProgramIdId, "PVM");

    lp_loc_secondpass = glGetUniformLocation(DR_SecondPassProgramIdId, "lp");
    ld_loc_secondpass = glGetUniformLocation(DR_SecondPassProgramIdId, "ld");
    ls_loc_secondpass = glGetUniformLocation(DR_SecondPassProgramIdId, "ls");

    win_size_loc_secondpass = glGetUniformLocation(DR_SecondPassProgramIdId, "win_size");


    glUniform1i(glGetUniformLocation(DR_SecondPassProgramIdId, "p_tex"), 0);
    glUniform1i(glGetUniformLocation(DR_SecondPassProgramIdId, "n_tex"), 1);
    glUniform1i(glGetUniformLocation(DR_SecondPassProgramIdId, "c_tex"), 2);
    //second pass end
    /////////////////////////////////////////////////////////////////////////////////////




    /////////////////////////////////////////////////////////////////////////////////////
    //AMBIENT LIGHT PASS


    //vertex shader
    Shader dr_vertex_ambientpass(QApplication::applicationDirPath() +
                               "/shaders/deferred_renderer_ambient_pass.vsh",
                               GL_VERTEX_SHADER);
    if(dr_vertex_ambientpass.isCreated()){
        DR_AmbientPassVertexShaderId = dr_vertex_ambientpass.getShaderId();
        debugMessage("Deferred Renderer ambient pass vertex shader compiled successful.");
    }
    else{
        debugMessage("Deferred Renderer ambient pass vertex shader compiled failed!");
        debugMessage(dr_vertex_ambientpass.getError());
        return false;
    }


    //fragment shader
    Shader dr_fragment_ambientpass(QApplication::applicationDirPath() +
                               "/shaders/deferred_renderer_ambient_pass.fsh",
                               GL_FRAGMENT_SHADER);
    if(dr_fragment_ambientpass.isCreated()){
        DR_AmbientPassFragmentShaderId = dr_fragment_ambientpass.getShaderId();
        debugMessage("Deferred Renderer ambient pass fragment shader compiled successful.");
    }
    else{
        debugMessage("Deferred Renderer ambient pass fragment shader compiled failed!");
        debugMessage(dr_fragment_ambientpass.getError());
        return false;
    }





    //create program, link it and bind locs
    DR_AmbientPassProgramIdId = glCreateProgram();
    glAttachShader(DR_AmbientPassProgramIdId, DR_AmbientPassVertexShaderId);
    glAttachShader(DR_AmbientPassProgramIdId, DR_AmbientPassFragmentShaderId);

    // Bind the custom vertex attributes
    //we have no vertices actually.... they are hardcoded in the vertex shader
    // glBindAttribLocation(DR_AmbientPassProgramIdId, 0, "vp");


    glLinkProgram(DR_AmbientPassProgramIdId);

    //GLint linked;
    glGetProgramiv(DR_AmbientPassProgramIdId, GL_LINK_STATUS, &linked);
    if (linked){
        debugMessage("deferred renderer program pass ambient linked");
    }
    else{
        debugMessage("deferred renderer program pass ambient linking failed!!!");
        char messages[256];
        glGetProgramInfoLog(DR_AmbientPassProgramIdId, sizeof(messages), 0, &messages[0]);
        debugMessage(QString(messages));
        return false;
    }

    glUseProgram(DR_AmbientPassProgramIdId);

    ErrorCheckValue = glGetError();
    if (ErrorCheckValue != GL_NO_ERROR)
    {
        debugMessage("ERROR(3): Could not create the shaders: " + QString((char*) gluErrorString(ErrorCheckValue)));
        //exit(EXIT_FAILURE);
        return false;
    }

    //no vertex attributes
    //glEnableVertexAttribArray(0);
    //glEnableVertexAttribArray(1);
    //glEnableVertexAttribArray(2);

    //no matrices needed
    /*
    p_mat_loc_secondpass = glGetUniformLocation(DR_AmbientPassProgramIdId, "P");
    v_mat_loc_secondpass = glGetUniformLocation(DR_AmbientPassProgramIdId, "V");
    m_mat_loc_secondpass = glGetUniformLocation(DR_AmbientPassProgramIdId, "M");
    pvm_mat_loc_secondpass = glGetUniformLocation(DR_AmbientPassProgramIdId, "PVM");
    */

    //dir_loc_ambientpass = glGetUniformLocation(DR_AmbientPassProgramIdId, "direction");
    color_loc_ambientpass = glGetUniformLocation(DR_AmbientPassProgramIdId, "ambient");


    win_size_loc_ambientpass = glGetUniformLocation(DR_AmbientPassProgramIdId, "win_size");


    glUniform1i(glGetUniformLocation(DR_AmbientPassProgramIdId, "p_tex"), 0);
    glUniform1i(glGetUniformLocation(DR_AmbientPassProgramIdId, "n_tex"), 1);
    glUniform1i(glGetUniformLocation(DR_AmbientPassProgramIdId, "c_tex"), 2);
    //ambient light dir pass end
    /////////////////////////////////////////////////////////////////////////////////////





    /////////////////////////////////////////////////////////////////////////////////////
    //AMBIENT DIRECTIONAL LIGHT PASS


    //vertex shader
    Shader dr_vertex_directionalambientpass(QApplication::applicationDirPath() +
                               "/shaders/deferred_renderer_directional_ambient_pass.vsh",
                               GL_VERTEX_SHADER);
    if(dr_vertex_directionalambientpass.isCreated()){
        DR_DirectionalAmbientPassVertexShaderId = dr_vertex_directionalambientpass.getShaderId();
        debugMessage("Deferred Renderer directional ambient pass vertex shader compiled successful.");
    }
    else{
        debugMessage("Deferred Renderer directional ambient pass vertex shader compiled failed!");
        debugMessage(dr_vertex_directionalambientpass.getError());
        return false;
    }


    //fragment shader
    Shader dr_fragment_directionalambientpass(QApplication::applicationDirPath() +
                               "/shaders/deferred_renderer_directional_ambient_pass.fsh",
                               GL_FRAGMENT_SHADER);
    if(dr_fragment_directionalambientpass.isCreated()){
        DR_DirectionalAmbientPassFragmentShaderId = dr_fragment_directionalambientpass.getShaderId();
        debugMessage("Deferred Renderer directional ambient pass fragment shader compiled successful.");
    }
    else{
        debugMessage("Deferred Renderer directional ambient pass fragment shader compiled failed!");
        debugMessage(dr_fragment_directionalambientpass.getError());
        return false;
    }





    //create program, link it and bind locs
    DR_DirectionalAmbientPassProgramIdId = glCreateProgram();
    glAttachShader(DR_DirectionalAmbientPassProgramIdId, DR_DirectionalAmbientPassVertexShaderId);
    glAttachShader(DR_DirectionalAmbientPassProgramIdId, DR_DirectionalAmbientPassFragmentShaderId);

    // Bind the custom vertex attributes
    //we have no vertices actually.... they are hardcoded in the vertex shader
    // glBindAttribLocation(DR_AmbientPassProgramIdId, 0, "vp");


    glLinkProgram(DR_DirectionalAmbientPassProgramIdId);

    //GLint linked;
    glGetProgramiv(DR_DirectionalAmbientPassProgramIdId, GL_LINK_STATUS, &linked);
    if (linked){
        debugMessage("deferred renderer program pass directional ambient linked");
    }
    else{
        debugMessage("deferred renderer program pass directional ambient linking failed!!!");
        char messages[256];
        glGetProgramInfoLog(DR_DirectionalAmbientPassProgramIdId, sizeof(messages), 0, &messages[0]);
        debugMessage(QString(messages));
        return false;
    }

    glUseProgram(DR_DirectionalAmbientPassProgramIdId);

    ErrorCheckValue = glGetError();
    if (ErrorCheckValue != GL_NO_ERROR)
    {
        debugMessage("ERROR(3): Could not create the shaders: " + QString((char*) gluErrorString(ErrorCheckValue)));
        //exit(EXIT_FAILURE);
        return false;
    }

    //no vertex attributes
    //glEnableVertexAttribArray(0);
    //glEnableVertexAttribArray(1);
    //glEnableVertexAttribArray(2);

    //no matrices needed
    /*
    p_mat_loc_secondpass = glGetUniformLocation(DR_AmbientPassProgramIdId, "P");
    v_mat_loc_secondpass = glGetUniformLocation(DR_AmbientPassProgramIdId, "V");
    m_mat_loc_secondpass = glGetUniformLocation(DR_AmbientPassProgramIdId, "M");
    pvm_mat_loc_secondpass = glGetUniformLocation(DR_AmbientPassProgramIdId, "PVM");
    */

    v_mat_loc_directionalambientpass = glGetUniformLocation(DR_DirectionalAmbientPassProgramIdId, "V");

    dir_loc_directionalambientpass = glGetUniformLocation(DR_DirectionalAmbientPassProgramIdId, "direction");
    color_loc_directionalambientpass = glGetUniformLocation(DR_DirectionalAmbientPassProgramIdId, "ambient");


    win_size_loc_directionalambientpass = glGetUniformLocation(DR_DirectionalAmbientPassProgramIdId, "win_size");


    glUniform1i(glGetUniformLocation(DR_DirectionalAmbientPassProgramIdId, "p_tex"), 0);
    glUniform1i(glGetUniformLocation(DR_DirectionalAmbientPassProgramIdId, "n_tex"), 1);
    glUniform1i(glGetUniformLocation(DR_DirectionalAmbientPassProgramIdId, "c_tex"), 2);
    //ambient light dir pass end
    /////////////////////////////////////////////////////////////////////////////////////










    /////////////////////////////////////////////////////////////////////////////////////
    //DEBUG PASS


    //vertex shader
    Shader dr_vertex_debugpass(QApplication::applicationDirPath() +
                               "/shaders/deferred_renderer_debug_pass.vsh",
                               GL_VERTEX_SHADER);
    if(dr_vertex_debugpass.isCreated()){
        DR_DebugPassVertexShaderId = dr_vertex_debugpass.getShaderId();
        debugMessage("Deferred Renderer debug pass vertex shader compiled successful.");
    }
    else{
        debugMessage("Deferred Renderer debug pass vertex shader compiled failed!");
        debugMessage(dr_vertex_debugpass.getError());
        return false;
    }


    //fragment shader
    Shader dr_fragment_debugpass(QApplication::applicationDirPath() +
                               "/shaders/deferred_renderer_debug_pass.fsh",
                               GL_FRAGMENT_SHADER);
    if(dr_fragment_debugpass.isCreated()){
        DR_DebugPassFragmentShaderId = dr_fragment_debugpass.getShaderId();
        debugMessage("Deferred Renderer debug pass fragment shader compiled successful.");
    }
    else{
        debugMessage("Deferred Renderer debug pass fragment shader compiled failed!");
        debugMessage(dr_fragment_debugpass.getError());
        return false;
    }





    //create program, link it and bind locs
    DR_DebugPassProgramIdId = glCreateProgram();
    glAttachShader(DR_DebugPassProgramIdId, DR_DebugPassVertexShaderId);
    glAttachShader(DR_DebugPassProgramIdId, DR_DebugPassFragmentShaderId);

    // Bind the custom vertex attributes
    //we have no vertices actually.... they are hardcoded in the vertex shader
    glBindAttribLocation(DR_DebugPassProgramIdId, 0, "vp");


    glLinkProgram(DR_DebugPassProgramIdId);

    //GLint linked;
    glGetProgramiv(DR_DebugPassProgramIdId, GL_LINK_STATUS, &linked);
    if (linked){
        debugMessage("deferred renderer program pass debug linked");
    }
    else{
        debugMessage("deferred renderer program pass debug linking failed!!!");
        char messages[256];
        glGetProgramInfoLog(DR_DebugPassProgramIdId, sizeof(messages), 0, &messages[0]);
        debugMessage(QString(messages));
        return false;
    }

    glUseProgram(DR_DebugPassProgramIdId);

    ErrorCheckValue = glGetError();
    if (ErrorCheckValue != GL_NO_ERROR)
    {
        debugMessage("ERROR(3): Could not create the shaders: " + QString((char*) gluErrorString(ErrorCheckValue)));
        //exit(EXIT_FAILURE);
        return false;
    }

    //no vertex attributes
    glEnableVertexAttribArray(0);



    pvm_mat_loc_debugpass = glGetUniformLocation(DR_DebugPassProgramIdId, "PVM");

    color_loc_debugpass = glGetUniformLocation(DR_DebugPassProgramIdId, "color");


    //DEBUG pass end
    /////////////////////////////////////////////////////////////////////////////////////










    //TEST FOR ERRORS

    ErrorCheckValue = glGetError();
    if (ErrorCheckValue != GL_NO_ERROR)
    {
        debugMessage("ERROR: after Shader: " + QString((char*) gluErrorString(ErrorCheckValue)));
        //exit(EXIT_FAILURE);
        return false;
    }

    glEnable(GL_DEPTH_TEST);
    //glDepthMask(GL_TRUE);
    return true;
}


bool Renderer::createBuffers(){
    debugMessage("creating buffers...");
    ///////////////////////////////////////////////////////////////////////////////////
    //gen framebuffers
    //

    fb = 0;
    glGenFramebuffers (1, &fb);
    glBindFramebuffer (GL_FRAMEBUFFER, fb);
    //position texture
    glGenTextures (1, &fb_tex_p);
    glBindTexture (GL_TEXTURE_2D, fb_tex_p);
    glTexImage2D (
      GL_TEXTURE_2D,
      0,
      GL_RGB16F,
      600,
      400,
      0,
      GL_BGR,
      GL_UNSIGNED_BYTE,
      NULL
    );
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


    //normal texture
    glGenTextures (1, &fb_tex_n);
    glBindTexture (GL_TEXTURE_2D, fb_tex_n);
    glTexImage2D (
      GL_TEXTURE_2D,
      0,
      GL_RGB16F,
      600,
      400,
      0,
      GL_BGR,
      GL_UNSIGNED_BYTE,
      NULL
    );
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


    //color texture
    glGenTextures (1, &fb_tex_c);
    glBindTexture (GL_TEXTURE_2D, fb_tex_c);
    glTexImage2D (
                GL_TEXTURE_2D,
                0,
                GL_RGB16F,
                600,
                400,
                0,
                GL_BGR,
                GL_UNSIGNED_BYTE,
                NULL
                );
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


    glFramebufferTexture2D (
      GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fb_tex_p, 0
    );
    glFramebufferTexture2D (
      GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, fb_tex_n, 0
    );
    glFramebufferTexture2D (
      GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, fb_tex_c, 0
    );


    rb = 0;
    glGenRenderbuffers (1, &rb);
    glBindRenderbuffer (GL_RENDERBUFFER, rb);
    glRenderbufferStorage (
      GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 600, 400
    );
    glFramebufferRenderbuffer (
      GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rb
    );

    GLenum draw_bufs[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
    glDrawBuffers (3, draw_bufs);





    // Always check that our framebuffer is ok
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
        debugMessage("framebuffer error!");
        return false;
    }
    debugMessage("created buffers.");
    return true;
}

void Renderer::destroyShaders(){
    debugMessage("destroying shaders...");
    GLenum ErrorCheckValue = glGetError();

    glUseProgram(0);

    glDetachShader(ProgramId, VertexShaderId);
    glDetachShader(ProgramId, FragmentShaderId);

    glDeleteShader(FragmentShaderId);
    glDeleteShader(VertexShaderId);

    glDeleteProgram(ProgramId);

    ErrorCheckValue = glGetError();
    if (ErrorCheckValue != GL_NO_ERROR)
    {
        debugMessage("ERROR(4): Could not destroy the shaders: "  + QString((char*) gluErrorString(ErrorCheckValue)));
        //exit(EXIT_FAILURE);
        return;
    }
}

/*
void Renderer::createVBO(){
    Vertex Vertices[] =
    {
        { { -0.8f, -0.8f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
        { {  0.0f,  0.8f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
        { {  0.8f, -0.8f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } }
    };

    GLenum ErrorCheckValue = glGetError();
    const size_t BufferSize = sizeof(Vertices);
    const size_t VertexSize = sizeof(Vertices[0]);
    const size_t RgbOffset = sizeof(Vertices[0].XYZW);


    glGenVertexArrays(1, &VaoId);
    glBindVertexArray(VaoId);


    glGenBuffers(1, &VboId);
    glBindBuffer(GL_ARRAY_BUFFER, VboId);
    glBufferData(GL_ARRAY_BUFFER, BufferSize, Vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, VertexSize, 0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, VertexSize, (GLvoid*)RgbOffset);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    ErrorCheckValue = glGetError();
    if (ErrorCheckValue != GL_NO_ERROR)
    {
        debugMessage("ERROR(5): Could not create a VBO: " + QString((char*) gluErrorString(ErrorCheckValue)));
        exit(EXIT_FAILURE);
    }

}

void Renderer::destroyVBO(){
    GLenum ErrorCheckValue = glGetError();

    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &VboId);

    glBindVertexArray(0);
    glDeleteVertexArrays(1, &VaoId);

    ErrorCheckValue = glGetError();
    if (ErrorCheckValue != GL_NO_ERROR)
    {
        debugMessage("ERROR(6): Could not destroy the VBO: " + QString((char*) gluErrorString(ErrorCheckValue)));
        exit(EXIT_FAILURE);
    }
}
*/

void Renderer::resizeBuffers(int x, int y){
    debugMessage("buffer resize");
    if(shadersAndBuffersCreated){
        //position texture
        glBindTexture (GL_TEXTURE_2D, fb_tex_p);
        glTexImage2D (
          GL_TEXTURE_2D,
          0,
          GL_RGB16F,
          x,
          y,
          0,
          GL_BGR,
          GL_UNSIGNED_BYTE,
          NULL
        );
        glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


        //normal texture
        glBindTexture (GL_TEXTURE_2D, fb_tex_n);
        glTexImage2D (
          GL_TEXTURE_2D,
          0,
          GL_RGB16F,
          x,
          y,
          0,
          GL_BGR,
          GL_UNSIGNED_BYTE,
          NULL
        );
        glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


        //color texture
        glBindTexture (GL_TEXTURE_2D, fb_tex_c);
        glTexImage2D (
                    GL_TEXTURE_2D,
                    0,
                    GL_RGB16F,
                    x,
                    y,
                    0,
                    GL_BGR,
                    GL_UNSIGNED_BYTE,
                    NULL
                    );
        glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


        glBindRenderbuffer (GL_RENDERBUFFER, rb);
        glRenderbufferStorage (
          GL_RENDERBUFFER, GL_DEPTH_COMPONENT, x, y
        );
        glFramebufferRenderbuffer (
          GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rb
        );
    }
}

//EVENT LISTENER
//do not invoke the parents method...
void Renderer::eventRecieved(Event e){
    if(e.type == Event::EventWindowResize){
        resizeBuffers(e.window->getSizeX(),e.window->getSizeY());
    }
}

void Renderer::debugMessage(QString message){
    Event e;
    e.type = Event::EventDebuggerMessage;
    e.debugger = new EventDebugger(message);
    this->transmit(e);
}

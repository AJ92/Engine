#include "renderer.h"
#include "Graphics/Model/model.h"
#include "Graphics/Model/Components/material.h"
#include "Graphics/Model/Components/mesh.h"
#include "Graphics/Model/Components/texturemap.h"
#include "Graphics/Model/Components/texturemapcube.h"
#include "Graphics/Model/light.h"

#include "Event/event.h"

#include "Object/positation.h"
#include "Object/compositeobject.h"
#include "Graphics/World/objectworld.h"

#include <QApplication>

Renderer::Renderer() :
    EventTransmitter()
{
    shadersAndBuffersCreated = false;
    firstTextureIndex = 2;
    secondTextureIndex = 4;
    thirdTextureIndex = 8;
    fourthTextureIndex = 16;

    objectworld = SP<ObjectWorld>();

    meshPerFrameCount = 0;
    trianglesPerFrameCount = 0;
    texBindsPerFrameCount = 0;
    frame_switch = 1;

    postProcessingMode =
            PostProcessingModeFXAA | PostProcessingModeSharpen |
            PostProcessingModeSSAO;

}

void Renderer::initialize(){
    debugMessage("initialising renderer ...");

    //enable color corrected output buffer
    glEnable(GL_FRAMEBUFFER_SRGB);

    //default render mode
    renderMode = PolygonModeStandard;

    createFullScreenQuad();
    createSkyBox();

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


void Renderer::setObjectWorld(SP<ObjectWorld> objectworld){
    this->objectworld = objectworld;
}

void Renderer::setCamera(SP<Camera> cam){
    this->cam = cam;
}

void Renderer::setWindow(SP<Window> win){
    this->win = win;
    this->win->addListener(this);
}

bool Renderer::meshInFrustum(SP<Frustum> f, SP<Model> mdl, SP<Mesh> mesh, Matrix4x4 &pvm_mat){
    //get the spherical bounds

    SP<Positation> posi = mdl->getParentCompositeObject()->getPositation();

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

    int type = f->sphereInFrustum(mdl_pos,max_rad);

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

        SP<Frustum> frustum(new Frustum());
        //setting up the clipping points/planes...
        frustum->setPoints(cam->getPosition() - touch_to_space(0,0)*near_,
                          cam->getPosition() - touch_to_space(win->getWindowWidth(),0)*near_,
                          cam->getPosition() - touch_to_space(0,win->getWindowHeight())*near_,
                          cam->getPosition() - touch_to_space(win->getWindowWidth(),win->getWindowHeight())*near_,
                          cam->getPosition() - touch_to_space(0,0)*far_,
                          cam->getPosition() - touch_to_space(win->getWindowWidth(),0)*far_,
                          cam->getPosition() - touch_to_space(0,win->getWindowHeight())*far_,
                          cam->getPosition() - touch_to_space(win->getWindowWidth(),win->getWindowHeight())*far_);



        //setup the octtree stuff so we cen loop trough the octtree nodes...
        SP<OctTree> ot = objectworld->getOctTree();
        SP<OctTreeFast> ot_dynamic_models = objectworld->getOctTreeFastDynamicModels();
        SP<OctTreeFast> ot_dynamic_lights = objectworld->getOctTreeFastDynamicLights();


        QList<SP<OctTree> > ot_nodes = ot->getNodesInFrustum(frustum);
        QList<SP<OctTreeFast> > ot_dynamic_models_nodes = ot_dynamic_models->getNodesInFrustum(frustum);
        QList<SP<OctTreeFast> > ot_dynamic_lights_nodes = ot_dynamic_lights->getNodesInFrustum(frustum);

        //debugMessage("Nodes: " + QString::number(ot_nodes.size()));

        //we have the octTree nodes which are in the frustum...
        //lets loop trough them and render the models inside of each node...

        ////////////////////////////////////////////////////////////////////////////////////
        // visual render mode (solid objects)


        if((renderMode & PolygonModeStandard) == PolygonModeStandard){
            ////////////////////////////////////////////////////////////////////////////////////
            // FIRST PASS of DEFERED RENDERER... fill the buffers

            //set up framebuffer and renderbuffer


            //bind renderbuffer
            glBindRenderbuffer (GL_RENDERBUFFER, rb1);

            // bind framebuffer
            glBindFramebuffer(GL_FRAMEBUFFER, fbo_1);
            //glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
            glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);




            glUseProgram(DR_FirstPassProgramIdId);

            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


            //STATIC MODELS
            for(int i = 0; i < ot_nodes.size(); i++){
                //render one node...

                //copy the lists so we can itterate through them
                QList<QList<SP<CompositeObject> > > compositeobject_mesh_list = ot_nodes[i]->getModelLibrary()->getCompositeobjectMeshList();
                QList<QList<SP<Mesh> > > mesh_model_list = ot_nodes[i]->getModelLibrary()->getMeshModelList();
                QList<QList<SP<Model> > > model_mesh_list = ot_nodes[i]->getModelLibrary()->getModelMeshList();
                QList<SP<Material> > material_mesh_list = ot_nodes[i]->getModelLibrary()->getMaterialMeshList();

                //loop trough the material_mesh_list
                for(int index = 0; index < material_mesh_list.size(); index++){

                    //check if material was loaded...
                    if(material_mesh_list[index]->isLoaded()){
                        //now set up the material and mesh

                        //tex
                        glActiveTexture (GL_TEXTURE0+firstTextureIndex);
                        SP<TextureMap> texmap = material_mesh_list[index]->getTextureMap(Material::Diffuse);
                        glBindTexture(GL_TEXTURE_2D, texmap->getGLTextureMap());
                        glUniform1i(glGetUniformLocation(DR_FirstPassProgramIdId, "sampler1"), firstTextureIndex);

                        texBindsPerFrameCount += 1;

                        //tex
                        glActiveTexture (GL_TEXTURE0+secondTextureIndex);
                        SP<TextureMap> bump = material_mesh_list[index]->getTextureMap(Material::Bump);
                        glBindTexture(GL_TEXTURE_2D, bump->getGLTextureMap());
                        glUniform1i(glGetUniformLocation(DR_FirstPassProgramIdId, "sampler2"), secondTextureIndex);

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
                            SP<Mesh> mesh = mesh_model_list[index].at(0);

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

                            glBindBuffer(GL_ARRAY_BUFFER, mesh->get_tangent_vbo());
                            glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0);
                            glEnableVertexAttribArray(3);

                            glBindBuffer(GL_ARRAY_BUFFER, mesh->get_bitangent_vbo());
                            glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, 0);
                            glEnableVertexAttribArray(4);

                            //now lets draw for every model it's meshs

                            //draw
                            int rendered = 0;
                            for(int mdl_index = 0; mdl_index < model_mesh_list[index].size(); mdl_index++){

                                //calculate if we need to draw the model
                                SP<Model> mdl =  model_mesh_list[index].at(mdl_index);

                                if(!mdl->isReadyToRender()){
                                    qDebug("mdl not ready to render...");
                                }

                                SP<Positation> posi = compositeobject_mesh_list[index][mdl_index]->getPositation();

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




                                glUniformMatrix4fv(p_mat_loc_firstpass, 1, GL_FALSE, p_mat);
                                glUniformMatrix4fv(v_mat_loc_firstpass, 1, GL_FALSE, v_mat);
                                glUniformMatrix4fv(m_mat_loc_firstpass, 1, GL_FALSE, m_mat);
                                glUniformMatrix4fv(vm_mat_loc_firstpass, 1, GL_FALSE, vm_mat);




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
                QList<SP<CompositeObject> > compositeobject_list = ot_dynamic_models_nodes[i]->getCompositeObjects();

                //loop trough the material_mesh_list
                for(int index = 0; index < compositeobject_list.size(); index++){

                    SP<CompositeObject> compobj = compositeobject_list.at(index);
                    SP<Positation> posi = compobj->getPositation();
                    QList<SP<Mesh> > mesh_list = compobj->getModel()->get_meshs();

                    //loop trough mesh...
                    for(int meshs = 0; meshs < mesh_list.size(); meshs++){

                        SP<Mesh> mesh = mesh_list[meshs];

                        //now set up the material and mesh

                        //tex
                        glActiveTexture (GL_TEXTURE0+firstTextureIndex);              
                        SP<TextureMap> texmap = mesh->get_material()->getTextureMap(Material::Diffuse);
                        glBindTexture(GL_TEXTURE_2D, texmap->getGLTextureMap());
                        glUniform1i(glGetUniformLocation(DR_FirstPassProgramIdId, "sampler1"), firstTextureIndex);

                        texBindsPerFrameCount += 1;

                        //tex
                        glActiveTexture (GL_TEXTURE0+secondTextureIndex);
                        SP<TextureMap> bump = mesh->get_material()->getTextureMap(Material::Bump);
                        glBindTexture(GL_TEXTURE_2D, bump->getGLTextureMap());
                        glUniform1i(glGetUniformLocation(DR_FirstPassProgramIdId, "sampler2"), secondTextureIndex);

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




                        glUniformMatrix4fv(p_mat_loc_firstpass, 1, GL_FALSE, p_mat);
                        glUniformMatrix4fv(v_mat_loc_firstpass, 1, GL_FALSE, v_mat);
                        glUniformMatrix4fv(m_mat_loc_firstpass, 1, GL_FALSE, m_mat);
                        glUniformMatrix4fv(vm_mat_loc_firstpass, 1, GL_FALSE, vm_mat);



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

            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, 0);


            ////////////////////////////////////////////////////////////////////////////////////
            // SECOND PASS of DEFERED RENDERER... take the filled buffers and ...
            // add some sexyness to them :P


            glBindFramebuffer (GL_FRAMEBUFFER, fbo_2);
            glDrawBuffer(GL_BACK);
            glClearColor (0.0, 0.0, 0.0, 1.0f); // no ambient... we add it later...
            glClear (GL_COLOR_BUFFER_BIT);

            glEnable (GL_BLEND); // --- could reject background frags!
            glBlendEquation (GL_FUNC_ADD);
            glBlendFunc (GL_ONE, GL_ONE); // addition each time


            glDisable (GL_DEPTH_TEST);
            glDepthMask (GL_FALSE);

            glActiveTexture (GL_TEXTURE0);
            glBindTexture (GL_TEXTURE_2D, fbo_1_tex_p);

            glActiveTexture (GL_TEXTURE1);
            glBindTexture (GL_TEXTURE_2D, fbo_1_tex_n);

            glActiveTexture (GL_TEXTURE2);
            glBindTexture (GL_TEXTURE_2D, fbo_1_tex_c);

            glUseProgram (DR_SecondPassProgramIdId);

            glPolygonMode(GL_FRONT, GL_FILL);

            glUniform2f (win_size_loc_secondpass, win->getWindowWidth(), win->getWindowHeight());



            //DYNAMIC lights
            for(int i = 0; i < ot_dynamic_lights_nodes.size(); i++){
                //render one node...

                //copy the lists so we can itterate through them
                QList<SP<CompositeObject> > compositeobject_list = ot_dynamic_lights_nodes[i]->getCompositeObjects();

                //loop trough the material_mesh_list
                for(int index = 0; index < compositeobject_list.size(); index++){

                    SP<CompositeObject> compobj = compositeobject_list.at(index);
                    SP<Positation> posi = compobj->getPositation();
                    QList<SP<Mesh> > mesh_list = compobj->getModel()->get_meshs();
                    SP<Light> light = compobj->getLight();

                    //loop trough mesh...
                    for(int meshs = 0; meshs < mesh_list.size(); meshs++){

                        SP<Mesh> mesh = mesh_list[meshs];

                        //now set up the material and mesh

                        // LIGHT HAS NO TEXTURE
                        //tex
                        /*
                        glActiveTexture (GL_TEXTURE0+firstTextureIndex);
                        glBindTexture(GL_TEXTURE_2D, mesh->get_material()->get_diffuse_map_texture());
                        glUniform1i(glGetUniformLocation(DR_FirstPassProgramIdId, "sampler1"), firstTextureIndex);

                        texBindsPerFrameCount += 1;
                        */


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



                        //Indizes
                        //|    0        4        8        12   |
                        //|                                    |
                        //|    1        5        9        13   |
                        //|                                    |
                        //|    2        6        10       14   |
                        //|                                    |
                        //|    3        7        11       15   |


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
                        meshPerFrameCount +=1;
                        trianglesPerFrameCount += mesh->get_triangle_count();
                    }
                }
            }
        }

        //end of PolygonModeStandard




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
                     0.0240,
                     0.0240,
                     0.0238); // ambient color

        //glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glDrawArrays(GL_TRIANGLES, 0, fsq_triangle_count*3);







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

        glUniform3f (dir_loc_directionalambientpass,
                      1.0,
                      0.1,
                      0.1); // ambient light direction

        glUniform3f (color_loc_directionalambientpass,
                     0.6,//0.330,
                     0.55,//0.310,
                     0.5//0.350
                     ); // ambient color


        for (int f = 0; f < 4; f++) {
            for (int g = 0; g < 4; g++) {
                v_mat[f * 4 + g] = (GLfloat) (v_m[f*4+g]);
            }
        }


        glUniformMatrix4fv(v_mat_loc_directionalambientpass, 1, GL_FALSE, v_mat);

        //glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glDrawArrays(GL_TRIANGLES, 0, fsq_triangle_count*3);


        //
        // DRAWING FINISHED
        //////////////////////////////////////////////////////////////////////////////////////////





        ///////////////////////////////////////////////////////////////////////////////
        //SKYBOX
        //

        glBindFramebuffer(GL_FRAMEBUFFER, fbo_3);
        //glDrawBuffer(GL_BACK);

        glDisable (GL_BLEND);

        //glClearColor(0,0,0,0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(DR_SkyBoxPassProgramIdId);

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glDepthMask (GL_FALSE);

        glActiveTexture (GL_TEXTURE0+firstTextureIndex);
        glBindTexture(GL_TEXTURE_CUBE_MAP, sb_texmap->getGLTextureMap());
        glUniform1i(glGetUniformLocation(DR_SkyBoxPassProgramIdId, "sampler1"), firstTextureIndex);

        glBindVertexArray(sb_vertex_array_object);

        //VBOs
        glBindBuffer(GL_ARRAY_BUFFER, sb_vertex_vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);

        //TODO: improve this crap....
        Matrix4x4 trans;
        trans.scale(214.0,214.0,214.0);
        trans.translate(cam->getPosition());

        vm_m = v_m * trans;

        //TRANSPOSE
        for (int f = 0; f < 4; f++) {
            for (int g = 0; g < 4; g++) {
                p_mat[f * 4 + g] = (GLfloat) (p_m[f*4+g]);
                v_mat[f * 4 + g] = (GLfloat) (v_m[f*4+g]);
                m_mat[f * 4 + g] = (GLfloat) (trans[f*4+g]);
                vm_mat[f * 4 + g] = (GLfloat) (vm_m[f*4+g]);
            }
        }

        glUniformMatrix4fv(p_mat_loc_skyboxpass, 1, GL_FALSE, p_mat);
        glUniformMatrix4fv(v_mat_loc_skyboxpass, 1, GL_FALSE, v_mat);
        glUniformMatrix4fv(m_mat_loc_skyboxpass, 1, GL_FALSE, m_mat);
        glUniformMatrix4fv(vm_mat_loc_skyboxpass, 1, GL_FALSE, vm_mat);

        //draw
        glDrawArrays(GL_TRIANGLES, 0, sb_triangle_count*3);
        meshPerFrameCount +=1;
        trianglesPerFrameCount += sb_triangle_count;
        texBindsPerFrameCount += 1;
        glDepthMask (GL_TRUE);
        //SKYBOX END
        ///////////////////////////////////////////////////////////////////////////////









        /////////////////////////////////////////////////////////////////////////////////
        ///
        /// BUFFERCOPY PASS (copy the lit framebuffer onto the skybox)
        ///
        ///

        glBindVertexArray(fsq_vertex_array_object);

        //VBOs
        glBindBuffer(GL_ARRAY_BUFFER, fsq_vertex_vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);

        //tex coords actually not needed!!!
        /*
        glBindBuffer(GL_ARRAY_BUFFER, fsq_texcoord_vbo);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(1);
        */

        //normal not needed...
        /*
        glBindBuffer(GL_ARRAY_BUFFER, fsq_normal_vbo);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(2);
        */


        glActiveTexture (GL_TEXTURE0);
        glBindTexture (GL_TEXTURE_2D, fbo_1_tex_p);

        //previously the normal was on tex1 and color on tex2...
        glActiveTexture (GL_TEXTURE1);
        glBindTexture (GL_TEXTURE_2D, fbo_2_tex_c);



        glUseProgram (DR_BufferCopyPassProgramIdId);

        glPolygonMode(GL_FRONT_AND_BACK, GL_POLYGON);

        glUniform2f (win_size_loc_buffercopypass, win->getWindowWidth(), win->getWindowHeight());

        //glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glDrawArrays(GL_TRIANGLES, 0, fsq_triangle_count*3);




//////////////////////////////////////////////////////////////////////////////////////////
//POST PROCESSING EFFECTS and FILTERS

        //used to swap around buffers for post processing stuff...
        GLuint input_frame = fbo_3_tex_c;
        GLuint output_frame = fbo_2;
        GLuint temp_swap;


        glDisable (GL_BLEND);
        glBindVertexArray(fsq_vertex_array_object);
        //VBOs
        //glBindBuffer(GL_ARRAY_BUFFER, fsq_vertex_vbo);
        //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        //glEnableVertexAttribArray(0);
        glUseProgram (DR_EdgeDetectionPassProgramIdId);
        glPolygonMode(GL_FRONT_AND_BACK, GL_POLYGON);
        glUniform2f (win_size_loc_edgedetectionpass, win->getWindowWidth(), win->getWindowHeight());
        glUniform1i (frame_switch_loc_edgedetectionpass, frame_switch);


        ////////////////////////////////////////////////////////////
        //  POST PROCESSING SSAO first
        //      use fbo_3_tex_c as input   fbo_2 as output

        if((postProcessingMode & PostProcessingModeSSAO) == PostProcessingModeSSAO){
            glBindFramebuffer(GL_FRAMEBUFFER, output_frame);
            //glDrawBuffer(GL_BACK);

            //switch texture slot... color to 0
            glActiveTexture (GL_TEXTURE0);
            glBindTexture (GL_TEXTURE_2D, input_frame); //color from light pass

            glActiveTexture (GL_TEXTURE1);
            glBindTexture (GL_TEXTURE_2D, fbo_1_tex_d); //depth from first pass

            glActiveTexture (GL_TEXTURE2);
            glBindTexture (GL_TEXTURE_2D, fbo_1_tex_n); //normal from first pass

            glActiveTexture (GL_TEXTURE3);
            glBindTexture (GL_TEXTURE_2D, fbo_1_tex_p); //normal from first pass

            glBindVertexArray(fsq_vertex_array_object);

            //VBOs
            //glBindBuffer(GL_ARRAY_BUFFER, fsq_vertex_vbo);
            //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
            //glEnableVertexAttribArray(0);


            glUseProgram (DR_EdgeDetectionPassProgramIdId);

            glPolygonMode(GL_FRONT_AND_BACK, GL_POLYGON);

            glUniform2f (win_size_loc_edgedetectionpass, win->getWindowWidth(), win->getWindowHeight());
            glUniform1i (frame_switch_loc_edgedetectionpass, frame_switch);
            glUniform1i (function_loc_edgedetectionpass, 8); //7 is fastSSAO  8 is quality SSAO

            glDrawArrays(GL_TRIANGLES, 0, fsq_triangle_count*3);

            //
            ////////////////////////////////////////////////////////////

            //swap
            //input_frame = fbo_3_tex_c;
            //output_frame = fbo_2;

            //input_frame = fbo_2_tex_c;
            //output_frame = fbo_3;

            if(input_frame == fbo_3_tex_c){
                input_frame = fbo_2_tex_c;
                output_frame = fbo_3;
            }
            else{
                input_frame = fbo_3_tex_c;
                output_frame = fbo_2;
            }



        }




        ////////////////////////////////////////////////////////////
        //  POST PROCESSING fxaa first
        //      use fbo_2_tex_c as input   fbo_3 as output

        if((postProcessingMode & PostProcessingModeFXAA) == PostProcessingModeFXAA){

            //bind framebuffer so we can draw to the edge texture....
            //glBindFramebuffer(GL_FRAMEBUFFER, fb);


            glBindFramebuffer(GL_FRAMEBUFFER, output_frame);
            //glDrawBuffer(GL_BACK);

            //switch texture slot... color to 0
            glActiveTexture (GL_TEXTURE0);
            glBindTexture (GL_TEXTURE_2D, input_frame);

            //glActiveTexture (GL_TEXTURE1);
            //glBindTexture (GL_TEXTURE_2D, fbo_1_tex_p);

            //glBindVertexArray(fsq_vertex_array_object);

            //VBOs
            //glBindBuffer(GL_ARRAY_BUFFER, fsq_vertex_vbo);
            //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
            //glEnableVertexAttribArray(0);


            //glUseProgram (DR_EdgeDetectionPassProgramIdId);

            //glPolygonMode(GL_FRONT_AND_BACK, GL_POLYGON);

            glUniform2f (win_size_loc_edgedetectionpass, win->getWindowWidth(), win->getWindowHeight());
            glUniform1i (frame_switch_loc_edgedetectionpass, frame_switch);
            glUniform1i (function_loc_edgedetectionpass, 0);

            glDrawArrays(GL_TRIANGLES, 0, fsq_triangle_count*3);

            //
            ////////////////////////////////////////////////////////////

            //swap
            //input_frame = fbo_3_tex_c;
            //output_frame = fbo_2;

            //input_frame = fbo_2_tex_c;
            //output_frame = fbo_3;

            if(input_frame == fbo_3_tex_c){
                input_frame = fbo_2_tex_c;
                output_frame = fbo_3;
            }
            else{
                input_frame = fbo_3_tex_c;
                output_frame = fbo_2;
            }

        }



        ////////////////////////////////////////////////////////////
        //  POST PROCESSING sharpening third
        if((postProcessingMode & PostProcessingModeSharpen) == PostProcessingModeSharpen){

            //glDisable (GL_BLEND);

            //bind framebuffer so we can draw to the edge texture....
            //glBindFramebuffer(GL_FRAMEBUFFER, fb);


            glBindFramebuffer(GL_FRAMEBUFFER, output_frame);
            glDrawBuffer(GL_BACK);

            //switch texture slot... color to 0
            glActiveTexture (GL_TEXTURE0);
            glBindTexture (GL_TEXTURE_2D, input_frame);

            //glActiveTexture (GL_TEXTURE1);
            //glBindTexture (GL_TEXTURE_2D, fbo_1_tex_p);

            //glBindVertexArray(fsq_vertex_array_object);

            //VBOs
            //glBindBuffer(GL_ARRAY_BUFFER, fsq_vertex_vbo);
            //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
            //glEnableVertexAttribArray(0);


            //glUseProgram (DR_EdgeDetectionPassProgramIdId);

            //glPolygonMode(GL_FRONT_AND_BACK, GL_POLYGON);

            //glUniform2f (win_size_loc_edgedetectionpass, win->getWindowWidth(), win->getWindowHeight());
            //glUniform1i (frame_switch_loc_edgedetectionpass, frame_switch);
            glUniform1i (function_loc_edgedetectionpass, 2);

            glDrawArrays(GL_TRIANGLES, 0, fsq_triangle_count*3);

            //
            ////////////////////////////////////////////////////////////

            //swap
            //input_frame = fbo_3_tex_c;
            //output_frame = fbo_2;

            //input_frame = fbo_2_tex_c;
            //output_frame = fbo_3;

            if(input_frame == fbo_3_tex_c){
                input_frame = fbo_2_tex_c;
                output_frame = fbo_3;
            }
            else{
                input_frame = fbo_3_tex_c;
                output_frame = fbo_2;
            }

        }






        ////////////////////////////////////////////////////////////
        //  POST PROCESSING h blur fourth
        //      use fbo_2_tex_c as input   fbo_3 as output
        if((postProcessingMode & PostProcessingModeBlurH) == PostProcessingModeBlurH){

            //glDisable (GL_BLEND);

            //bind framebuffer so we can draw to the edge texture....
            //glBindFramebuffer(GL_FRAMEBUFFER, fb);


            glBindFramebuffer(GL_FRAMEBUFFER, output_frame);
            //glDrawBuffer(GL_BACK);

            //switch texture slot... color to 0
            glActiveTexture (GL_TEXTURE0);
            glBindTexture (GL_TEXTURE_2D, input_frame);


            //glBindVertexArray(fsq_vertex_array_object);

            //VBOs
            //glBindBuffer(GL_ARRAY_BUFFER, fsq_vertex_vbo);
            //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
            //glEnableVertexAttribArray(0);


            //glUseProgram (DR_EdgeDetectionPassProgramIdId);

            //glPolygonMode(GL_FRONT_AND_BACK, GL_POLYGON);

            //glUniform2f (win_size_loc_edgedetectionpass, win->getWindowWidth(), win->getWindowHeight());
            //glUniform1i (frame_switch_loc_edgedetectionpass, frame_switch);
            glUniform1i (function_loc_edgedetectionpass, 3);

            glDrawArrays(GL_TRIANGLES, 0, fsq_triangle_count*3);

            //
            ////////////////////////////////////////////////////////////

            //swap
            //input_frame = fbo_3_tex_c;
            //output_frame = fbo_2;

            //input_frame = fbo_2_tex_c;
            //output_frame = fbo_3;

            if(input_frame == fbo_3_tex_c){
                input_frame = fbo_2_tex_c;
                output_frame = fbo_3;
            }
            else{
                input_frame = fbo_3_tex_c;
                output_frame = fbo_2;
            }

        }



        ////////////////////////////////////////////////////////////
        //  POST PROCESSING v blur fourth
        //      use fbo_3_tex_c as input   fbo_2 as output
        if((postProcessingMode & PostProcessingModeBlurV) == PostProcessingModeBlurV){

            //glDisable (GL_BLEND);

            //bind framebuffer so we can draw to the edge texture....
            //glBindFramebuffer(GL_FRAMEBUFFER, fb);


            glBindFramebuffer(GL_FRAMEBUFFER, output_frame);
            //glDrawBuffer(GL_BACK);

            //switch texture slot... color to 0
            glActiveTexture (GL_TEXTURE0);
            glBindTexture (GL_TEXTURE_2D, input_frame);


            //glBindVertexArray(fsq_vertex_array_object);

            //VBOs
            //glBindBuffer(GL_ARRAY_BUFFER, fsq_vertex_vbo);
            //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
            //glEnableVertexAttribArray(0);


            //glUseProgram (DR_EdgeDetectionPassProgramIdId);

            //glPolygonMode(GL_FRONT_AND_BACK, GL_POLYGON);

            //glUniform2f (win_size_loc_edgedetectionpass, win->getWindowWidth(), win->getWindowHeight());
            //glUniform1i (frame_switch_loc_edgedetectionpass, frame_switch);
            glUniform1i (function_loc_edgedetectionpass, 4);

            glDrawArrays(GL_TRIANGLES, 0, fsq_triangle_count*3);

            //
            ////////////////////////////////////////////////////////////

            //swap
            //input_frame = fbo_3_tex_c;
            //output_frame = fbo_2;

            //input_frame = fbo_2_tex_c;
            //output_frame = fbo_3;

            if(input_frame == fbo_3_tex_c){
                input_frame = fbo_2_tex_c;
                output_frame = fbo_3;
            }
            else{
                input_frame = fbo_3_tex_c;
                output_frame = fbo_2;
            }

        }




        ////////////////////////////////////////////////////////////
        //  POST PROCESSING noise second
        //      use fbo_3_tex_c as input   fbo_2 as output

        //glDisable (GL_BLEND);

        //bind framebuffer so we can draw to the edge texture....
        //glBindFramebuffer(GL_FRAMEBUFFER, fb);


        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        //glDrawBuffer(GL_BACK);

        //switch texture slot... color to 0
        glActiveTexture (GL_TEXTURE0);
        glBindTexture (GL_TEXTURE_2D, input_frame);

        //glActiveTexture (GL_TEXTURE1);
        //glBindTexture (GL_TEXTURE_2D, fbo_1_tex_p);

        //glBindVertexArray(fsq_vertex_array_object);

        //VBOs
        //glBindBuffer(GL_ARRAY_BUFFER, fsq_vertex_vbo);
        //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        //glEnableVertexAttribArray(0);


        //glUseProgram (DR_EdgeDetectionPassProgramIdId);

        //glPolygonMode(GL_FRONT_AND_BACK, GL_POLYGON);

        //glUniform2f (win_size_loc_edgedetectionpass, win->getWindowWidth(), win->getWindowHeight());
        //glUniform1i (frame_switch_loc_edgedetectionpass, frame_switch);
        glUniform1i (function_loc_edgedetectionpass, 1);

        glDrawArrays(GL_TRIANGLES, 0, fsq_triangle_count*3);

        //
        ////////////////////////////////////////////////////////////



        /*

        ////////////////////////////////////////////////////////////
        //  POST PROCESSING h blur luminance fourth
        //      use fbo_2_tex_c as input   fbo_3 as output

        glDisable (GL_BLEND);

        //bind framebuffer so we can draw to the edge texture....
        //glBindFramebuffer(GL_FRAMEBUFFER, fb);


        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glDrawBuffer(GL_BACK);

        //switch texture slot... color to 0
        glActiveTexture (GL_TEXTURE0);
        glBindTexture (GL_TEXTURE_2D, fbo_2_tex_c);

        glActiveTexture (GL_TEXTURE1);
        glBindTexture (GL_TEXTURE_2D, fbo_1_tex_p);

        glBindVertexArray(fsq_vertex_array_object);

        //VBOs
        glBindBuffer(GL_ARRAY_BUFFER, fsq_vertex_vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);


        glUseProgram (DR_EdgeDetectionPassProgramIdId);

        glPolygonMode(GL_FRONT_AND_BACK, GL_POLYGON);

        glUniform2f (win_size_loc_edgedetectionpass, win->getWindowWidth(), win->getWindowHeight());
        glUniform1i (frame_switch_loc_edgedetectionpass, frame_switch);
        glUniform1i (function_loc_edgedetectionpass, 5);

        glDrawArrays(GL_TRIANGLES, 0, fsq_triangle_count*3);

        //
        ////////////////////////////////////////////////////////////

        */



        //WIREFRAME mode
        if((renderMode & PolygonModeWireframe) == PolygonModeWireframe){
            glUseProgram (DR_DebugPassProgramIdId);

            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

            glClear(GL_DEPTH_BUFFER_BIT);


            //the color we want to render in...
            glUniform3f (color_loc_debugpass, 1.0, 1.0, 1.0);
            //glPointSize(3.0f);



            //STATIC MODELS
            for(int i = 0; i < ot_nodes.size(); i++){
                //render one node...

                //copy the lists so we can itterate through them
                QList<QList<SP<CompositeObject> > > compositeobject_mesh_list = ot_nodes[i]->getModelLibrary()->getCompositeobjectMeshList();
                QList<QList<SP<Mesh> > > mesh_model_list = ot_nodes[i]->getModelLibrary()->getMeshModelList();
                QList<QList<SP<Model> > > model_mesh_list = ot_nodes[i]->getModelLibrary()->getModelMeshList();
                QList<SP<Material> > material_mesh_list = ot_nodes[i]->getModelLibrary()->getMaterialMeshList();

                //loop trough the material_mesh_list
                for(int index = 0; index < material_mesh_list.size(); index++){

                    //check if material was loaded...
                    if(material_mesh_list[index]->isLoaded()){
                        //no need to setup materials here

                        //tex
                        //glActiveTexture (GL_TEXTURE0+firstTextureIndex);
                        //glBindTexture(GL_TEXTURE_2D, material_mesh_list[index]->get_diffuse_map_texture());
                        //glUniform1i(glGetUniformLocation(DR_FirstPassProgramIdId, "sampler1"), firstTextureIndex);

                        //texBindsPerFrameCount += 1;


                        ///////////////////////////////////////////////////////////////////////////////////
                        ///
                        /// TODO:
                        ///
                        /// WE NEED TO CHECK IF THE MESH DATA IS UNIQUE..
                        /// BUT AT THIS POINt WE ASUME IT's ALLWAYS THE SAME
                        ///
                        ///////

                        if(mesh_model_list[index].size()>0){
                            SP<Mesh> mesh = mesh_model_list[index].at(0);

                            //VAO

                            glBindVertexArray(mesh->get_vertex_array_object());

                            //VBOs
                            glBindBuffer(GL_ARRAY_BUFFER, mesh->get_vertex_vbo());
                            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
                            glEnableVertexAttribArray(0);

                            /*
                            glBindBuffer(GL_ARRAY_BUFFER, mesh->get_texcoord_vbo());
                            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
                            glEnableVertexAttribArray(1);

                            glBindBuffer(GL_ARRAY_BUFFER, mesh->get_normal_vbo());
                            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
                            glEnableVertexAttribArray(2);
                            */

                            //now lets draw for every model it's meshs

                            //draw
                            int rendered = 0;
                            for(int mdl_index = 0; mdl_index < model_mesh_list[index].size(); mdl_index++){

                                //calculate if we need to draw the model
                                SP<Model> mdl =  model_mesh_list[index].at(mdl_index);

                                if(!mdl->isReadyToRender()){
                                    qDebug("mdl not ready to render...");
                                }

                                SP<Positation> posi = compositeobject_mesh_list[index][mdl_index]->getPositation();

                                m_m = posi->get_model_matrix();
                                pvm_m = p_m * v_m * m_m;


                                // don't need to check every mesh now if it is in the frustum yay....

                                //TRANSPOSE
                                for (int f = 0; f < 4; f++) {
                                    for (int g = 0; g < 4; g++) {
                                        pvm_mat[f * 4 + g] = (GLfloat) (pvm_m[f*4+g]);
                                    }
                                }


                                glUniformMatrix4fv(pvm_mat_loc_debugpass, 1, GL_FALSE, pvm_mat);




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
                QList<SP<CompositeObject> > compositeobject_list = ot_dynamic_models_nodes[i]->getCompositeObjects();

                //loop trough the material_mesh_list
                for(int index = 0; index < compositeobject_list.size(); index++){

                    SP<CompositeObject> compobj = compositeobject_list.at(index);
                    SP<Positation> posi = compobj->getPositation();
                    QList<SP<Mesh> > mesh_list = compobj->getModel()->get_meshs();

                    //loop trough mesh...
                    for(int meshs = 0; meshs < mesh_list.size(); meshs++){

                        SP<Mesh> mesh = mesh_list[meshs];

                        //no need to set up textures here

                        //tex
                        //glActiveTexture (GL_TEXTURE0+firstTextureIndex);
                        //glBindTexture(GL_TEXTURE_2D, mesh->get_material()->get_diffuse_map_texture());
                        //glUniform1i(glGetUniformLocation(DR_FirstPassProgramIdId, "sampler1"), firstTextureIndex);

                        //texBindsPerFrameCount += 1;


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

                        /*
                        glBindBuffer(GL_ARRAY_BUFFER, mesh->get_texcoord_vbo());
                        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
                        glEnableVertexAttribArray(1);

                        glBindBuffer(GL_ARRAY_BUFFER, mesh->get_normal_vbo());
                        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
                        glEnableVertexAttribArray(2);
                        */

                        //now lets draw for every model it's meshs

                        //draw


                        m_m = posi->get_model_matrix();
                        pvm_m = p_m * v_m * m_m;


                        // don't need to check every mesh now if it is in the frustum yay....

                        //TRANSPOSE
                        for (int f = 0; f < 4; f++) {
                            for (int g = 0; g < 4; g++) {
                                pvm_mat[f * 4 + g] = (GLfloat) (pvm_m[f*4+g]);
                            }
                        }


                        glUniformMatrix4fv(pvm_mat_loc_debugpass, 1, GL_FALSE, pvm_mat);


                        //draw
                        glDrawArrays(GL_TRIANGLES, 0, mesh->get_triangle_count()*3);
                        meshPerFrameCount +=1;
                        trianglesPerFrameCount += mesh->get_triangle_count();
                    }

                    //debugMessage("Rendered: " + QString::number(rendered));

                }
            }



        }


        //WIREFRAME mode
        if((renderMode & PolygonModeVertex) == PolygonModeVertex){
            glUseProgram (DR_DebugPassProgramIdId);

            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

            glClear(GL_DEPTH_BUFFER_BIT);


            //the color we want to render in...
            glUniform3f (color_loc_debugpass, 1.0, 0.0, 0.0);
            glPointSize(3.0f);



            //STATIC MODELS
            for(int i = 0; i < ot_nodes.size(); i++){
                //render one node...

                //copy the lists so we can itterate through them
                QList<QList<SP<CompositeObject> > > compositeobject_mesh_list = ot_nodes[i]->getModelLibrary()->getCompositeobjectMeshList();
                QList<QList<SP<Mesh> > > mesh_model_list = ot_nodes[i]->getModelLibrary()->getMeshModelList();
                QList<QList<SP<Model> > > model_mesh_list = ot_nodes[i]->getModelLibrary()->getModelMeshList();
                QList<SP<Material> > material_mesh_list = ot_nodes[i]->getModelLibrary()->getMaterialMeshList();

                //loop trough the material_mesh_list
                for(int index = 0; index < material_mesh_list.size(); index++){

                    //check if material was loaded...
                    if(material_mesh_list[index]->isLoaded()){
                        //no need to setup materials here

                        //tex
                        //glActiveTexture (GL_TEXTURE0+firstTextureIndex);
                        //glBindTexture(GL_TEXTURE_2D, material_mesh_list[index]->get_diffuse_map_texture());
                        //glUniform1i(glGetUniformLocation(DR_FirstPassProgramIdId, "sampler1"), firstTextureIndex);

                        //texBindsPerFrameCount += 1;


                        ///////////////////////////////////////////////////////////////////////////////////
                        ///
                        /// TODO:
                        ///
                        /// WE NEED TO CHECK IF THE MESH DATA IS UNIQUE..
                        /// BUT AT THIS POINt WE ASUME IT's ALLWAYS THE SAME
                        ///
                        ///////

                        if(mesh_model_list[index].size()>0){
                            SP<Mesh> mesh = mesh_model_list[index].at(0);

                            //VAO

                            glBindVertexArray(mesh->get_vertex_array_object());

                            //VBOs
                            glBindBuffer(GL_ARRAY_BUFFER, mesh->get_vertex_vbo());
                            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
                            glEnableVertexAttribArray(0);

                            /*
                            glBindBuffer(GL_ARRAY_BUFFER, mesh->get_texcoord_vbo());
                            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
                            glEnableVertexAttribArray(1);

                            glBindBuffer(GL_ARRAY_BUFFER, mesh->get_normal_vbo());
                            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
                            glEnableVertexAttribArray(2);
                            */

                            //now lets draw for every model it's meshs

                            //draw
                            int rendered = 0;
                            for(int mdl_index = 0; mdl_index < model_mesh_list[index].size(); mdl_index++){

                                //calculate if we need to draw the model
                                SP<Model> mdl =  model_mesh_list[index].at(mdl_index);

                                if(!mdl->isReadyToRender()){
                                    qDebug("mdl not ready to render...");
                                }

                                SP<Positation> posi = compositeobject_mesh_list[index][mdl_index]->getPositation();

                                m_m = posi->get_model_matrix();
                                pvm_m = p_m * v_m * m_m;


                                // don't need to check every mesh now if it is in the frustum yay....

                                //TRANSPOSE
                                for (int f = 0; f < 4; f++) {
                                    for (int g = 0; g < 4; g++) {
                                        pvm_mat[f * 4 + g] = (GLfloat) (pvm_m[f*4+g]);
                                    }
                                }


                                glUniformMatrix4fv(pvm_mat_loc_debugpass, 1, GL_FALSE, pvm_mat);




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
                QList<SP<CompositeObject> > compositeobject_list = ot_dynamic_models_nodes[i]->getCompositeObjects();

                //loop trough the material_mesh_list
                for(int index = 0; index < compositeobject_list.size(); index++){

                    SP<CompositeObject> compobj = compositeobject_list.at(index);
                    SP<Positation> posi = compobj->getPositation();
                    QList<SP<Mesh> > mesh_list = compobj->getModel()->get_meshs();

                    //loop trough mesh...
                    for(int meshs = 0; meshs < mesh_list.size(); meshs++){

                        SP<Mesh> mesh = mesh_list[meshs];

                        //no need to set up textures here

                        //tex
                        //glActiveTexture (GL_TEXTURE0+firstTextureIndex);
                        //glBindTexture(GL_TEXTURE_2D, mesh->get_material()->get_diffuse_map_texture());
                        //glUniform1i(glGetUniformLocation(DR_FirstPassProgramIdId, "sampler1"), firstTextureIndex);

                        //texBindsPerFrameCount += 1;


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

                        /*
                        glBindBuffer(GL_ARRAY_BUFFER, mesh->get_texcoord_vbo());
                        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
                        glEnableVertexAttribArray(1);

                        glBindBuffer(GL_ARRAY_BUFFER, mesh->get_normal_vbo());
                        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
                        glEnableVertexAttribArray(2);
                        */

                        //now lets draw for every model it's meshs

                        //draw


                        m_m = posi->get_model_matrix();
                        pvm_m = p_m * v_m * m_m;


                        // don't need to check every mesh now if it is in the frustum yay....

                        //TRANSPOSE
                        for (int f = 0; f < 4; f++) {
                            for (int g = 0; g < 4; g++) {
                                pvm_mat[f * 4 + g] = (GLfloat) (pvm_m[f*4+g]);
                            }
                        }


                        glUniformMatrix4fv(pvm_mat_loc_debugpass, 1, GL_FALSE, pvm_mat);


                        //draw
                        glDrawArrays(GL_TRIANGLES, 0, mesh->get_triangle_count()*3);
                        meshPerFrameCount +=1;
                        trianglesPerFrameCount += mesh->get_triangle_count();
                    }

                    //debugMessage("Rendered: " + QString::number(rendered));

                }
            }



        }





        //additional debug modes

        //WIREFRAME LIGHTS mode
        if((renderMode & PolygonModeLightWireframe) == PolygonModeLightWireframe){
            glUseProgram (DR_DebugPassProgramIdId);

            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

            glClear(GL_DEPTH_BUFFER_BIT);


            //the color we want to render in...
            glUniform3f (color_loc_debugpass, 1.0, 1.0, 0.0);
            //glPointSize(3.0f);


            //DYNAMIC MODELS
            for(int i = 0; i < ot_dynamic_lights_nodes.size(); i++){
                //render one node...

                //copy the lists so we can itterate through them
                QList<SP<CompositeObject> > compositeobject_list = ot_dynamic_lights_nodes[i]->getCompositeObjects();

                //loop trough the material_mesh_list
                for(int index = 0; index < compositeobject_list.size(); index++){

                    SP<CompositeObject> compobj = compositeobject_list.at(index);
                    SP<Positation> posi = compobj->getPositation();
                    QList<SP<Mesh> > mesh_list = compobj->getModel()->get_meshs();

                    //loop trough mesh...
                    for(int meshs = 0; meshs < mesh_list.size(); meshs++){

                        SP<Mesh> mesh = mesh_list[meshs];

                        //no need to set up textures here

                        //tex
                        //glActiveTexture (GL_TEXTURE0+firstTextureIndex);
                        //glBindTexture(GL_TEXTURE_2D, mesh->get_material()->get_diffuse_map_texture());
                        //glUniform1i(glGetUniformLocation(DR_FirstPassProgramIdId, "sampler1"), firstTextureIndex);

                        //texBindsPerFrameCount += 1;


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

                        /*
                        glBindBuffer(GL_ARRAY_BUFFER, mesh->get_texcoord_vbo());
                        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
                        glEnableVertexAttribArray(1);

                        glBindBuffer(GL_ARRAY_BUFFER, mesh->get_normal_vbo());
                        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
                        glEnableVertexAttribArray(2);
                        */

                        //now lets draw for every model it's meshs

                        //draw


                        m_m = posi->get_model_matrix();
                        pvm_m = p_m * v_m * m_m;


                        // don't need to check every mesh now if it is in the frustum yay....

                        //TRANSPOSE
                        for (int f = 0; f < 4; f++) {
                            for (int g = 0; g < 4; g++) {
                                pvm_mat[f * 4 + g] = (GLfloat) (pvm_m[f*4+g]);
                            }
                        }


                        glUniformMatrix4fv(pvm_mat_loc_debugpass, 1, GL_FALSE, pvm_mat);


                        //draw
                        glDrawArrays(GL_TRIANGLES, 0, mesh->get_triangle_count()*3);
                        meshPerFrameCount +=1;
                        trianglesPerFrameCount += mesh->get_triangle_count();
                    }
                }
            }
        }


        if((renderMode & PolygonModeLightVertex) == PolygonModeLightVertex){
            glUseProgram (DR_DebugPassProgramIdId);

            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

            glClear(GL_DEPTH_BUFFER_BIT);


            //the color we want to render in...
            glUniform3f (color_loc_debugpass, 1.0, 0.5, 0.0);
            glPointSize(3.0f);


            //DYNAMIC MODELS
            for(int i = 0; i < ot_dynamic_lights_nodes.size(); i++){
                //render one node...

                //copy the lists so we can itterate through them
                QList<SP<CompositeObject> > compositeobject_list = ot_dynamic_lights_nodes[i]->getCompositeObjects();

                //loop trough the material_mesh_list
                for(int index = 0; index < compositeobject_list.size(); index++){

                    SP<CompositeObject> compobj = compositeobject_list.at(index);
                    SP<Positation> posi = compobj->getPositation();
                    QList<SP<Mesh> > mesh_list = compobj->getModel()->get_meshs();

                    //loop trough mesh...
                    for(int meshs = 0; meshs < mesh_list.size(); meshs++){

                        SP<Mesh> mesh = mesh_list[meshs];

                        //no need to set up textures here

                        //tex
                        //glActiveTexture (GL_TEXTURE0+firstTextureIndex);
                        //glBindTexture(GL_TEXTURE_2D, mesh->get_material()->get_diffuse_map_texture());
                        //glUniform1i(glGetUniformLocation(DR_FirstPassProgramIdId, "sampler1"), firstTextureIndex);

                        //texBindsPerFrameCount += 1;


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

                        /*
                        glBindBuffer(GL_ARRAY_BUFFER, mesh->get_texcoord_vbo());
                        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
                        glEnableVertexAttribArray(1);

                        glBindBuffer(GL_ARRAY_BUFFER, mesh->get_normal_vbo());
                        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
                        glEnableVertexAttribArray(2);
                        */

                        //now lets draw for every model it's meshs

                        //draw


                        m_m = posi->get_model_matrix();
                        pvm_m = p_m * v_m * m_m;


                        // don't need to check every mesh now if it is in the frustum yay....

                        //TRANSPOSE
                        for (int f = 0; f < 4; f++) {
                            for (int g = 0; g < 4; g++) {
                                pvm_mat[f * 4 + g] = (GLfloat) (pvm_m[f*4+g]);
                            }
                        }


                        glUniformMatrix4fv(pvm_mat_loc_debugpass, 1, GL_FALSE, pvm_mat);


                        //draw
                        glDrawArrays(GL_TRIANGLES, 0, mesh->get_triangle_count()*3);
                        meshPerFrameCount +=1;
                        trianglesPerFrameCount += mesh->get_triangle_count();
                    }

                    //debugMessage("Rendered: " + QString::number(rendered));

                }
            }
        }



        //WIREFRAME OctTree mode
        if((renderMode & PolygonModeOctTreeWireframe) == PolygonModeOctTreeWireframe){

            SP<Model> unitcube = objectworld->getUnitCubeModel();
            if(unitcube->isReadyToRender()){

                glUseProgram (DR_DebugPassProgramIdId);

                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

                glClear(GL_DEPTH_BUFFER_BIT);


                //the color we want to render in...
                glUniform3f (color_loc_debugpass, 0.2, 0.2, 1.0);
                //glPointSize(3.0f);

                //setup the model...
                SP<Mesh> mesh = unitcube->get_meshs().at(0);

                //VAO

                glBindVertexArray(mesh->get_vertex_array_object());

                //VBOs
                glBindBuffer(GL_ARRAY_BUFFER, mesh->get_vertex_vbo());
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
                glEnableVertexAttribArray(0);


                //STATIC OctTree nodes
                for(int i = 0; i < ot_nodes.size(); i++){
                    //render one node...

                    SP<OctTree> ot_n = ot_nodes.at(i);

                    if(ot_n->getModelLibrary()->modelCount() > 0){
                        SP<Positation> posi(new Positation());
                        posi->set_position(ot_n->getPosition());
                        posi->set_scale(ot_n->getSize(),ot_n->getSize(),ot_n->getSize());


                        m_m = posi->get_model_matrix();
                        pvm_m = p_m * v_m * m_m;


                        // don't need to check every mesh now if it is in the frustum yay....

                        //TRANSPOSE
                        for (int f = 0; f < 4; f++) {
                            for (int g = 0; g < 4; g++) {
                                pvm_mat[f * 4 + g] = (GLfloat) (pvm_m[f*4+g]);
                            }
                        }


                        glUniformMatrix4fv(pvm_mat_loc_debugpass, 1, GL_FALSE, pvm_mat);

                        //draw
                        glDrawArrays(GL_TRIANGLES, 0, mesh->get_triangle_count()*3);
                        meshPerFrameCount +=1;
                        trianglesPerFrameCount += mesh->get_triangle_count();
                    }
                }

                glUniform3f (color_loc_debugpass, 0.0, 1.0, 0.0);

                //DYNAMIC OctTree nodes
                for(int i = 0; i < ot_dynamic_models_nodes.size(); i++){
                    //render one node...

                    SP<OctTreeFast> ot_n = ot_dynamic_models_nodes.at(i);

                    if(ot_n->getObjectCount() > 0){


                        SP<Positation> posi(new Positation());
                        posi->set_position(ot_n->getPosition());
                        posi->set_scale(ot_n->getSize(),ot_n->getSize(),ot_n->getSize());


                        m_m = posi->get_model_matrix();
                        pvm_m = p_m * v_m * m_m;


                        // don't need to check every mesh now if it is in the frustum yay....

                        //TRANSPOSE
                        for (int f = 0; f < 4; f++) {
                            for (int g = 0; g < 4; g++) {
                                pvm_mat[f * 4 + g] = (GLfloat) (pvm_m[f*4+g]);
                            }
                        }


                        glUniformMatrix4fv(pvm_mat_loc_debugpass, 1, GL_FALSE, pvm_mat);

                        //draw
                        glDrawArrays(GL_TRIANGLES, 0, mesh->get_triangle_count()*3);
                        meshPerFrameCount +=1;
                        trianglesPerFrameCount += mesh->get_triangle_count();
                    }
                }


                glUniform3f (color_loc_debugpass, 1.0, 1.0, 0.0);

                //DYNAMIC OctTree nodes lights...
                for(int i = 0; i < ot_dynamic_lights_nodes.size(); i++){
                    //render one node...

                    SP<OctTreeFast> ot_n = ot_dynamic_lights_nodes.at(i);

                    if(ot_n->getObjectCount() > 0){

                        SP<Positation> posi(new Positation());
                        posi->set_position(ot_n->getPosition());
                        posi->set_scale(ot_n->getSize(),ot_n->getSize(),ot_n->getSize());


                        m_m = posi->get_model_matrix();
                        pvm_m = p_m * v_m * m_m;


                        // don't need to check every mesh now if it is in the frustum yay....

                        //TRANSPOSE
                        for (int f = 0; f < 4; f++) {
                            for (int g = 0; g < 4; g++) {
                                pvm_mat[f * 4 + g] = (GLfloat) (pvm_m[f*4+g]);
                            }
                        }


                        glUniformMatrix4fv(pvm_mat_loc_debugpass, 1, GL_FALSE, pvm_mat);

                        //draw
                        glDrawArrays(GL_TRIANGLES, 0, mesh->get_triangle_count()*3);
                        meshPerFrameCount +=1;
                        trianglesPerFrameCount += mesh->get_triangle_count();
                    }
                }
            }
        }



        //WIREFRAME OctTree mode
        if((renderMode & PolygonModeOctTreeVertex) == PolygonModeOctTreeVertex){

            SP<Model> unitcube = objectworld->getUnitCubeModel();
            if(unitcube->isReadyToRender()){

                glUseProgram (DR_DebugPassProgramIdId);

                glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

                glClear(GL_DEPTH_BUFFER_BIT);


                //the color we want to render in...
                glUniform3f (color_loc_debugpass, 1.0, 1.0, 1.0);
                glPointSize(3.0f);

                //setup the model...
                SP<Mesh> mesh = unitcube->get_meshs().at(0);

                //VAO

                glBindVertexArray(mesh->get_vertex_array_object());

                //VBOs
                glBindBuffer(GL_ARRAY_BUFFER, mesh->get_vertex_vbo());
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
                glEnableVertexAttribArray(0);


                //STATIC OctTree nodes
                for(int i = 0; i < ot_nodes.size(); i++){
                    //render one node...

                    SP<OctTree> ot_n = ot_nodes.at(i);


                    if(ot_n->getModelLibrary()->modelCount() > 0){

                        SP<Positation> posi(new Positation());
                        posi->set_position(ot_n->getPosition());
                        posi->set_scale(ot_n->getSize(),ot_n->getSize(),ot_n->getSize());


                        m_m = posi->get_model_matrix();
                        pvm_m = p_m * v_m * m_m;


                        // don't need to check every mesh now if it is in the frustum yay....

                        //TRANSPOSE
                        for (int f = 0; f < 4; f++) {
                            for (int g = 0; g < 4; g++) {
                                pvm_mat[f * 4 + g] = (GLfloat) (pvm_m[f*4+g]);
                            }
                        }


                        glUniformMatrix4fv(pvm_mat_loc_debugpass, 1, GL_FALSE, pvm_mat);

                        //draw
                        glDrawArrays(GL_TRIANGLES, 0, mesh->get_triangle_count()*3);
                        meshPerFrameCount +=1;
                        trianglesPerFrameCount += mesh->get_triangle_count();
                    }
                }

                glUniform3f (color_loc_debugpass, 0.0, 1.0, 0.0);

                //DYNAMIC OctTree nodes
                for(int i = 0; i < ot_dynamic_models_nodes.size(); i++){
                    //render one node...

                    SP<OctTreeFast> ot_n = ot_dynamic_models_nodes.at(i);

                    if(ot_n->getObjectCount() > 0){

                        SP<Positation> posi(new Positation());
                        posi->set_position(ot_n->getPosition());
                        posi->set_scale(ot_n->getSize(),ot_n->getSize(),ot_n->getSize());


                        m_m = posi->get_model_matrix();
                        pvm_m = p_m * v_m * m_m;


                        // don't need to check every mesh now if it is in the frustum yay....

                        //TRANSPOSE
                        for (int f = 0; f < 4; f++) {
                            for (int g = 0; g < 4; g++) {
                                pvm_mat[f * 4 + g] = (GLfloat) (pvm_m[f*4+g]);
                            }
                        }


                        glUniformMatrix4fv(pvm_mat_loc_debugpass, 1, GL_FALSE, pvm_mat);

                        //draw
                        glDrawArrays(GL_TRIANGLES, 0, mesh->get_triangle_count()*3);
                        meshPerFrameCount +=1;
                        trianglesPerFrameCount += mesh->get_triangle_count();
                    }
                }


                glUniform3f (color_loc_debugpass, 1.0, 1.0, 0.0);

                //DYNAMIC OctTree nodes lights...
                for(int i = 0; i < ot_dynamic_lights_nodes.size(); i++){
                    //render one node...

                    SP<OctTreeFast> ot_n = ot_dynamic_lights_nodes.at(i);

                    if(ot_n->getObjectCount() > 0){

                        SP<Positation> posi(new Positation());
                        posi->set_position(ot_n->getPosition());
                        posi->set_scale(ot_n->getSize(),ot_n->getSize(),ot_n->getSize());


                        m_m = posi->get_model_matrix();
                        pvm_m = p_m * v_m * m_m;


                        // don't need to check every mesh now if it is in the frustum yay....

                        //TRANSPOSE
                        for (int f = 0; f < 4; f++) {
                            for (int g = 0; g < 4; g++) {
                                pvm_mat[f * 4 + g] = (GLfloat) (pvm_m[f*4+g]);
                            }
                        }


                        glUniformMatrix4fv(pvm_mat_loc_debugpass, 1, GL_FALSE, pvm_mat);

                        //draw
                        glDrawArrays(GL_TRIANGLES, 0, mesh->get_triangle_count()*3);
                        meshPerFrameCount +=1;
                        trianglesPerFrameCount += mesh->get_triangle_count();
                    }
                }
            }
        }



        glPointSize(1.0f);
        //revert the states
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, 0);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, 0);

        glEnable (GL_DEPTH_TEST);
        glDepthMask (GL_TRUE);
        glDisable (GL_BLEND);


        frame_switch += 1;
        if(frame_switch > 300){
            frame_switch = 1;
        }

    }//end of objectworld

}















//OLD RENDERING CRAP






/*
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


                    //debugMessage("Rendered: " +
                    //             QString::number(rendered) + " / " +
                    //             QString::number(model_mesh_list[index].size()) + " models.");

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


                        //    Indizes
                        //    |    0        4        8        12   |
                        //    |                                    |
                        //    |    1        5        9        13   |
                        //    |                                    |
                        //    |    2        6        10       14   |
                        //    |                                    |
                        //    |    3        7        11       15   |


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

                    //debugMessage("Rendered: " +
                    //             QString::number(rendered) + " / " +
                    //             QString::number(l_model_mesh_list[index].size()) + " lights.");

                }
            }





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



    }
    else{
        debugMessage("ERROR during rendering: The ModelLibrary isn't set yet!");
    }
}

*/

void Renderer::render(SP<Model> m){

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

void Renderer::setPostProcessingMode(int postProcessingModeBits){
    postProcessingMode = postProcessingModeBits;
}

int Renderer::getPostProcessingMode(){
    return postProcessingMode;
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

bool Renderer::createFullScreenQuad(){
    //init fsq
    fsq_triangle_count = 2;

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
    glBufferData(GL_ARRAY_BUFFER, fsq_triangle_count * 3* 3 * sizeof(GLfloat), fsq_vertices, GL_STATIC_DRAW);



    glGenBuffers(1, &fsq_texcoord_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, fsq_texcoord_vbo);
    glBufferData(GL_ARRAY_BUFFER, fsq_triangle_count * 3 * 3 * sizeof(GLfloat), fsq_texcoords, GL_STATIC_DRAW);



    glGenBuffers(1, &fsq_normal_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, fsq_normal_vbo);
    glBufferData(GL_ARRAY_BUFFER, fsq_triangle_count * 3 * 3 * sizeof(GLfloat), fsq_normals, GL_STATIC_DRAW);


    debugMessage("created fullscreenquad!");
    //
    //////////////////////////////

    return true;
}

bool Renderer::createSkyBox(){
    //sky box



    //init sb
    sb_triangle_count = 12;


    sb_vertices = new GLfloat[108]{
      -10.0f,  10.0f, -10.0f,
      -10.0f, -10.0f, -10.0f,
       10.0f, -10.0f, -10.0f,
       10.0f, -10.0f, -10.0f,
       10.0f,  10.0f, -10.0f,
      -10.0f,  10.0f, -10.0f,

      -10.0f, -10.0f,  10.0f,
      -10.0f, -10.0f, -10.0f,
      -10.0f,  10.0f, -10.0f,
      -10.0f,  10.0f, -10.0f,
      -10.0f,  10.0f,  10.0f,
      -10.0f, -10.0f,  10.0f,

       10.0f, -10.0f, -10.0f,
       10.0f, -10.0f,  10.0f,
       10.0f,  10.0f,  10.0f,
       10.0f,  10.0f,  10.0f,
       10.0f,  10.0f, -10.0f,
       10.0f, -10.0f, -10.0f,

      -10.0f, -10.0f,  10.0f,
      -10.0f,  10.0f,  10.0f,
       10.0f,  10.0f,  10.0f,
       10.0f,  10.0f,  10.0f,
       10.0f, -10.0f,  10.0f,
      -10.0f, -10.0f,  10.0f,

      -10.0f,  10.0f, -10.0f,
       10.0f,  10.0f, -10.0f,
       10.0f,  10.0f,  10.0f,
       10.0f,  10.0f,  10.0f,
      -10.0f,  10.0f,  10.0f,
      -10.0f,  10.0f, -10.0f,

      -10.0f, -10.0f, -10.0f,
      -10.0f, -10.0f,  10.0f,
       10.0f, -10.0f, -10.0f,
       10.0f, -10.0f, -10.0f,
      -10.0f, -10.0f,  10.0f,
       10.0f, -10.0f,  10.0f
    };

    /*
    sb_vertices = new GLfloat[108];

    sb_vertices[0] = -10.0f;
    sb_vertices[1] =  10.0f;
    sb_vertices[2] = -10.0f;
    sb_vertices[3] =  10.0f;
    sb_vertices[4] = -10.0f;
    sb_vertices[5] = -10.0f;
    sb_vertices[6] =  10.0f;
    sb_vertices[7] = -10.0f;
    sb_vertices[8] = -10.0f;
    sb_vertices[9] =  10.0f;
    sb_vertices[10] = -10.0f;
    sb_vertices[11] = -10.0f;
    sb_vertices[12] =  10.0f;
    sb_vertices[13] =  10.0f;
    sb_vertices[14] = -10.0f;
    sb_vertices[15] = -10.0f;
    sb_vertices[16] =  10.0f;
    sb_vertices[17] = -10.0f;
    sb_vertices[18] = -10.0f;
    sb_vertices[19] = -10.0f;
    sb_vertices[20] =  10.0f;
    sb_vertices[21] = -10.0f;
    sb_vertices[22] = -10.0f;
    sb_vertices[23] = -10.0f;
    sb_vertices[24] = -10.0f;
    sb_vertices[25] =  10.0f;
    sb_vertices[26] = -10.0f;
    sb_vertices[27] = -10.0f;
    sb_vertices[28] =  10.0f;
    sb_vertices[29] = -10.0f;
    sb_vertices[30] = -10.0f;
    sb_vertices[31] =  10.0f;
    sb_vertices[32] =  10.0f;
    sb_vertices[33] = -10.0f;
    sb_vertices[34] = -10.0f;
    sb_vertices[35] =  10.0f;
    sb_vertices[36] =  10.0f;
    sb_vertices[37] = -10.0f;
    sb_vertices[38] = -10.0f;
    sb_vertices[39] =  10.0f;
    sb_vertices[40] = -10.0f;
    sb_vertices[41] =  10.0f;
    sb_vertices[42] =  10.0f;
    sb_vertices[43] =  10.0f;
    sb_vertices[44] =  10.0f;
    sb_vertices[45] =  10.0f;
    sb_vertices[46] =  10.0f;
    sb_vertices[47] =  10.0f;
    sb_vertices[48] =  10.0f;
    sb_vertices[49] =  10.0f;
    sb_vertices[50] = -10.0f;
    sb_vertices[51] =  10.0f;
    sb_vertices[52] = -10.0f;
    sb_vertices[53] = -10.0f;
    sb_vertices[54] = -10.0f;
    sb_vertices[55] = -10.0f;
    sb_vertices[56] =  10.0f;
    sb_vertices[57] = -10.0f;
    sb_vertices[58] =  10.0f;
    sb_vertices[59] =  10.0f;
    sb_vertices[60] =  10.0f;
    sb_vertices[61] =  10.0f;
    sb_vertices[62] =  10.0f;
    sb_vertices[63] =  10.0f;
    sb_vertices[64] =  10.0f;
    sb_vertices[65] =  10.0f;
    sb_vertices[66] =  10.0f;
    sb_vertices[67] = -10.0f;
    sb_vertices[68] =  10.0f;
    sb_vertices[69] = -10.0f;
    sb_vertices[70] = -10.0f;
    sb_vertices[71] =  10.0f;
    sb_vertices[72] = -10.0f;
    sb_vertices[73] =  10.0f;
    sb_vertices[74] = -10.0f;
    sb_vertices[75] =  10.0f;
    sb_vertices[76] =  10.0f;
    sb_vertices[77] = -10.0f;
    sb_vertices[78] =  10.0f;
    sb_vertices[79] =  10.0f;
    sb_vertices[80] =  10.0f;
    sb_vertices[81] =  10.0f;
    sb_vertices[82] =  10.0f;
    sb_vertices[83] =  10.0f;
    sb_vertices[84] = -10.0f;
    sb_vertices[85] =  10.0f;
    sb_vertices[86] =  10.0f;
    sb_vertices[87] = -10.0f;
    sb_vertices[88] =  10.0f;
    sb_vertices[89] = -10.0f;
    sb_vertices[90] = -10.0f;
    sb_vertices[91] = -10.0f;
    sb_vertices[92] = -10.0f;
    sb_vertices[93] = -10.0f;
    sb_vertices[94] = -10.0f;
    sb_vertices[95] =  10.0f;
    sb_vertices[96] =  10.0f;
    sb_vertices[97] = -10.0f;
    sb_vertices[98] = -10.0f;
    sb_vertices[99] =  10.0f;
    sb_vertices[100] = -10.0f;
    sb_vertices[101] = -10.0f;
    sb_vertices[102] = -10.0f;
    sb_vertices[103] = -10.0f;
    sb_vertices[104] =  10.0f;
    sb_vertices[105] =  10.0f;
    sb_vertices[106] = -10.0f;
    sb_vertices[107] =  10.0f;

    */




    //////////////////////////////
    // SKYBOX VAO and VBO
    debugMessage("creating skybox");

    glGenVertexArrays(1, &sb_vertex_array_object);

    glBindVertexArray(sb_vertex_array_object);

    glGenBuffers(1, &sb_vertex_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, sb_vertex_vbo);
    glBufferData(GL_ARRAY_BUFFER, sb_triangle_count * 3* 3 * sizeof(GLfloat), sb_vertices, GL_STATIC_DRAW);



    //SKYBOX TEXMAP... atm hardcoded...
    sb_texmap = new TextureMapCube(
                "purple_sky_box",
                QApplication::applicationDirPath() + "/SkyBox/front.png",
                QApplication::applicationDirPath() + "/SkyBox/back.png",
                QApplication::applicationDirPath() + "/SkyBox/top.png",
                QApplication::applicationDirPath() + "/SkyBox/bottom.png",
                QApplication::applicationDirPath() + "/SkyBox/left.png",
                QApplication::applicationDirPath() + "/SkyBox/right.png"
                );
    sb_texmap->loadData();
    sb_texmap->loadGLdata();


    debugMessage("created skybox!");
    //
    //////////////////////////////

    return true;
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
    //SKYBOX SHADER
    GLenum ErrorCheckValue = glGetError();

    //vertex shader

    QString dr_vertex_skyboxpass_path(QApplication::applicationDirPath() +
                                     "/shaders/deferred_renderer_skybox_pass.vsh");
    Shader dr_vertex_skyboxpass(dr_vertex_skyboxpass_path,
                               GL_VERTEX_SHADER);
    if(dr_vertex_skyboxpass.isCreated()){
        DR_SkyBoxPassVertexShaderId = dr_vertex_skyboxpass.getShaderId();
        debugMessage("Deferred Renderer skybox pass vertex shader compiled successful.");
        debugMessage("path:  " + dr_vertex_skyboxpass_path);
    }
    else{
        debugMessage("Deferred Renderer skybox pass vertex shader compiled failed!");
        debugMessage("path:  " + dr_vertex_skyboxpass_path);
        debugMessage(dr_vertex_skyboxpass.getError());
        debugMessage(QString(dr_vertex_skyboxpass.getShaderSource()));
        return false;
    }

    //fragment shader
    Shader dr_fragment_skyboxpass(QApplication::applicationDirPath() +
                               "/shaders/deferred_renderer_skybox_pass.fsh",
                               GL_FRAGMENT_SHADER);
    if(dr_fragment_skyboxpass.isCreated()){
        DR_SkyBoxPassFragmentShaderId = dr_fragment_skyboxpass.getShaderId();
        debugMessage("Deferred Renderer skybox pass fragment shader compiled successful.");
    }
    else{
        debugMessage("Deferred Renderer skybox pass fragment shader compiled failed!");
        debugMessage(dr_fragment_skyboxpass.getError());
        return false;
    }


    //create program, link it and bind locs
    DR_SkyBoxPassProgramIdId = glCreateProgram();
    glAttachShader(DR_SkyBoxPassProgramIdId, DR_SkyBoxPassVertexShaderId);
    glAttachShader(DR_SkyBoxPassProgramIdId, DR_SkyBoxPassFragmentShaderId);


    // Bind the custom vertex attributes
    glBindAttribLocation(DR_SkyBoxPassProgramIdId, 0, "vp");

    glLinkProgram(DR_SkyBoxPassProgramIdId);

    GLint linked;
    glGetProgramiv(DR_SkyBoxPassProgramIdId, GL_LINK_STATUS, &linked);
    if (linked){
        debugMessage("deferred renderer program pass skybox linked");
    }
    else{
        debugMessage("deferred renderer program pass skybox linking failed!!!");
        char messages[256];
        glGetProgramInfoLog(DR_SkyBoxPassProgramIdId, sizeof(messages), 0, &messages[0]);
        debugMessage(QString(messages));
        return false;
    }

    glUseProgram(DR_SkyBoxPassProgramIdId);

    ErrorCheckValue = glGetError();
    if (ErrorCheckValue != GL_NO_ERROR)
    {
        debugMessage("ERROR(3): Could not create the shaders: " + QString((char*) gluErrorString(ErrorCheckValue)));
        //exit(EXIT_FAILURE);
        return false;
    }

    glEnableVertexAttribArray(0);
    //glEnableVertexAttribArray(1);
    //glEnableVertexAttribArray(2);

    p_mat_loc_skyboxpass = glGetUniformLocation(DR_SkyBoxPassProgramIdId, "P");
    v_mat_loc_skyboxpass = glGetUniformLocation(DR_SkyBoxPassProgramIdId, "V");
    m_mat_loc_skyboxpass = glGetUniformLocation(DR_SkyBoxPassProgramIdId, "M");
    vm_mat_loc_skyboxpass = glGetUniformLocation(DR_SkyBoxPassProgramIdId, "VM");

    glUniform1i(glGetUniformLocation(DR_SkyBoxPassProgramIdId, "sampler1"), 0);


    ErrorCheckValue = glGetError();
    if (ErrorCheckValue != GL_NO_ERROR)
    {
        debugMessage("ERROR: after Shader: " + QString((char*) gluErrorString(ErrorCheckValue)));
        //exit(EXIT_FAILURE);
        return false;
    }
    //skybox pass end
    ////////////////////////////////////////////////////////////////////////////////////////////









    /////////////////////////////////////////////////////////////////////////////////////
    //BUFFER COPY PASS


    //vertex shader
    Shader dr_vertex_buffercopypass(QApplication::applicationDirPath() +
                               "/shaders/deferred_renderer_buffercopy_pass.vsh",
                               GL_VERTEX_SHADER);
    if(dr_vertex_buffercopypass.isCreated()){
        DR_BufferCopyPassVertexShaderId = dr_vertex_buffercopypass.getShaderId();
        debugMessage("Deferred Renderer buffercopy pass vertex shader compiled successful.");
    }
    else{
        debugMessage("Deferred Renderer buffercopy pass vertex shader compiled failed!");
        debugMessage(dr_vertex_buffercopypass.getError());
        return false;
    }


    //fragment shader
    Shader dr_fragment_buffercopypass(QApplication::applicationDirPath() +
                               "/shaders/deferred_renderer_buffercopy_pass.fsh",
                               GL_FRAGMENT_SHADER);
    if(dr_fragment_buffercopypass.isCreated()){
        DR_BufferCopyPassFragmentShaderId = dr_fragment_buffercopypass.getShaderId();
        debugMessage("Deferred Renderer buffercopy pass fragment shader compiled successful.");
    }
    else{
        debugMessage("Deferred Renderer buffercopy pass fragment shader compiled failed!");
        debugMessage(dr_fragment_buffercopypass.getError());
        return false;
    }





    //create program, link it and bind locs
    DR_BufferCopyPassProgramIdId = glCreateProgram();
    glAttachShader(DR_BufferCopyPassProgramIdId, DR_BufferCopyPassVertexShaderId);
    glAttachShader(DR_BufferCopyPassProgramIdId, DR_BufferCopyPassFragmentShaderId);


    glLinkProgram(DR_BufferCopyPassProgramIdId);

    //GLint linked;
    glGetProgramiv(DR_BufferCopyPassProgramIdId, GL_LINK_STATUS, &linked);
    if (linked){
        debugMessage("deferred renderer program pass buffercopy linked");
    }
    else{
        debugMessage("deferred renderer program pass buffercopy linking failed!!!");
        char messages[256];
        glGetProgramInfoLog(DR_BufferCopyPassProgramIdId, sizeof(messages), 0, &messages[0]);
        debugMessage(QString(messages));
        return false;
    }

    glUseProgram(DR_BufferCopyPassProgramIdId);

    ErrorCheckValue = glGetError();
    if (ErrorCheckValue != GL_NO_ERROR)
    {
        debugMessage("ERROR(3): Could not create the shaders: " + QString((char*) gluErrorString(ErrorCheckValue)));
        //exit(EXIT_FAILURE);
        return false;
    }


    win_size_loc_buffercopypass = glGetUniformLocation(DR_BufferCopyPassProgramIdId, "win_size");


    glUniform1i(glGetUniformLocation(DR_BufferCopyPassProgramIdId, "p_tex"), 0);
    glUniform1i(glGetUniformLocation(DR_BufferCopyPassProgramIdId, "c_tex"), 1);
    //buffer copy pass end
    /////////////////////////////////////////////////////////////////////////////////////



















    ////////////////////////////////////////////////////////////////////////////////
    //FIRST SHADER

    //vertex shader

    QString dr_vertex_firstpass_path(QApplication::applicationDirPath() +
                                     "/shaders/deferred_renderer_first_pass.vsh");
    Shader dr_vertex_firstpass(dr_vertex_firstpass_path,
                               GL_VERTEX_SHADER);
    if(dr_vertex_firstpass.isCreated()){
        DR_FirstPassVertexShaderId = dr_vertex_firstpass.getShaderId();
        debugMessage("Deferred Renderer first pass vertex shader compiled successful.");
        debugMessage("path:  " + dr_vertex_firstpass_path);
    }
    else{
        debugMessage("Deferred Renderer first pass vertex shader compiled failed!");
        debugMessage("path:  " + dr_vertex_firstpass_path);
        debugMessage(dr_vertex_firstpass.getError());
        debugMessage(QString(dr_vertex_firstpass.getShaderSource()));
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

    //GLint linked;
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

    p_mat_loc_firstpass = glGetUniformLocation(DR_FirstPassProgramIdId, "P");
    v_mat_loc_firstpass = glGetUniformLocation(DR_FirstPassProgramIdId, "V");
    m_mat_loc_firstpass = glGetUniformLocation(DR_FirstPassProgramIdId, "M");
    vm_mat_loc_firstpass = glGetUniformLocation(DR_FirstPassProgramIdId, "VM");

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









    /////////////////////////////////////////////////////////////////////////////////////
    //EDGE DETECTION PASS


    //vertex shader
    Shader dr_vertex_nfaa_edge(QApplication::applicationDirPath() +
                               "/shaders/nfaa_edge_vertex_shader.vsh",
                               GL_VERTEX_SHADER);
    if(dr_vertex_nfaa_edge.isCreated()){
        DR_EdgeDetectionPassVertexShaderId = dr_vertex_nfaa_edge.getShaderId();
        debugMessage("Deferred Renderer nfaa edge detection vertex shader compiled successful.");
    }
    else{
        debugMessage("Deferred Renderer nfaa edge detection vertex shader compiled failed!");
        debugMessage(dr_vertex_nfaa_edge.getError());
        return false;
    }


    //fragment shader
    Shader dr_fragment_nfaa_edge(QApplication::applicationDirPath() +
                               "/shaders/nfaa_edge_fragment_shader.fsh",
                               GL_FRAGMENT_SHADER);
    if(dr_fragment_nfaa_edge.isCreated()){
        DR_EdgeDetectionPassFragmentShaderId = dr_fragment_nfaa_edge.getShaderId();
        debugMessage("Deferred Renderer nfaa edge detection fragment shader compiled successful.");
    }
    else{
        debugMessage("Deferred Renderer nfaa edge detection fragment shader compiled failed!");
        debugMessage(dr_fragment_nfaa_edge.getError());
        return false;
    }





    //create program, link it and bind locs
    DR_EdgeDetectionPassProgramIdId = glCreateProgram();
    glAttachShader(DR_EdgeDetectionPassProgramIdId, DR_EdgeDetectionPassVertexShaderId);
    glAttachShader(DR_EdgeDetectionPassProgramIdId, DR_EdgeDetectionPassFragmentShaderId);



    glLinkProgram(DR_EdgeDetectionPassProgramIdId);

    //GLint linked;
    glGetProgramiv(DR_EdgeDetectionPassProgramIdId, GL_LINK_STATUS, &linked);
    if (linked){
        debugMessage("deferred renderer program pass nfaa edge detection linked");
    }
    else{
        debugMessage("deferred renderer program pass nfaa edge detection linking failed!!!");
        char messages[256];
        glGetProgramInfoLog(DR_EdgeDetectionPassProgramIdId, sizeof(messages), 0, &messages[0]);
        debugMessage(QString(messages));
        return false;
    }

    glUseProgram(DR_EdgeDetectionPassProgramIdId);

    ErrorCheckValue = glGetError();
    if (ErrorCheckValue != GL_NO_ERROR)
    {
        debugMessage("ERROR(3): Could not create the shaders: " + QString((char*) gluErrorString(ErrorCheckValue)));
        //exit(EXIT_FAILURE);
        return false;
    }

    win_size_loc_edgedetectionpass = glGetUniformLocation(DR_EdgeDetectionPassProgramIdId, "win_size");
    frame_switch_loc_edgedetectionpass = glGetUniformLocation(DR_EdgeDetectionPassProgramIdId, "frame_switch");
    function_loc_edgedetectionpass = glGetUniformLocation(DR_EdgeDetectionPassProgramIdId, "function");

    glUniform1i(glGetUniformLocation(DR_EdgeDetectionPassProgramIdId, "l_tex"), 0);
    glUniform1i(glGetUniformLocation(DR_EdgeDetectionPassProgramIdId, "d_tex"), 1);
    glUniform1i(glGetUniformLocation(DR_EdgeDetectionPassProgramIdId, "n_tex"), 2);
    glUniform1i(glGetUniformLocation(DR_EdgeDetectionPassProgramIdId, "p_tex"), 3);


    //EDGE DETECTION PASS pass end
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


    debugMessage("fbo 1");
    fbo_1 = 0;
    glGenFramebuffers (1, &fbo_1);
    glBindFramebuffer (GL_FRAMEBUFFER, fbo_1);


    //position texture
    glGenTextures (1, &fbo_1_tex_p);
    glBindTexture (GL_TEXTURE_2D, fbo_1_tex_p);
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
    glGenTextures (1, &fbo_1_tex_n);
    glBindTexture (GL_TEXTURE_2D, fbo_1_tex_n);
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
    glGenTextures (1, &fbo_1_tex_c);
    glBindTexture (GL_TEXTURE_2D, fbo_1_tex_c);
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


    //depth texture
    glGenTextures (1, &fbo_1_tex_d);
    glBindTexture (GL_TEXTURE_2D, fbo_1_tex_d);
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
      GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fbo_1_tex_p, 0
    );
    glFramebufferTexture2D (
      GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, fbo_1_tex_n, 0
    );
    glFramebufferTexture2D (
      GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, fbo_1_tex_c, 0
    );
    glFramebufferTexture2D (
      GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, GL_TEXTURE_2D, fbo_1_tex_d, 0
    );




    rb1 = 0;
    glGenRenderbuffers (1, &rb1);
    glBindRenderbuffer (GL_RENDERBUFFER, rb1);
    glRenderbufferStorage (
      GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 600, 400
    );
    glFramebufferRenderbuffer (
      GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rb1
    );

    GLenum draw_bufs[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3};
    glDrawBuffers (4, draw_bufs);

    // Always check that our framebuffer is ok
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
        debugMessage("framebuffer error in first fbo!");
        return false;
    }









    debugMessage("fbo 2");
    fbo_2 = 0;
    glGenFramebuffers (1, &fbo_2);
    glBindFramebuffer (GL_FRAMEBUFFER, fbo_2);


    //position texture
    glGenTextures (1, &fbo_2_tex_c);
    glBindTexture (GL_TEXTURE_2D, fbo_2_tex_c);
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
      GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fbo_2_tex_c, 0
    );






    rb2 = 0;
    glGenRenderbuffers (1, &rb2);
    glBindRenderbuffer (GL_RENDERBUFFER, rb2);
    glRenderbufferStorage (
      GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 600, 400
    );
    glFramebufferRenderbuffer (
      GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rb2
    );

    GLenum draw_bufs2[] = { GL_COLOR_ATTACHMENT0};
    glDrawBuffers (1, draw_bufs2);

    // Always check that our framebuffer is ok
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
        debugMessage("framebuffer error in second fbo!");
        return false;
    }





    debugMessage("fbo 3");
    fbo_3 = 0;
    glGenFramebuffers (1, &fbo_3);
    glBindFramebuffer (GL_FRAMEBUFFER, fbo_3);


    //position texture
    glGenTextures (1, &fbo_3_tex_c);
    glBindTexture (GL_TEXTURE_2D, fbo_3_tex_c);
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
      GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fbo_3_tex_c, 0
    );






    rb3 = 0;
    glGenRenderbuffers (1, &rb3);
    glBindRenderbuffer (GL_RENDERBUFFER, rb3);
    glRenderbufferStorage (
      GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 600, 400
    );
    glFramebufferRenderbuffer (
      GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rb3
    );

    GLenum draw_bufs3[] = { GL_COLOR_ATTACHMENT0};
    glDrawBuffers (1, draw_bufs3);

    // Always check that our framebuffer is ok
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
        debugMessage("framebuffer error in third fbo!");
        return false;
    }






    debugMessage("created buffers.");
    return true;
}

void Renderer::destroyShaders(){
    debugMessage("destroying shaders...");
    GLenum ErrorCheckValue = glGetError();

    glUseProgram(0);

    //old shader stuff
    /*
    glDetachShader(ProgramId, VertexShaderId);
    glDetachShader(ProgramId, FragmentShaderId);

    glDeleteShader(FragmentShaderId);
    glDeleteShader(VertexShaderId);

    glDeleteProgram(ProgramId);
    */

    //skybox pass
    glDetachShader(DR_SkyBoxPassProgramIdId, DR_SkyBoxPassVertexShaderId);
    glDetachShader(DR_SkyBoxPassProgramIdId, DR_SkyBoxPassFragmentShaderId);

    glDeleteShader(DR_SkyBoxPassFragmentShaderId);
    glDeleteShader(DR_SkyBoxPassVertexShaderId);

    glDeleteProgram(DR_SkyBoxPassProgramIdId);


    //buffercopy pass
    glDetachShader(DR_BufferCopyPassProgramIdId, DR_BufferCopyPassVertexShaderId);
    glDetachShader(DR_BufferCopyPassProgramIdId, DR_BufferCopyPassFragmentShaderId);

    glDeleteShader(DR_BufferCopyPassFragmentShaderId);
    glDeleteShader(DR_BufferCopyPassVertexShaderId);

    glDeleteProgram(DR_BufferCopyPassProgramIdId);


    //color pass (first pass)
    glDetachShader(DR_FirstPassProgramIdId, DR_FirstPassVertexShaderId);
    glDetachShader(DR_FirstPassProgramIdId, DR_FirstPassFragmentShaderId);

    glDeleteShader(DR_FirstPassFragmentShaderId);
    glDeleteShader(DR_FirstPassVertexShaderId);

    glDeleteProgram(DR_FirstPassProgramIdId);


    //DEFERRED LIGHTING PASS
    glDetachShader(DR_SecondPassProgramIdId, DR_SecondPassVertexShaderId);
    glDetachShader(DR_SecondPassProgramIdId, DR_SecondPassFragmentShaderId);

    glDeleteShader(DR_SecondPassFragmentShaderId);
    glDeleteShader(DR_SecondPassVertexShaderId);

    glDeleteProgram(DR_SecondPassProgramIdId);


    //DEFERRED AMBIENT PASS
    glDetachShader(DR_AmbientPassProgramIdId, DR_AmbientPassVertexShaderId);
    glDetachShader(DR_AmbientPassProgramIdId, DR_AmbientPassFragmentShaderId);

    glDeleteShader(DR_AmbientPassFragmentShaderId);
    glDeleteShader(DR_AmbientPassVertexShaderId);

    glDeleteProgram(DR_AmbientPassProgramIdId);


    //DEFERRED DIRECTIONALAMBIENT PASS
    glDetachShader(DR_DirectionalAmbientPassProgramIdId, DR_DirectionalAmbientPassVertexShaderId);
    glDetachShader(DR_DirectionalAmbientPassProgramIdId, DR_DirectionalAmbientPassFragmentShaderId);

    glDeleteShader(DR_DirectionalAmbientPassFragmentShaderId);
    glDeleteShader(DR_DirectionalAmbientPassVertexShaderId);

    glDeleteProgram(DR_DirectionalAmbientPassProgramIdId);


    //DEFERRED DEBUG PASS
    glDetachShader(DR_DebugPassProgramIdId, DR_DebugPassVertexShaderId);
    glDetachShader(DR_DebugPassProgramIdId, DR_DebugPassFragmentShaderId);

    glDeleteShader(DR_DebugPassFragmentShaderId);
    glDeleteShader(DR_DebugPassVertexShaderId);

    glDeleteProgram(DR_DebugPassProgramIdId);


    //DEFERRED edge detection pass
    glDetachShader(DR_EdgeDetectionPassProgramIdId, DR_EdgeDetectionPassVertexShaderId);
    glDetachShader(DR_EdgeDetectionPassProgramIdId, DR_EdgeDetectionPassFragmentShaderId);

    glDeleteShader(DR_EdgeDetectionPassFragmentShaderId);
    glDeleteShader(DR_EdgeDetectionPassVertexShaderId);

    glDeleteProgram(DR_EdgeDetectionPassProgramIdId);


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


        //FBO1

        //position texture
        glBindTexture (GL_TEXTURE_2D, fbo_1_tex_p);
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
        glBindTexture (GL_TEXTURE_2D, fbo_1_tex_n);
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
        glBindTexture (GL_TEXTURE_2D, fbo_1_tex_c);
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


        //depth texture
        glBindTexture (GL_TEXTURE_2D, fbo_1_tex_d);
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



        glBindRenderbuffer (GL_RENDERBUFFER, rb1);
        glRenderbufferStorage (
          GL_RENDERBUFFER, GL_DEPTH_COMPONENT, x, y
        );
        glFramebufferRenderbuffer (
          GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rb1
        );








        //FBO2

        //color texture 1
        glBindTexture (GL_TEXTURE_2D, fbo_2_tex_c);
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




        glBindRenderbuffer (GL_RENDERBUFFER, rb2);
        glRenderbufferStorage (
          GL_RENDERBUFFER, GL_DEPTH_COMPONENT, x, y
        );
        glFramebufferRenderbuffer (
          GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rb2
        );








        //FBO3

        //color texture 1
        glBindTexture (GL_TEXTURE_2D, fbo_3_tex_c);
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




        glBindRenderbuffer (GL_RENDERBUFFER, rb3);
        glRenderbufferStorage (
          GL_RENDERBUFFER, GL_DEPTH_COMPONENT, x, y
        );
        glFramebufferRenderbuffer (
          GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rb3
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

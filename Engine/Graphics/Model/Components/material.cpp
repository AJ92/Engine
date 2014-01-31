#include "material.h"

Material::Material(QString name,QString path) :
    Object(),
    mtl_name(name),
    mtl_path(path),
    mtl_ambient_loaded(false),
    mtl_diffuse_loaded(false),
    mtl_specular_loaded(false),
    mtl_bump_loaded(false),
    tex_slots(4)
{

}

Material::~Material(){
    qDebug("Material DESTRUCTOR CALLED");
    glDeleteTextures(tex_slots,gl_mtls);
    //might need to delete those...
    //delete [] mtl_xxxxxxxx_tex_data;
    qDebug("Material DESTRUCTOR FINISHED");
}

void Material::loadData(){
    //load data, GL not involved
    if(load_map_rgba(mtl_ambient_map_path, mtl_ambient_img, mtl_ambient_tex_data)){
        mtl_ambient_loaded = true;
    }
    if(load_map_rgba(mtl_diffuse_map_path, mtl_diffuse_img, mtl_diffuse_tex_data)){
        mtl_diffuse_loaded = true;
    }
    if(load_map_rgba(mtl_specular_map_path, mtl_specular_img, mtl_specular_tex_data)){
        mtl_specular_loaded = true;
    }
    if(load_map_rgba(mtl_bump_map_path, mtl_bump_img, mtl_bump_tex_data)){
        mtl_bump_loaded = true;
    }
}

void Material::loadGLdata(){
    // always 4 generated textures are not sooo good...
    gl_mtls = new GLuint[tex_slots];
    glGenTextures(tex_slots, gl_mtls);

    if(mtl_ambient_loaded){
        load_gl_map(0, mtl_ambient_img, mtl_ambient_tex_data);
    }
    if(mtl_diffuse_loaded){
        load_gl_map(1, mtl_diffuse_img, mtl_diffuse_tex_data);
    }
    if(mtl_specular_loaded){
        load_gl_map(2, mtl_specular_img, mtl_specular_tex_data);
    }
    if(mtl_bump_loaded){
        load_gl_map(3, mtl_bump_img, mtl_bump_tex_data);
    }
}

bool Material::load_gl_map(int slot, QImage &image, GLuint * &tex_data){
    glBindTexture(GL_TEXTURE_2D, gl_mtls[slot]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(), 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, tex_data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return true;
}


QString Material::get_name(){
    return mtl_name;
}

Vector3 Material::get_ambient_c(){
    return mtl_ambient_c;
}

Vector3 Material::get_diffuse_c(){
    return mtl_diffuse_c;
}

Vector3 Material::get_specular_c(){
    return mtl_specular_c;
}

float Material::get_specular_ns(){
    return mtl_specular_ns;
}

float Material::get_specular_ni(){
    return mtl_specular_ni;
}

float Material::get_transparency_d(){
    return mtl_transparency_d;
}

float Material::get_transparency_tr(){
    return mtl_transparency_tr;
}

Vector3 Material::get_transparency_tf(){
    return mtl_transparency_tf;
}


QString Material::get_ambient_map_name(){
    return mtl_ambient_map;
}

GLuint Material::get_ambient_map_texture(){
    return gl_mtls[0];
}

QString Material::get_diffuse_map_name(){
    return mtl_diffuse_map;
}

GLuint Material::get_diffuse_map_texture(){
    return gl_mtls[1];
}

QString Material::get_specular_map_name(){
    return mtl_specular_map;
}

GLuint Material::get_specular_map_texture(){
    return gl_mtls[2];
}

QString Material::get_bump_map_name(){
    return mtl_bump_map;
}

GLuint Material::get_bump_map_texture(){
    return gl_mtls[3];
}

GLuint* Material::get_map_textures(){
    return gl_mtls;
}

int Material::get_illumination(){
    return mtl_illumination;
}


//set
void Material::set_name(QString name){
    mtl_name = name;
}

void Material::set_ambient_c(Vector3 color){
    mtl_ambient_c = color;
}

void Material::set_diffuse_c(Vector3 color){
    mtl_diffuse_c = color;
}

void Material::set_specular_c(Vector3 color){
    mtl_specular_c = color;
}

void Material::set_specular_ns(float value){
    mtl_specular_ns = value;
}

void Material::set_specular_ni(float value){
    mtl_specular_ni = value;
}

void Material::set_transparency_d(float value){
    mtl_transparency_d = value;
}

void Material::set_transparency_tr(float value){
    mtl_transparency_tr = value;
}

void Material::set_transparency_tf(Vector3 color){
    mtl_transparency_tf = color;
}


void Material::set_ambient_map_name(QString map_name){
    mtl_ambient_map = map_name;
}

void Material::set_diffuse_map_name(QString map_name){
    mtl_diffuse_map = map_name;
}

void Material::set_specular_map_name(QString map_name){
    mtl_specular_map = map_name;
}

void Material::set_bump_map_name(QString map_name){
    mtl_bump_map = map_name;
}

void Material::set_illumination(int value){
    mtl_illumination = value;
}

void Material::set_ambient_map_path(QString map_path){
    mtl_ambient_map_path = map_path;
}

void Material::set_diffuse_map_path(QString map_path){
    mtl_diffuse_map_path = map_path;
}

void Material::set_specular_map_path(QString map_path){
    mtl_specular_map_path = map_path;
}

void Material::set_bump_map_path(QString map_path){
    mtl_bump_map_path = map_path;
}


bool Material::load_map_rgba(QString path, QImage &image, GLuint * &tex_data){
    image = QImage(path);

    //If QImage failed loading the image...
    if(image.isNull()){
        return false;
    }


    GLuint* pData = new GLuint[image.width() * image.height()];
    GLuint* sdata = (GLuint*)image.bits();
    GLuint* tdata = pData;

    for (int y = 0; y < image.height(); y++) {
        for (int x = 0; x < image.width(); x++) {
            *tdata = ((*sdata&255) << 16) | (((*sdata>>8)&255) << 8)
                    | (((*sdata>>16)&255) << 0) | (((*sdata>>24)&255) << 24);
            sdata++;
            tdata++;
        }
    }
    tex_data = pData;
    //delete [] pTexData;
    return true;
}

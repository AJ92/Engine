#include "material.h"

Material::Material(QString name,QString path) :
    Object(),
    mtl_name(name),
    mtl_path(path),
    tex_slots(4)
{
    // always 4 generated textures are not sooo good...
    gl_mtls = new GLuint[tex_slots];
    glGenTextures(tex_slots, gl_mtls);
}

Material::~Material(){
    qDebug("Material DESTRUCTOR CALLED");
    glDeleteTextures(tex_slots,gl_mtls);
    qDebug("Material DESTRUCTOR FINISHED");
}

bool Material::load_ambient_map(QString path){
    return load_map(path,0);
}

bool Material::load_diffuse_map(QString path){
    return load_map(path,1);
}

bool Material::load_specular_map(QString path){
    return load_map(path,2);
}

bool Material::load_bump_map(QString path){
    return load_map(path,3);
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
    return gl_mtls[0];
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


//wrapper function for texture loading...
bool Material::load_map(QString path, int slot){
    if(slot < 0 || slot >= tex_slots){
        qDebug("bool Material::load_map(QString path, int slot) slot %i is wrong...", slot);
        return false;
    }

    glBindTexture(GL_TEXTURE_2D, gl_mtls[slot]);

    if(path.endsWith(".png",Qt::CaseInsensitive)){
        if(load_map_rgba(path)){
            //qDebug("Texture map %i loaded from png file.", slot);
            return true;
        }
        else{
            qDebug("Texture map %i failed loaded from png file.", slot);
            return false;
        }
    }

    qDebug("Texture map %i loading failed...", slot);
    return false;

}


bool Material::load_map_rgba(QString path){
    QImage image = QImage(path);

    //If QImage failed loading the image...
    if(image.isNull()){
        return false;
    }


    GLuint* pTexData = new GLuint[image.width() * image.height()];
    GLuint* sdata = (GLuint*)image.bits();
    GLuint* tdata = pTexData;

    for (int y = 0; y < image.height(); y++) {
        for (int x = 0; x < image.width(); x++) {
            *tdata = ((*sdata&255) << 16) | (((*sdata>>8)&255) << 8)
                    | (((*sdata>>16)&255) << 0) | (((*sdata>>24)&255) << 24);
            sdata++;
            tdata++;
        }
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(), 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, pTexData);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    delete [] pTexData;
    return true;
}

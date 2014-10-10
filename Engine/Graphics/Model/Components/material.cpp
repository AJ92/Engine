#include "material.h"

Material::Material(QString name,QString path) :
    mtl_name(name),
    mtl_path(path),
    mtl_ambient_loaded(false),
    mtl_diffuse_loaded(false),
    mtl_specular_loaded(false),
    mtl_bump_loaded(false),
    tex_slots(4),
    loaded(false)
{

}

Material::~Material(){
    //qDebug("Material DESTRUCTOR CALLED");
    glDeleteTextures(tex_slots,gl_mtls);
    //might need to delete those...

    //qDebug("Material DESTRUCTOR FINISHED");
}

void Material::loadData(){
    //load data, GL not involved

    if(load_map_rgba(mtl_ambient_map_path, mtl_ambient_img)){
        mtl_ambient_loaded = true;
    }
    if(load_map_rgba(mtl_diffuse_map_path, mtl_diffuse_img)){
        mtl_diffuse_loaded = true;
    }
    if(load_map_rgba(mtl_specular_map_path, mtl_specular_img)){
        mtl_specular_loaded = true;
    }
    if(load_map_rgba(mtl_bump_map_path, mtl_bump_img)){
        mtl_bump_loaded = true;
    }

}

void Material::loadGLdata(){
    // always 4 generated textures are not sooo good...
    gl_mtls = new GLuint[tex_slots];
    glGenTextures(tex_slots, gl_mtls);

    qDebug("loading material");

    if(mtl_ambient_loaded){
        load_gl_map(0, mtl_ambient_img);
    }
    if(mtl_diffuse_loaded){
        load_gl_map(1, mtl_diffuse_img);
    }
    if(mtl_specular_loaded){
        load_gl_map(2, mtl_specular_img);
    }
    if(mtl_bump_loaded){
        load_gl_map(3, mtl_bump_img);
    }
    qDebug("loaded material!");
    loaded = true;
}

bool Material::isLoaded(){
    return loaded;
}

bool Material::load_gl_map(int slot, QImage &image){
    glBindTexture(GL_TEXTURE_2D, gl_mtls[slot]);
    /*
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(), 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, tex_data);
    */

    GLint width = image.width();
    GLint height = image.height();

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0,
                 GL_BGRA, GL_UNSIGNED_BYTE, (GLuint*)image.bits());

    qDebug("tex loaded...");


    //gen mipmaps
    GLint num_mipmaps = 16;

    glTexStorage2D(GL_TEXTURE_2D, num_mipmaps, GL_RGBA8, width, height);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_BGRA, GL_UNSIGNED_BYTE, (GLuint*)image.bits());
    glGenerateMipmap(GL_TEXTURE_2D);  //Generate num_mipmaps number of mipmaps here.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    //for mipmaps smooth
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    //mipmaps pixelated
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);


    //smooth
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //pixelated
    //glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    //glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    qDebug("mipmap generated...");


    image.~QImage();
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


bool Material::load_map_rgba(QString path, QImage &image){
    image = QImage(path);

    //If QImage failed loading the image...
    if(image.isNull()){
        return false;
    }
    //setting the QImage bits by hand... ARGB to BGRA
    //windows' openGL handles BGRA faster than RGBA in RGBA8 mode
    GLuint count=0, max=(GLuint)(image.height()*image.width());
    GLuint* p = (GLuint*)(image.bits());
    GLuint n;
    while( count<max )
    {
        n = p[count];   //n = ARGB      
        //to BGRA
        p[count] =    ((n     &255) << 0 )  |   //B
                     (((n>>8) &255) << 8 )  |   //G
                     (((n>>16)&255) << 16)  |   //R
                     (((n>>24)&255) << 24);     //A

        //RGBA
        /*
        p[count] =    ((n     &255) << 16)  |   //R
                     (((n>>8) &255) << 8 )  |   //G
                     (((n>>16)&255) << 0 )  |   //B
                     (((n>>24)&255) << 24);     //A
        */
        count++;
    }
    return true;
}

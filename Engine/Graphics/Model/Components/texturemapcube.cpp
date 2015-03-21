#include "texturemapcube.h"

TextureMapCube::TextureMapCube(
        QString name,
        QString front,
        QString back,
        QString top,
        QString bottom,
        QString left,
        QString right
) :
    TextureMap(name),
    texmap_front_path(front),
    texmap_back_path(back),
    texmap_top_path(top),
    texmap_bottom_path(bottom),
    texmap_left_path(left),
    texmap_right_path(right)
{

}

void TextureMapCube::loadData(){
    //load data, GL not involved
    qDebug("loading texmap cube data");
    if(texmap_front_path.compare("")!=0){
        if(load_map_rgba(texmap_front_path, texmap_front_img)){
            texmap_front_loaded = true;
        }
    }
    if(texmap_back_path.compare("")!=0){
        if(load_map_rgba(texmap_back_path, texmap_back_img)){
            texmap_back_loaded = true;
        }
    }
    if(texmap_top_path.compare("")!=0){
        if(load_map_rgba(texmap_top_path, texmap_top_img)){
            texmap_top_loaded = true;
        }
    }
    if(texmap_bottom_path.compare("")!=0){
        if(load_map_rgba(texmap_bottom_path, texmap_bottom_img)){
            texmap_bottom_loaded = true;
        }
    }
    if(texmap_left_path.compare("")!=0){
        if(load_map_rgba(texmap_left_path, texmap_left_img)){
            texmap_left_loaded = true;
        }
    }
    if(texmap_right_path.compare("")!=0){
        if(load_map_rgba(texmap_right_path, texmap_right_img)){
            texmap_right_loaded = true;
        }
    }
}

void TextureMapCube::loadGLdata(){
    glGenTextures(1, &gl_texmap);
    qDebug("loading texmap cube for openGL");

    if(texmap_front_loaded && texmap_back_loaded &&
            texmap_top_loaded && texmap_bottom_loaded &&
            texmap_left_loaded && texmap_right_loaded){
        if(!load_gl_map()){
            loaded = false;
            qDebug("fail");
        }
        else{
            qDebug("success");
        }
    }
    else{
        qDebug("at least one texture side could not be loaded!");
    }

    qDebug("loaded texmap cube for openGL!");
    loaded = true;
}

bool TextureMapCube::load_gl_map(){

    qDebug("loading gl maps!");

    glActiveTexture (GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, gl_texmap);

    GLint num_mipmaps = 16;
    GLint width = texmap_front_img.width();
    GLint height = texmap_front_img.height();


    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA8,
                 (GLint) texmap_front_img.width(),
                 (GLint) texmap_front_img.height(),
                 0, GL_BGRA, GL_UNSIGNED_BYTE, (GLuint*)texmap_front_img.bits());

    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA8,
                 (GLint) texmap_back_img.width(),
                 (GLint) texmap_back_img.height(),
                 0, GL_BGRA, GL_UNSIGNED_BYTE, (GLuint*)texmap_back_img.bits());

    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA8,
                 (GLint) texmap_top_img.width(),
                 (GLint) texmap_top_img.height(),
                 0, GL_BGRA, GL_UNSIGNED_BYTE, (GLuint*)texmap_top_img.bits());

    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA8,
                 (GLint) texmap_bottom_img.width(),
                 (GLint) texmap_bottom_img.height(),
                 0, GL_BGRA, GL_UNSIGNED_BYTE, (GLuint*)texmap_bottom_img.bits());

    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA8,
                 (GLint) texmap_left_img.width(),
                 (GLint) texmap_left_img.height(),
                 0, GL_BGRA, GL_UNSIGNED_BYTE, (GLuint*)texmap_left_img.bits());

    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA8,
                 (GLint) texmap_right_img.width(),
                 (GLint) texmap_right_img.height(),
                 0, GL_BGRA, GL_UNSIGNED_BYTE, (GLuint*)texmap_right_img.bits());

    qDebug("tex loaded...");


    //glTexStorage2D(GL_TEXTURE_CUBE_MAP, num_mipmaps, GL_RGBA8, width, height);
    //glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_BGRA, GL_UNSIGNED_BYTE, (GLuint*)texmap_img.bits());
    //glGenerateMipmap(GL_TEXTURE_2D);  //Generate num_mipmaps number of mipmaps here.


    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    //smooth
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    //pixelated
    //glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    //glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


    GLenum ErrorCheckValue = glGetError();
    if(ErrorCheckValue == GL_NO_ERROR)
        qDebug("Error");

    qDebug("tex params set...");

    //might want to delete the textures...
    //image.~QImage();
    return true;
}

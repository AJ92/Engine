#include "texturemap.h"


TextureMap::TextureMap(QString name) :
    texmap_name(name),
    texmap_path(""),
    loaded(false)
{

}

TextureMap::TextureMap(QString name, QString path) :
    texmap_name(name),
    texmap_path(path),
    loaded(false)
{
}

TextureMap::~TextureMap(){
    glDeleteTextures(1,&gl_texmap);
}

GLuint TextureMap::getGLTextureMap(){
    return gl_texmap;
}

bool TextureMap::isLoaded(){
    return loaded;
}


void TextureMap::loadData(){
    //load data, GL not involved
    qDebug("loading texmap data");
    if(texmap_path.compare("")!=0){
        if(load_map_rgba(texmap_path, texmap_img)){
            texmap_loaded = true;
        }
    }

}

void TextureMap::loadGLdata(){
    glGenTextures(1, &gl_texmap);
    qDebug("loading texmap for openGL");

    if(texmap_loaded){
        if(!load_gl_map()){
            loaded = false;
        }
    }

    qDebug("loaded texmap for openGL!");
    loaded = true;
}


bool TextureMap::load_gl_map(){
    glBindTexture(GL_TEXTURE_2D, gl_texmap);
    /*
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(), 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, tex_data);
    */

    GLint width = texmap_img.width();
    GLint height = texmap_img.height();

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0,
                 GL_BGRA, GL_UNSIGNED_BYTE, (GLuint*)texmap_img.bits());

    qDebug("tex loaded...");


    //gen mipmaps
    GLint num_mipmaps = 16;

    glTexStorage2D(GL_TEXTURE_2D, num_mipmaps, GL_RGBA8, width, height);
    //glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_BGRA, GL_UNSIGNED_BYTE, (GLuint*)texmap_img.bits());
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

    qDebug("mipmaps generated...");


    //delete the textures....
    //image.~QImage();
    return true;
}


QString TextureMap::get_name(){
    return texmap_name;
}


bool TextureMap::load_map_rgba(QString path, QImage &image){
    qDebug("    loading image...");
    qDebug("    " + path.toUtf8());

    image = QImage(path);

    //If QImage failed loading the image...
    if(image.isNull()){
        qDebug("    image could not be loaded...");
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

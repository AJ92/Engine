#ifndef TEXTUREMAP_H
#define TEXTUREMAP_H

//for openGL access to store the textures...
#include "Graphics/OpenGL/OpenGL.h"

#include "Object/object.h"

#include "mathematics.h"

#include <QString>
#include <QStringList>
#include <QImage>

class TextureMap : public Object
{
public:
    //load texture without a texmap e.g. color only
    TextureMap(QString name);
    //load texture with a texmap e.g. diffuse map
    TextureMap(QString name, QString path);
    virtual ~TextureMap();

    void loadData();
    void loadGLdata();

    GLuint getGLTextureMap();

    bool isLoaded();

    QString get_name();

private:

    QString texmap_name;
    QString texmap_path;
    bool texmap_loaded;

    QImage texmap_img;

    GLuint  gl_texmap;

    //load textures...
    bool load_gl_map(QImage &image);
    bool load_map_rgba(QString path, QImage &image);
    bool loaded;


};

#endif // TEXTUREMAP_H

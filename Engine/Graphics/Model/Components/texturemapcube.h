#ifndef TEXTUREMAPCUBE_H
#define TEXTUREMAPCUBE_H

#include "Graphics/Model/Components/texturemap.h"

class TextureMapCube : public TextureMap
{
public:
    TextureMapCube(
            QString name,
            QString front,
            QString back,
            QString top,
            QString bottom,
            QString left,
            QString right
    );

    void loadData();
    void loadGLdata();

protected:

    QString texmap_front_path;
    bool texmap_front_loaded;
    QImage texmap_front_img;

    QString texmap_back_path;
    bool texmap_back_loaded;
    QImage texmap_back_img;

    QString texmap_top_path;
    bool texmap_top_loaded;
    QImage texmap_top_img;

    QString texmap_bottom_path;
    bool texmap_bottom_loaded;
    QImage texmap_bottom_img;

    QString texmap_left_path;
    bool texmap_left_loaded;
    QImage texmap_left_img;

    QString texmap_right_path;
    bool texmap_right_loaded;
    QImage texmap_right_img;

    virtual bool load_gl_map();

};

#endif // TEXTUREMAPCUBE_H

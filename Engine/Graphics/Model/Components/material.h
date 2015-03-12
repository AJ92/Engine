#ifndef MATERIAL_H
#define MATERIAL_H

//for openGL access to store the textures...
#include "Graphics/OpenGL/OpenGL.h"

#include "Object/object.h"

#include "mathematics.h"

#include <QString>
#include <QStringList>
#include <QImage>

#include "Object/SmartPointer/smartpointer.h"
#include "Graphics/Model/Components/texturemap.h"

class Material : public Object
{
public:
    Material(QString name);
    virtual ~Material();


    enum TextureMapType{
        None            = 0x0001,   // No Texture   map defined...
        Ambient         = 0x0002,   // Ambient      map defined
        Diffuse         = 0x0004,   // Diffuse      map defined
        Specular        = 0x0008,   // Specular     map defined
        Bump            = 0x0010    // Bump         map defined
    };

    //load the bitmaps, and creates openGL textures
    //first set the paths...

    void loadData();
    void loadGLdata();

    QString get_name();

    void addTextureMap(SP<TextureMap> textureMap, TextureMapType type);
    bool isTextureMapSet(TextureMapType type);
    SP<TextureMap> getTextureMap(TextureMapType type);

    bool isLoaded();

private:

    bool loaded;

    QString mtl_name;

    int loaded_texmaps;

    SP<TextureMap> ambient_textureMap;
    SP<TextureMap> diffuse_textureMap;
    SP<TextureMap> specular_textureMap;
    SP<TextureMap> bump_textureMap;

};

#endif // MATERIAL_H

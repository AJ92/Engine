#include "material.h"

Material::Material(QString name) :
    mtl_name(name),
    loaded_texmaps(None),
    loaded(false)
{

}

Material::~Material(){

}

void Material::loadData(){
    if((loaded_texmaps & Ambient) == Ambient){
        qDebug("Material: loading Ambient map");
        ambient_textureMap->loadData();
    }
    if((loaded_texmaps & Diffuse) == Diffuse){
        qDebug("Material: loading Diffuse map");
        diffuse_textureMap->loadData();
    }
    if((loaded_texmaps & Specular) == Specular){
        qDebug("Material: loading Specular map");
        specular_textureMap->loadData();
    }
    if((loaded_texmaps & Bump) == Bump){
        qDebug("Material: loading Bump map");
        bump_textureMap->loadData();
    }
}

void Material::loadGLdata(){
    if((loaded_texmaps & Ambient) == Ambient){
        ambient_textureMap->loadGLdataGammaCorrected();
    }
    if((loaded_texmaps & Diffuse) == Diffuse){
        diffuse_textureMap->loadGLdataGammaCorrected();
    }
    if((loaded_texmaps & Specular) == Specular){
        specular_textureMap->loadGLdataGammaCorrected();
    }
    if((loaded_texmaps & Bump) == Bump){
        bump_textureMap->loadGLdata();
    }
    loaded = true;
}

bool Material::isLoaded(){
    return loaded;
}

QString Material::get_name(){
    return mtl_name;
}

void Material::addTextureMap(SP<TextureMap> textureMap, TextureMapType type){
    if(type == Ambient){
        ambient_textureMap = textureMap;
        loaded_texmaps = loaded_texmaps | type;
        return;
    }
    else if(type == Diffuse){
        diffuse_textureMap = textureMap;
        loaded_texmaps = loaded_texmaps | type;
        return;
    }
    else if(type == Specular){
        specular_textureMap = textureMap;
        loaded_texmaps = loaded_texmaps | type;
        return;
    }
    else if(type == Bump){
        bump_textureMap = textureMap;
        loaded_texmaps = loaded_texmaps | type;
        return;
    }
}

bool Material::isTextureMapSet(TextureMapType type){
    if((loaded_texmaps & type) == type){
        return true;
    }
    return false;
}

SP<TextureMap> Material::getTextureMap(TextureMapType type){
    if(type == Ambient){
        return ambient_textureMap;
    }
    else if(type == Diffuse){
        return diffuse_textureMap;
    }
    else if(type == Specular){
        return specular_textureMap;
    }
    else if(type == Bump){
        return bump_textureMap;
    }
}


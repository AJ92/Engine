#ifndef MATERIAL_H
#define MATERIAL_H

#include <QVector3D>
#include <QString>
#include <QImage>

#include "World/resources.h"
#include <GLES2/gl2.h>


//0+0+0+0     no maps initialized                                                 = 0
//1+0+0+0     ambient_map                                         initialized     = 1
//0+2+0+0                   diffuse_map                           initialized     = 2
//1+2+0+0     ambient_map + diffuse_map                           initialized     = 3
//0+0+4+0                                 specular_map            initialized     = 4
//1+0+4+0     ambient_map                 specular_map            initialized     = 5
//0+2+4+0                   diffuse_map + specular_map            initialized     = 6
//1+2+4+0     ambient_map + diffuse_map + specular_map            initialized     = 7
//0+0+0+8                                                bump_map initialized     = 8
//1+0+0+8     ambient_map                              + bump_map initialized     = 9
//0+2+0+8                   diffuse_map                + bump_map initialized     = 10
//1+2+0+8     ambient_map + diffuse_map                + bump_map initialized     = 11
//0+0+4+8                                 specular_map + bump_map initialized     = 12
//1+0+4+8     ambient_map               + specular_map + bump_map initialized     = 13
//0+2+4+8                   diffuse_map + specular_map + bump_map initialized     = 14
//1+2+4+8     ambient_map + diffuse_map + specular_map + bump_map initialized     = 15

//1 == ambient; 2 == diffuse; 3 == specular; 4 == bump;
#define no_map      0
#define map_1       1
#define map_2       2
#define map_1_2     3
#define map_3       4
#define map_1_3     5
#define map_2_3     6
#define map_1_2_3   7
#define map_4       8
#define map_1_4     9
#define map_2_4     10
#define map_1_2_4   11
#define map_3_4     12
#define map_1_3_4   13
#define map_2_3_4   14
#define map_1_2_3_4 15


class Resources;
class Material
{
public:
    Material(QString name,QString path);
    ~Material();

    /*
    void inc_count();
    void dec_count();
    long get_count();
    */

    //init
    int init();


    int get_maps_loaded_stat();

    //get
    QString     get_material_name();
    QVector3D   get_mtl_ambient_c();
    QVector3D   get_mtl_diffuse_c();
    QVector3D   get_mtl_specular_c();
    float       get_mtl_specular_ns();
    float       get_mtl_specular_ni();
    float       get_mtl_transparency_d();
    float       get_mtl_transparency_tr();
    QVector3D   get_mtl_transparency_tf();


    QString     get_mtl_ambient_map();
    GLuint      get_mtl_ambient_tex_map();
    //space for bitmap
    QString     get_mtl_diffuse_map();
    GLuint      get_mtl_diffuse_tex_map();
    //space for bitmap
    QString     get_mtl_specular_map();
    GLuint      get_mtl_specular_tex_map();
    //space for bitmap
    QString     get_mtl_bump_map();
    GLuint      get_mtl_bump_tex_map();
    //space for bitmap
    GLuint*     get_mtl_tex_maps();
    int         get_mtl_illumination();


    //set
    void        set_mtl_name(QString mtl_name);
    void        set_mtl_ambient_c(QVector3D color);
    void        set_mtl_diffuse_c(QVector3D color);
    void        set_mtl_specular_c(QVector3D color);
    void        set_mtl_specular_ns(float value);
    void        set_mtl_specular_ni(float value);
    void        set_mtl_transparency_d(float value);
    void        set_mtl_transparency_tr(float value);
    void        set_mtl_transparency_tf(QVector3D color);
    void        set_mtl_ambient_map(QString map_name);
    //space for bitmap
    void        set_mtl_diffuse_map(QString map_name);
    //space for bitmap
    void        set_mtl_specular_map(QString map_name);
    //space for bitmap
    void        set_mtl_bump_map(QString map_name);
    //space for bitmap
    void        set_mtl_illumination(int value);




    int         update_tex_map(QString texture_path, int tex_map);
    int         update_tex_map(QImage *texture, int tex_map);
    int         delete_tex_map(int tex_map);


    static long next_id();
    long get_id();

private:

    static long next_identifier;
    const long identifier;

    Resources *resman;
    QString material_name;
    QString material_path;


    QVector3D mtl_ambient_c;
    QVector3D mtl_diffuse_c;
    QVector3D mtl_specular_c;
    float mtl_specular_ns;
    float mtl_specular_ni;
    float mtl_transparency_d;
    float mtl_transparency_tr;
    QVector3D mtl_transparency_tf;


    QString mtl_ambient_map;
    GLuint  mtl_ambient_tex_map;

    QString mtl_diffuse_map;
    GLuint  mtl_diffuse_tex_map;

    QString mtl_specular_map;
    GLuint  mtl_specular_tex_map;

    QString mtl_bump_map;
    GLuint  mtl_bump_tex_map;

    GLuint*  gl_mtls;

    int maps_loaded_stat;

    int mtl_illumination;


    void load_image(QString image_path,GLuint &mtl_map_id,bool &ok);

    GLuint load_img_data_dds_rgba(QString image_path,bool &ok);
    GLuint load_img_data_qimg_rgba(QString image_path, bool &ok);


    void update_image(QString image_path,GLuint mtl_map_id,bool &ok);
    void update_image(QImage *image,GLuint mtl_map_id,bool &ok);

    GLuint update_img_data_dds_rgba(QString image_path, GLuint mtl_map_id, bool &ok);
    GLuint update_img_data_qimg_rgba(QString image_path, GLuint mtl_map_id, bool &ok);
    GLuint update_img_data_qimg(QImage *image, GLuint mtl_map_id, bool &ok);

    void generate_mipmaps(GLuint mtl_map_id);
    void set_bilinear_texture_filtering();
    void set_trilinear_texture_filtering();
};
#endif // MATERIAL_H

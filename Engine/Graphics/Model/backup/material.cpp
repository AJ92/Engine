#include "material.h"

#define get_size(a) ( sizeof ( a ) / sizeof ( *a ) )

long Material::next_identifier = 0;

Material::Material(QString name,QString path):
    identifier(next_id())
{
    qDebug("\n\nnew material\nMATERIAL ID: %d",identifier);

    material_name = name;
    material_path = path;
    mtl_ambient_c = QVector3D(1.0,1.0,1.0);
    mtl_diffuse_c = QVector3D(1.0,1.0,1.0);
    mtl_specular_c = QVector3D(1.0,1.0,1.0);
    mtl_specular_ns = 10.0;
    mtl_specular_ni = 1.5;
    mtl_transparency_d = 1.0;
    mtl_transparency_tr = 0.0;
    mtl_transparency_tf = QVector3D(1.0,1.0,1.0);
    mtl_ambient_map = "";
    //space for bitmap
    mtl_diffuse_map = "";
    //space for bitmap
    mtl_specular_map = "";
    //space for bitmap
    mtl_bump_map = "";
    //space for bitmap

    maps_loaded_stat = 0;

    mtl_illumination = 0;
}

Material::~Material(){
    qDebug("Material DESTRUCTOR CALLED");
    glDeleteTextures(4,gl_mtls);
    qDebug("Material DESTRUCTOR FINISHED");
}

long Material::next_id(){
    next_identifier++;
    return next_identifier;
}

long Material::get_id(){
    return identifier;
}

int Material::get_maps_loaded_stat(){
    return maps_loaded_stat;
}

GLuint Material::load_img_data_dds_rgba(QString image_path,bool &ok){
    QFile file(image_path);
    if ( file.open(QIODevice::ReadOnly)) {
        qDebug("loading " + image_path.toUtf8() + ":");
    }
    else{
        qDebug("error in opening dds image");
    }
    QDataStream in( &file );
    in.setByteOrder( QDataStream::LittleEndian );

    //check for right header !!!
    qDebug("header:");
    qint64 cmp_header = 533118272580;
    qint64 header;
    in >> header;
    qDebug(QString::number(header).toUtf8());
    if(header != cmp_header){
        ok = false;
        return -1;
    }
    qint8 n;
    for(int i = 0; i<4; i++){
        in >> n;
    }
    qint32 x;
    in >> x;
    qDebug("x size: " + QString::number(x).toUtf8());
    qint32 y;
    in >> y;
    qDebug("y size: " + QString::number(y).toUtf8());

    int image_data[x*y*4];

    for(int i = 0; i<108; i++){
        in >> n;
    }

    //after 128 bytes the data of the image actually begins:
    int j = 0;
    quint8 o;
    while(!in.atEnd()){
        in >> o;
        //qDebug("R: " + QString::number(o).toUtf8());
        image_data[j] = o;
        in >> o;
        //qDebug("G: " + QString::number(o).toUtf8());
        image_data[j+1] = o;
        in >> o;
        //qDebug("B: " + QString::number(o).toUtf8());
        image_data[j+2] = o;
        in >> o;
        //qDebug("A: " + QString::number(o).toUtf8()+ "\n");
        image_data[j+3] = o;
        j+=4;
    }
    GLuint mtl_map;
    glGenTextures(1, &mtl_map);
    glBindTexture(GL_TEXTURE_2D, mtl_map);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    ok = true;
    return mtl_map;
}

GLuint Material::update_img_data_dds_rgba(QString image_path, GLuint mtl_map_id, bool &ok){
    QFile file(image_path);
    if ( file.open(QIODevice::ReadOnly)) {
        qDebug("loading " + image_path.toUtf8() + ":");
    }
    else{
        qDebug("error in opening dds image");
    }
    QDataStream in( &file );
    in.setByteOrder( QDataStream::LittleEndian );

    //check for right header !!!
    qDebug("header:");
    qint64 cmp_header = 533118272580;
    qint64 header;
    in >> header;
    qDebug(QString::number(header).toUtf8());
    if(header != cmp_header){
        ok = false;
        return -1;
    }
    qint8 n;
    for(int i = 0; i<4; i++){
        in >> n;
    }
    qint32 x;
    in >> x;
    qDebug("x size: " + QString::number(x).toUtf8());
    qint32 y;
    in >> y;
    qDebug("y size: " + QString::number(y).toUtf8());

    int image_data[x*y*4];

    for(int i = 0; i<108; i++){
        in >> n;
    }

    //after 128 bytes the data of the image actually begins:
    int j = 0;
    quint8 o;
    while(!in.atEnd()){
        in >> o;
        //qDebug("R: " + QString::number(o).toUtf8());
        image_data[j] = o;
        in >> o;
        //qDebug("G: " + QString::number(o).toUtf8());
        image_data[j+1] = o;
        in >> o;
        //qDebug("B: " + QString::number(o).toUtf8());
        image_data[j+2] = o;
        in >> o;
        //qDebug("A: " + QString::number(o).toUtf8()+ "\n");
        image_data[j+3] = o;
        j+=4;
    }

    glBindTexture(GL_TEXTURE_2D, mtl_map_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    ok = true;
    return mtl_map_id;
}

GLuint Material::load_img_data_qimg_rgba(QString image_path,bool &ok){
    //GLuint mtl_map;
    //glGenTextures(1, &mtl_map);
    //glBindTexture(GL_TEXTURE_2D, mtl_map);
    QImage image = QImage(image_path);
    qDebug("x size: " + QString::number(image.width()).toUtf8());
    qDebug("y size: " + QString::number(image.height()).toUtf8());
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
    ok = true;
    //return mtl_map;
    return 1;
}

GLuint Material::update_img_data_qimg_rgba(QString image_path,GLuint mtl_map_id, bool &ok){
    glBindTexture(GL_TEXTURE_2D, mtl_map_id);
    QImage image = QImage(image_path);
    qDebug("x size: " + QString::number(image.width()).toUtf8());
    qDebug("y size: " + QString::number(image.height()).toUtf8());
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
    ok = true;
    return mtl_map_id;
}

GLuint Material::update_img_data_qimg(QImage *image, GLuint mtl_map_id, bool &ok){
    glBindTexture(GL_TEXTURE_2D, mtl_map_id);
    qDebug("x size: " + QString::number(image->width()).toUtf8());
    qDebug("y size: " + QString::number(image->height()).toUtf8());
    GLuint* pTexData = new GLuint[image->width() * image->height()];
    GLuint* sdata = (GLuint*)image->bits();
    GLuint* tdata = pTexData;

    for (int y = 0; y < image->height(); y++) {
        for (int x = 0; x < image->width(); x++) {
            *tdata = ((*sdata&255) << 16) | (((*sdata>>8)&255) << 8)
                    | (((*sdata>>16)&255) << 0) | (((*sdata>>24)&255) << 24);
            sdata++;
            tdata++;
        }
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->width(), image->height(), 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, pTexData);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    delete [] pTexData;
    ok = true;
    return mtl_map_id;
}

int Material::delete_tex_map(int tex_map){
    int ret = 0;

    if(tex_map == 1){
        mtl_ambient_map = "none";
        glDeleteTextures(1,&mtl_ambient_tex_map);

        qDebug("   ambient map deleted...");
        ret+=1;
    }
    else if(tex_map == 2){
        mtl_diffuse_map = "none";
        glDeleteTextures(1,&mtl_diffuse_tex_map);

        qDebug("   diffuse map deleted...");
        ret+=2;
    }
    else if(tex_map == 4){
        mtl_specular_map = "none";
        glDeleteTextures(1,&mtl_specular_tex_map);

        qDebug("   specular map deleted...");
        ret+=4;
    }
    else if(tex_map == 8){
        mtl_bump_map = "none";
        glDeleteTextures(1,&mtl_bump_tex_map);

        qDebug("   bump map deleted...");
        ret+=8;
    }

    return ret;
}

void Material::load_image(QString image_path,GLuint &mtl_map_id,bool &ok){
    QStringList image_path_parts = image_path.split(".",QString::SkipEmptyParts);
    if(image_path_parts.isEmpty()){
        ok=false;
        return;
    }
    if(image_path_parts.last() == "png"){
        //new
        glBindTexture(GL_TEXTURE_2D, mtl_map_id);
        //mtl_map_id = load_img_data_qimg_rgba(image_path,ok);
        load_img_data_qimg_rgba(image_path,ok);
        qDebug("Tex_map: " + QString::number(mtl_map_id).toUtf8());
        return;
    }
    if(image_path_parts.last() == "dds"){
        mtl_map_id = load_img_data_dds_rgba(image_path,ok);
        return;
    }

    ok = false;
    return;
}


void Material::update_image(QString image_path,GLuint mtl_map_id,bool &ok){
    QStringList image_path_parts = image_path.split(".",QString::SkipEmptyParts);
    if(image_path_parts.isEmpty()){
        ok=false;
        return;
    }
    if(image_path_parts.last() == "png"){
        update_img_data_qimg_rgba(image_path,mtl_map_id,ok);
        qDebug("Tex_map: " + QString::number(mtl_map_id).toUtf8());
        return;
    }
    if(image_path_parts.last() == "dds"){
        update_img_data_dds_rgba(image_path,mtl_map_id,ok);
        return;
    }

    ok = false;
    return;
}

void Material::update_image(QImage *image,GLuint mtl_map_id,bool &ok){
    if(image->isNull()){
        ok=false;
        return;
    }
    else{
        update_img_data_qimg(image,mtl_map_id,ok);
        qDebug("Tex_map: " + QString::number(mtl_map_id).toUtf8());
        return;
    }


    ok = false;
    return;
}

int Material::update_tex_map(QImage *texture, int tex_map){
    int ret = 0;

    bool loaded = false; //checks if texture data got loaded properly...

    if(tex_map == 1){
        mtl_ambient_map = "updated using a QImage";
        update_image(texture,get_mtl_ambient_tex_map(),loaded);
        if(loaded==false){
            ret+=0;
        }
        else{
            qDebug("   ambient map updated...");
            ret+=1;
        }
    }
    else if(tex_map == 2){
        mtl_diffuse_map = "updated using a QImage";
        update_image(texture,get_mtl_diffuse_tex_map(),loaded);
        if(loaded==false){
            ret+=0;
        }
        else{
            qDebug("   diffuse map updated...");
            ret+=2;
        }
    }
    else if(tex_map == 4){
        mtl_specular_map = "updated using a QImage";
        update_image(texture,get_mtl_specular_tex_map(),loaded);
        if(loaded==false){
            ret+=0;
        }
        else{
            qDebug("   specular map updated...");
            ret+=4;
        }
    }
    else if(tex_map == 8){
        mtl_bump_map = "updated using a QImage";
        update_image(texture,get_mtl_bump_tex_map(),loaded);
        if(loaded==false){
            ret+=0;
        }
        else{
            qDebug("   bump map updated...");
            ret+=8;
        }
    }

    return ret;
}

int Material::update_tex_map(QString texture_path, int tex_map){
    int ret = 0;

    bool loaded = false; //checks if texture data got loaded properly...

    if(tex_map == 1){
        mtl_ambient_map = texture_path;
        update_image(mtl_ambient_map,get_mtl_ambient_tex_map(),loaded);
        if(loaded==false){
            ret+=0;
        }
        else{
            qDebug("   ambient map updated...");
            ret+=1;
        }
    }
    else if(tex_map == 2){
        mtl_diffuse_map = texture_path;
        update_image(mtl_diffuse_map,get_mtl_diffuse_tex_map(),loaded);
        if(loaded==false){
            ret+=0;
        }
        else{
            qDebug("   diffuse map updated...");
            ret+=2;
        }
    }
    else if(tex_map == 4){
        mtl_specular_map = texture_path;
        update_image(mtl_specular_map,get_mtl_specular_tex_map(),loaded);
        if(loaded==false){
            ret+=0;
        }
        else{
            qDebug("   specular map updated...");
            ret+=4;
        }
    }
    else if(tex_map == 8){
        mtl_bump_map = texture_path;
        update_image(mtl_bump_map,get_mtl_bump_tex_map(),loaded);
        if(loaded==false){
            ret+=0;
        }
        else{
            qDebug("   bump map updated...");
            ret+=8;
        }
    }

    return ret;
}

int Material::init(){
    int ret = 0;

    bool loaded = false; //checks if texture data got loaded properly...

    //returns pointer to image data array in RGBA format 0-255 and bool true
        //if it succed to load the file
    //returns pointer to empty data array with one uninitialized value and bool false
        //if it failes to load the file

    // always 4 generated textures are not sooo good...
    gl_mtls = new GLuint[4];
    glGenTextures(4, gl_mtls);


    load_image(material_path + mtl_ambient_map,gl_mtls[0],loaded);
    if(loaded==false){
        ret+=0;
    }
    else{
        qDebug("   ambient map loaded...");
        ret+=1;
    }
    load_image(material_path + mtl_diffuse_map,gl_mtls[1],loaded);
    if(loaded==false){
        ret+=0;
    }
    else{
        generate_mipmaps(gl_mtls[1]);
        set_trilinear_texture_filtering();
        qDebug("   diffuse map loaded...");
        ret+=2;
    }
    load_image(material_path + mtl_specular_map,gl_mtls[2],loaded);
    if(loaded==false){
        ret+=0;
    }
    else{
        qDebug("   specular map loaded...");
        ret+=4;
    }
    load_image(material_path + mtl_bump_map,gl_mtls[3],loaded);
    if(loaded==false){
        ret+=0;
    }
    else{
        qDebug("   bump map loaded...");
        ret+=8;
    }

    /*
    load_image(":/" + mtl_ambient_map,mtl_ambient_tex_map,loaded);
    if(loaded==false){
        ret+=0;
    }
    else{
        qDebug("   ambient map loaded...");
        ret+=1;
    }
    load_image(":/" + mtl_diffuse_map,mtl_diffuse_tex_map,loaded);
    if(loaded==false){
        ret+=0;
    }
    else{
        qDebug("   diffuse map loaded...");
        ret+=2;
    }
    load_image(":/" + mtl_specular_map,mtl_specular_tex_map,loaded);
    if(loaded==false){
        ret+=0;
    }
    else{
        qDebug("   specular map loaded...");
        ret+=4;
    }
    load_image(":/" + mtl_bump_map,mtl_bump_tex_map,loaded);
    if(loaded==false){
        ret+=0;
    }
    else{
        qDebug("   bump map loaded...");
        ret+=8;
    }
    */

    return ret;
}

/*
void Material::inc_count(){
    count+=1;
}

void Material::dec_count(){
    count-=1;
}

long Material::get_count(){
    return count;
}
*/

QString     Material::get_material_name(){
    return material_name;
}
QVector3D   Material::get_mtl_ambient_c(){
    return mtl_ambient_c;
}
QVector3D   Material::get_mtl_diffuse_c(){
    return mtl_diffuse_c;
}
QVector3D   Material::get_mtl_specular_c(){
    return mtl_specular_c;
}
float       Material::get_mtl_specular_ns(){
    return mtl_specular_ns;
}
float       Material::get_mtl_specular_ni(){
    return mtl_specular_ni;
}
float       Material::get_mtl_transparency_d(){
    return mtl_transparency_d;
}
float       Material::get_mtl_transparency_tr(){
    return mtl_transparency_tr;
}
QVector3D   Material::get_mtl_transparency_tf(){
    return mtl_transparency_tf;
}
QString     Material::get_mtl_ambient_map(){
    return mtl_ambient_map;
}
GLuint     Material::get_mtl_ambient_tex_map(){
    //return mtl_ambient_tex_map;
    return gl_mtls[0];
}
//space for bitmap
QString     Material::get_mtl_diffuse_map(){
    return mtl_diffuse_map;
}
GLuint     Material::get_mtl_diffuse_tex_map(){
    //return mtl_diffuse_tex_map;
    return gl_mtls[1];
}
//space for bitmap
QString     Material::get_mtl_specular_map(){
    return mtl_specular_map;
}
GLuint     Material::get_mtl_specular_tex_map(){
    //return mtl_specular_tex_map;
    return gl_mtls[2];
}
//space for bitmap
QString     Material::get_mtl_bump_map(){
    return mtl_bump_map;
}
GLuint     Material::get_mtl_bump_tex_map(){
    //return mtl_bump_tex_map;
    return gl_mtls[3];
}
GLuint*    Material::get_mtl_tex_maps(){
    return gl_mtls;
}

//space for bitmap
int         Material::get_mtl_illumination(){
    return mtl_illumination;
}


void   Material::set_mtl_name(QString mtl_name){
    material_name = mtl_name;
}
void   Material::set_mtl_ambient_c(QVector3D color){
    mtl_ambient_c = color;
}
void   Material::set_mtl_diffuse_c(QVector3D color){
    mtl_diffuse_c = color;
}
void   Material::set_mtl_specular_c(QVector3D color){
    mtl_specular_c = color;
}
void   Material::set_mtl_specular_ns(float value){
    mtl_specular_ns = value;
}
void   Material::set_mtl_specular_ni(float value){
    mtl_specular_ni = value;
}
void   Material::set_mtl_transparency_d(float value){
    mtl_transparency_d = value;
}
void   Material::set_mtl_transparency_tr(float value){
    mtl_transparency_tr = value;
}
void   Material::set_mtl_transparency_tf(QVector3D color){
    mtl_transparency_tf = color;
}
void   Material::set_mtl_ambient_map(QString map_name){
    mtl_ambient_map = map_name;
}
//space for bitmap
void   Material::set_mtl_diffuse_map(QString map_name){
    mtl_diffuse_map = map_name;
}
//space for bitmap
void   Material::set_mtl_specular_map(QString map_name){
    mtl_specular_map = map_name;
}
//space for bitmap
void   Material::set_mtl_bump_map(QString map_name){
    mtl_bump_map = map_name;
}
//space for bitmap
void   Material::set_mtl_illumination(int value){
    mtl_illumination = value;
}

void Material::generate_mipmaps(GLuint mtl_map_id){
    glGenerateMipmap(GL_TEXTURE_2D);
}

void Material::set_bilinear_texture_filtering(){
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Material::set_trilinear_texture_filtering(){
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

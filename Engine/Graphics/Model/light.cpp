#include "light.h"

Light::Light(const Light &light) :
    Object()
{
    isReady = false;
    diffuse_c = Vector3(1.0,1.0,1.0);
    specular_c = Vector3(0.3,0.4,0.5);
    //copy all the stuff to this new object
    //lets hope const keyword won't make trouble
}


Light::Light() :
    Object()
{
    diffuse_c = Vector3(1.0,1.0,1.0);
    specular_c = Vector3(0.3,0.4,0.5);
    isReady = false;
    //set some vars as default
}

Light::~Light(){

}


void Light::setDiffuseColor(double r, double g, double b){
    diffuse_c = Vector3(r,g,b);
}

void Light::setSpecularColor(double r, double g, double b){
    specular_c = Vector3(r,g,b);
}

Vector3 Light::getDiffuseColor(){
    return diffuse_c;
}

Vector3 Light::getSpecularColor(){
    return specular_c;
}

void Light::set_data(const Light &light){
    //not done yet
}

void Light::instance_from(Light &light){
    //later
}

bool Light::equalData(const Light &light) const{
    //done later
    if(1){
        return true;
    }
    return false;
}

//override + overload bam
bool Light::equal(const Light &light) const{
    if(this->id() == light.id()){
        return true;
    }
    return false;
}

//friend
bool operator==(const Light &light1, const Light &light2){
    return light1.equal(light2);
}

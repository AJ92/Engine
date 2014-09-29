#ifndef LIGHT_H
#define LIGHT_H

#include "Object/object.h"
#include "Graphics/Model/model.h"
#include "mathematics.h"

class Light : public Object
{
public:
    //create a copy from mdl...
    Light(const Light & light);
    //construct empty Model
    Light();


    //light properties
    void setDiffuseColor(double r, double g, double b);
    void setSpecularColor(double r, double g, double b);

    Vector3 getDiffuseColor();
    Vector3 getSpecularColor();

    void set_data(const Light &light);
    void instance_from(Light &light);

    bool equalData(const Light &light) const;

    //override + overload bam
    bool equal(const Light &light) const;

    friend bool operator==(const Light &light1, const Light &light2);

private:
    //some lightvars which we gonna use later

    bool isReady;

    Vector3 diffuse_c;
    Vector3 specular_c;
};

#endif // LIGHT_H

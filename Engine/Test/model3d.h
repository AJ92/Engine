#ifndef MODEL3D_H
#define MODEL3D_H

#include "Components/Components.h"

class Model3D : public GraphicsComponent
{
public:
    Model3D();
    virtual void update(GameObject &gameobject);

};

#endif // MODEL3D_H

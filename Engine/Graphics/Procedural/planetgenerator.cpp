#include "planetgenerator.h"

PlanetGenerator::PlanetGenerator()
{
}

Planet * PlanetGenerator::generatePlanet(int random_seed){
    //create a basic cube which gonna be subdivided
    QVector<Vector3> base_vertices;

    //front
    base_vertices.append(Vector3(-1.0, 1.0,-1.0));
    base_vertices.append(Vector3( 1.0, 1.0,-1.0));
    base_vertices.append(Vector3(-1.0,-1.0,-1.0));

    base_vertices.append(Vector3(-1.0,-1.0,-1.0));
    base_vertices.append(Vector3( 1.0, 1.0,-1.0));
    base_vertices.append(Vector3( 1.0,-1.0,-1.0));


    //back (swap vertex 2 and 3 of the two triangles)
    base_vertices.append(Vector3(-1.0, 1.0, 1.0));
    base_vertices.append(Vector3(-1.0,-1.0, 1.0));
    base_vertices.append(Vector3( 1.0, 1.0, 1.0));

    base_vertices.append(Vector3(-1.0,-1.0, 1.0));
    base_vertices.append(Vector3( 1.0,-1.0, 1.0));
    base_vertices.append(Vector3( 1.0, 1.0, 1.0));


    //left
    base_vertices.append(Vector3(-1.0, 1.0, 1.0));
    base_vertices.append(Vector3(-1.0, 1.0,-1.0));
    base_vertices.append(Vector3(-1.0,-1.0, 1.0));

    base_vertices.append(Vector3(-1.0,-1.0, 1.0));
    base_vertices.append(Vector3(-1.0, 1.0,-1.0));
    base_vertices.append(Vector3(-1.0,-1.0,-1.0));


    //right (swap vertex 2 and 3 of the two triangles)
    base_vertices.append(Vector3( 1.0, 1.0, 1.0));
    base_vertices.append(Vector3( 1.0,-1.0, 1.0));
    base_vertices.append(Vector3( 1.0, 1.0,-1.0));

    base_vertices.append(Vector3( 1.0,-1.0, 1.0));
    base_vertices.append(Vector3( 1.0,-1.0,-1.0));
    base_vertices.append(Vector3( 1.0, 1.0,-1.0));


    //top
    base_vertices.append(Vector3(-1.0, 1.0, 1.0));
    base_vertices.append(Vector3( 1.0, 1.0, 1.0));
    base_vertices.append(Vector3(-1.0, 1.0,-1.0));

    base_vertices.append(Vector3( 1.0, 1.0, 1.0));
    base_vertices.append(Vector3( 1.0, 1.0,-1.0));
    base_vertices.append(Vector3(-1.0, 1.0,-1.0));


    //bottom (swap vertex 2 and 3 of the two triangles)
    base_vertices.append(Vector3(-1.0,-1.0, 1.0));
    base_vertices.append(Vector3(-1.0,-1.0,-1.0));
    base_vertices.append(Vector3( 1.0,-1.0, 1.0));

    base_vertices.append(Vector3( 1.0,-1.0, 1.0));
    base_vertices.append(Vector3(-1.0,-1.0,-1.0));
    base_vertices.append(Vector3( 1.0,-1.0,-1.0));


}

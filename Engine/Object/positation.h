#ifndef POSITATION_H
#define POSITATION_H

#include "Object/object.h"
#include "Math/mathematics.h"
#include "Event/eventtransmitter.h"

class Event;


class Positation : virtual public EventTransmitter
{
public:
    Positation();

    void set_data(const Positation &Positation);

    Vector3 getPosition();
    void set_position(double x, double y, double z);
    void set_position(Vector3 position);

    void set_rotation(double angle, double x, double y, double z);
    void set_rotation(double angle, Vector3 rotation);

    void clear_rotation();
    void add_rotation(double angle, double x, double y, double z);
    void add_rotation(double angle, Vector3 rotation);

    void set_rotation_matrix(Matrix4x4 mat);

    void set_scale(double x, double y, double z);
    void set_scale(Vector3 scale);

    Vector3 get_scale();

    double get_size();

    Matrix4x4 get_model_matrix();

protected:

    bool matrix_changed;

    //spherical bound...
    double size;

    //translation, scale, rotation...
    Vector3 pos;
    double angle;
    Vector3 rot;
    Vector3 scl;

    Matrix4x4 mat_pos;
    Matrix4x4 mat_rot;
    Matrix4x4 mat_scl;

    Matrix4x4 mat_m;

    void set_matrix_pos();
    void set_matrix_rot();
    void set_matrix_scl();

    void build_model_matrix();

    void sendMovedEvent();

    void debugMessage(QString message);
};

#endif // POSITATION_H

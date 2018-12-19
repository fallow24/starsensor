#ifndef VECTOR_H
#define VECTOR_H

class Vec3D {

    public:
        double x,y,z;
        Vec3D operator+(Vec3D);
        Vec3D operator*(Vec3D);
        double dot(Vec3D);
};

#endif
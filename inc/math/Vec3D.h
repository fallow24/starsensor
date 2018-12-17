#ifndef VECTOR_H
#define VECTOR_H

class Vec3D {

    public:
        float x,y,z;
        Vec3D operator+(Vec3D);
        Vec3D operator*(Vec3D);
        float dot(Vec3D);
};

#endif
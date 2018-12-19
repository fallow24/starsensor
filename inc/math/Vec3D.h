#ifndef VECTOR_H
#define VECTOR_H

class Vec3D {

    public:
        float x,y,z;
        Vec3D();
        Vec3D(float,float,float);
        //float operator[]();
        Vec3D operator+(Vec3D);
        Vec3D operator*(Vec3D);
        Vec3D operator*(float);
        Vec3D operator/(float scalar);
        float dot(Vec3D);
        float norm();
        Vec3D cross(Vec3D);
};

#endif
#include "Vec3D.h"

Vec3D Vec3D::operator+(Vec3D v) {
    Vec3D* result = new Vec3D();
    result->x = this->x + v.x;
    result->y = this->y + v.y;
    result->z = this->z + v.z;
    return *result;
}

Vec3D Vec3D::operator*(Vec3D v) {
    Vec3D* result = new Vec3D();
    result->x = this->x * v.x;
    result->y = this->y * v.y;
    result->z = this->z * v.z;
    return *result;
}

float Vec3D::dot(Vec3D v) {
    return this->x * v.x + this->y * v.y + this->z * v.z;
}
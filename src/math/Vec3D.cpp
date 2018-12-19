#include "Vec3D.h"
#include <math.h>

Vec3D::Vec3D() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Vec3D::Vec3D(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vec3D Vec3D::operator+(Vec3D v) {
    return *new Vec3D(this->x + v.x, this->y + v.y, this->z + v.z);
}

Vec3D Vec3D::operator*(Vec3D v) {
    return *new Vec3D(this->x * v.x, this->y * v.y, this->z * v.z);
}

Vec3D Vec3D::operator*(float scalar) {
    return *new Vec3D(scalar * this->x, scalar * this->y, scalar * this->z);
}

Vec3D Vec3D::operator/(float scalar) {
    return *new Vec3D(this->x / scalar, this->y / scalar, this->z / scalar);
}

float Vec3D::dot(Vec3D v) {
    return this->x * v.x + this->y * v.y + this->z * v.z;
}

Vec3D Vec3D::cross(Vec3D v) {
    return *new Vec3D(this->y * v.z - this->z * v.y, this->z * v.x - this->x * v.z, this->x * v.y - this->y *v.x);
}

float Vec3D::norm() {
    return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}
#ifndef MATRIX_H
#define MATRIX_H

#include "Vec3D.h"

class Matrix {
    public:
        int lines, columns;
        double* matrix;
        Matrix(int, int);
        Matrix(Vec3D, Vec3D, Vec3D);
        void printMatrix();
        Matrix operator*(Matrix);
        Matrix transpose();
        double trace();
};

#endif
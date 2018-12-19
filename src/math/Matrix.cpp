#include "Matrix.h"
#include <stdio.h>

Matrix::Matrix(int lines, int columns) {
    this->lines = lines;
    this->columns = columns;
    this->matrix = new double[lines * columns];
    for(int i = 0; i < lines * columns; i++) matrix[i] = 0;
}


Matrix::Matrix(Vec3D x, Vec3D y, Vec3D z) {
    this->lines = 3;
    this->columns = 3;
    this->matrix = new double[9];
    matrix[0] = x.x;
    matrix[1] = y.x;
    matrix[2] = z.x;
    matrix[3] = x.y;
    matrix[4] = y.y;
    matrix[5] = z.y;
    matrix[6] = x.z;
    matrix[7] = y.z;
    matrix[8] = z.z;
}

void Matrix::printMatrix() {
    printf("[   ");
    for(int i = 0; i < this->lines * this->columns; i++) {
        if(i % this->columns == 0 && i != 0) printf("]\n[   ");
        printf("%f   ", this->matrix[i]);
    }
    printf("]\n");
}

Matrix Matrix::operator*(Matrix m) {
    Matrix* result = new Matrix(this->lines, m.columns);
    if(this->columns == m.lines) {
        int a = 0;
        int b = 0;
        for(int i = 0; i < this->lines * m.columns; i++) {
            if(i % m.columns == 0 && i != 0) {
                a += this->columns;
                b -= m.columns;
            }
            float sum = 0;
            for(int j = 0; j < this->columns; j++) {
                sum += this->matrix[j + a] * m.matrix[j * m.columns + b];
            }
            b++;
            result->matrix[i] = sum;
        }
    }
    return *result;
}

Matrix Matrix::transpose() {
    Matrix* result = new Matrix(this->columns, this->lines);
    int a = 0;
    int b = 0;
    for(int i = 0; i < this->lines * this->columns; i++){
        if(i % this->lines == 0 && i != 0) {
            a++;
            b += this->lines;
        }
        result->matrix[i] = this->matrix[(i - b) * this->columns + a];
    }
    return *result;
}





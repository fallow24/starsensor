#ifndef QUATERNION_H
#define QUATERNION_H

class Quaternion {
    public:
        float q0, q1, q2, q3;
        Quaternion(float, float, float, float);
        void printQuat();
};

#endif
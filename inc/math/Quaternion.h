#ifndef QUATERNION_H
#define QUATERNION_H

class Quaternion {
    public:
        double q0, q1, q2, q3;
        Quaternion(double,double,double,double);
        void printQuat();
};

#endif
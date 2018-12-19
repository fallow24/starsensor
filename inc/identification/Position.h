#ifndef POSITION_H
#define POSITION_H

#include "Vec3D.h"
#include "Matrix.h"
#include "Stars.h"
#include "Quaternion.h"

struct vectorTuple {
    Vec3D v1;
    Vec3D v2;
};

class Position {
    public:
        static vectorTuple calcStarVecs(Pointf*, Pointf*, int, int);
        static vectorTuple getStarsWithID(Database, int, int);
        static Matrix calcRotationMatrix(vectorTuple, vectorTuple);
        static Quaternion rotToQuat(Matrix rot);
};

#endif
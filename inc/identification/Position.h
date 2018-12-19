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
        vectorTuple calcStarVecs(Pointf*, Pointf*, int, int);
        vectorTuple getStarsWithID(Database, int, int);
        Matrix calcRotationMatrix(vectorTuple, vectorTuple);
        Quaternion rotToQuat(Matrix rot);
};

#endif
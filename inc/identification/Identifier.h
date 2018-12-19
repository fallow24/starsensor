#ifndef IDENTIFY_H
#define IDENTIFY_H

#include "Roi.h"
#include "Database.h"
#include "Triangles.h"
#include "SeqReg.h"
#include <math.h>

struct Angles
{
    double alpha1, alpha2, beta;
};

struct PointfAndAngle
{
    Pointf* p;
    double angle;
};

class Identifier
{
    public:
        Triangle bestfit(Triangles triangledb, int dbsize, Angles* angles);
        Pointf* findmiddlest(Pointf** focuspoints, int numberofstars, int width, int height);
        Angles* angles(Pointf* middlest, Pointf** focuspoints, int numberofstars);
        Pointf* geta1();
        Pointf* geta2();
    private:
        Pointf* a1;
        Pointf* a2;

};

#endif
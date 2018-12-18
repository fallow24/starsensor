#ifndef IDENTIFY_H
#define IDENTIFY_H

#include "Roi.h"
#include "Database.h"
#include "Triangles.h"
#include "SeqReg.h"
#include <math.h>

struct Angles
{
    float alpha1, alpha2, beta;
};

struct PointfAndAngle
{
    Pointf* p;
    float angle;
};

class Identifier
{
    public:
        static Triangle bestfit(Triangles triangledb, int dbsize, Angles* angles);
        static Pointf* findmiddlest(Pointf** focuspoints, int numberofstars, int width, int height);
        static Angles* angles(Pointf* middlest, Pointf** focuspoints, int numberofstars);
    private:


};

#endif
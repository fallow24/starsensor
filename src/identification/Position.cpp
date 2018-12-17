#include "Position.h"
#include "Vec3D.h"

vectorTuple Position::calcStarVecs(Pointf* M, Pointf* S1, int width, int height) {
    vectorTuple* sv = new vectorTuple;
    sv->v1.x = (M->x - width/2) * 5.8E-6;
    sv->v1.y = (M->y - height/2) * 5.8E-6;
    sv->v1.z = 25E-3;

    sv->v2.x = (S1->x - width/2) * 5.8E-6;
    sv->v2.y = (S1->y - height/2) * 5.8E-6;
    sv->v2.z = 25E-3;

    return *sv;
}


vectorTuple Position::getStarsWithID(Database stardb, int ID1, int ID2) {
    Star s1 = stardb.getStarWithID(0, stardb.size() - 1, ID1);
    Star s2 = stardb.getStarWithID(0, stardb.size() - 1, ID2);
    vectorTuple* vT = new vectorTuple;
    vT->v1.x = s1.x;
    vT->v1.y = s1.y;
    vT->v1.z = s1.z;
    vT->v2.x = s2.x;
    vT->v2.y = s2.y;
    vT->v2.z = s2.z;
    return *vT;
}

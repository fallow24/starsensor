#include "Position.h"
#include "Vec3D.h"

// calculate staVec3D Vec3D::operator/(float scalar)Vec3D Vec3D::operator/(float scalar)r vectors
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

//get the star vectors in ECI
vectorTuple Position::getStarsWithID(Database stardb, int ID1, int ID2) {
    Star s1 = stardb.getStarWithID(ID1);
    Star s2 = stardb.getStarWithID(ID2);
    vectorTuple* vT = new vectorTuple;
    vT->v1.x = s1.x;
    vT->v1.y = s1.y;
    vT->v1.z = s1.z;
    vT->v2.x = s2.x;
    vT->v2.y = s2.y;
    vT->v2.z = s2.z;
    return *vT;
}

//calculate rotation matrix
Matrix Position::calcRotationMatrix(vectorTuple senframe, vectorTuple eciframe) {
    Vec3D r1 = senframe.v1 / senframe.v1.norm();
    Vec3D r2 = senframe.v1.cross(senframe.v2 / (senframe.v1.cross(senframe.v2)).norm());
    Vec3D r3 = senframe.v2.cross(senframe.v1);

    Vec3D t1 = eciframe.v1 / eciframe.v1.norm();
    Vec3D t2 = eciframe.v1.cross(eciframe.v2 / (eciframe.v1.cross(eciframe.v2)).norm());
    Vec3D t3 = eciframe.v2.cross(eciframe.v1);

    Matrix* m1 = new Matrix(r1, r2, r3);
    Matrix* m2 = new Matrix(t1, t2, t3);
    Matrix rot = *m1 * (*m2).transpose();

    return rot;
}

//transform rotationmatrix to quaternion
Quaternion Position::rotToQuat(Matrix rot) {
    return *new Quaternion(0,0,0,0);//ToDo
}
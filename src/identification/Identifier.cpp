#include "Identifier.h"

Pointf* Identifier::findmiddlest(Pointf** focuspoints, int numberofstars, int width, int height)
{
    //fining middlest point
    Pointf* middlest; 
    int x, y, dist, min_dist = 200000000;
    for(int i = 0; i < numberofstars; i++)
    {
        x = focuspoints[i]->x - width/2.0;
        y = focuspoints[i]->y - height/2.0;
        dist = sqrt(x*x + y*y);
        if(dist < min_dist) {
            min_dist = dist;
            middlest = focuspoints[i];
        }
    }
    return middlest;
}

Angles* Identifier::angles(Pointf* middlest, Pointf** focuspoints, int numberofstars)
{
    Angles* angs = new Angles;

    //calculating all angles
    PointfAndAngle* pointfandangles = new PointfAndAngle[numberofstars - 1];
    double angle, dotproduct, abss1, abss2, z_2;
    int j = 0;
    for(int i = 0; i < numberofstars; i++)
    {   
        //Angle calculation
        z_2 = 25000.0 / 5.8 * 25000.0 / 5.8; //z-component
        dotproduct = middlest->x * focuspoints[i]->x + middlest->y * focuspoints[i]->y + z_2;
        abss1 = sqrt(middlest->x * middlest->x + middlest->y * middlest->y + z_2);
        abss2 = sqrt(focuspoints[i]->x * focuspoints[i]->x + focuspoints[i]->y * focuspoints[i]->y + z_2);
        angle = acos(dotproduct / (abss1 * abss2));

        if(fabs(angle) > 0.000001) {
            pointfandangles[j].angle = angle;
            pointfandangles[j].p = focuspoints[i]; 
        
            j++;
        }
    }

    //finding alpha1 and alpha2 (smalest angles)
    PointfAndAngle a1, a2;
    a1.angle = 2*M_PI; //maximum angle is 2PI
    a2.angle = 2*M_PI;
    for(int i = 0; i < numberofstars - 1; i++)
    {
        if(pointfandangles[i].angle < a1.angle) {
            a2 = a1;
            a1 = pointfandangles[i];
        } else if(pointfandangles[i].angle < a2.angle) {
            a2 = pointfandangles[i];
        } 
    }

    //find beta

    //Vector M_A1
    double M_A1_x = a1.p->x - middlest->x;
    double M_A1_y = a1.p->y - middlest->y;

    //Vector M_A2
    double M_A2_x = a2.p->x - middlest->x;
    double M_A2_y = a2.p->y - middlest->y;
    
    dotproduct = M_A1_x * M_A2_x + M_A1_y * M_A2_y;
    double absMA1 = sqrt(M_A1_x * M_A1_x + M_A1_y * M_A1_y);
    double absMA2 = sqrt(M_A2_x * M_A2_x + M_A2_y * M_A2_y);

    double beta = acos(dotproduct / (absMA1 * absMA2));

    //All angles are calculated now
    angs->alpha1 = a1.angle;
    angs->alpha2 = a2.angle;
    angs->beta = beta;

    this->a1 = a1.p;
    this->a2 = a2.p;

    return angs;
}

Triangle Identifier::bestfit(Triangles triangledb, int dbsize, Angles* angles)
{
    //error of alpha1, alpha2, beta
    double e, e_a1, e_a2, e_b, e_min = 10000000;
    Triangle tmp, bestFit;
    //itterating the triangle database
    for(int i = 0; i < dbsize; i++) {
        tmp = triangledb.data()[i];

        //claculate all partial-relative errors
        e_a1 = (tmp.alpha1 - angles->alpha1) / tmp.alpha1;
        e_a2 = (tmp.alpha2 - angles->alpha2) /tmp.alpha2;
        e_b = (tmp.beta - angles->beta) /tmp.beta;

        //relative error
        e = fabs(e_a1) + fabs(e_a2) + fabs(e_b);

        //if the relative error is smaller than the current relativ error
        if(e < e_min) {
            e_min = fabs(e);
            bestFit = tmp; //bestfit is the current triangle
        }
    }

    return bestFit;
}

Pointf* Identifier::geta1()
{
    return this->a1;
}

Pointf* Identifier::geta2()
{
    return this->a2;
}
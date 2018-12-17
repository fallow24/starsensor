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
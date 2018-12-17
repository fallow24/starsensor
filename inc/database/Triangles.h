#ifndef TRIANGLES_H
#define TRIANGLES_H

#include "Database.h"

struct Triangle 
{
    Star id1;
    Star id2;
    Star id3;
    float alpha1;
    float alpha2;
    float beta;
};

class Triangles
{
    public:
        Triangles(Database db)
        {   
            printf("Generating possible triangle database");
            fflush(stdout); //flushing the out stream BEFORE calculating
            database = new Triangle[db.size()];
            for(int i = 0; i < db.size(); i++)
            {
                if(i % 1000 == 0) {
                    printf(".");
                    fflush(stdout); //flushing the out stream BEFORE calculating
                }
                Startuple t = db.findnearest(i);
            
                database[i].id1 = db.stardata()[i];
                database[i].id2 = t.s1;
                database[i].id3 = t.s2;
                database[i].alpha1 = radiansToDegrees(db.anglebetween(db.stardata()[i], t.s1));
                database[i].alpha2 = radiansToDegrees(db.anglebetween(db.stardata()[i], t.s2));
                database[i].beta = radiansToDegrees(db.calcbeta(db.stardata()[i], t.s1, t.s2));
            }
            printf(" done!\n");
        }
        Triangle* data();

    private:
        Triangle* database;

};

#endif
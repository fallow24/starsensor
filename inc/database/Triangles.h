#ifndef TRIANGLES_H
#define TRIANGLES_H

#include "Database.h"

struct Triangle 
{
    Star id1;
    Star id2;
    Star id3;
    double alpha1;
    double alpha2;
    double beta;
};

class Triangles
{
    public:
        Triangles(Database db)
        {   
            printf("Generating possible triangle database 0%% [          ] 100%%");
            printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
            fflush(stdout); //flushing the out stream BEFORE calculating
            database = new Triangle[db.size()];
            int integ = 10, debug;
            Star m;
            for(int i = 0; i < db.size(); i++)
            {
                if(((double)i / db.size() * 100) > integ) {
                    integ+=10;
                    printf("#");
                    fflush(stdout); //flushing the out stream BEFORE calculating
                }
                Startuple* t = db.findnearest(i);
            
                database[i].id1 = db.stardata()[i];
                database[i].id2 = t->s1;
                database[i].id3 = t->s2;
                debug = db.stardata()[i].id;
                m = db.stardata()[i];
                database[i].alpha1 = (db.anglebetween(db.stardata()[i], t->s1));
                database[i].alpha2 = (db.anglebetween(db.stardata()[i], t->s2));
                database[i].beta = (db.calcbeta(db.stardata()[i], t->s1, t->s2));
            }
            printf(" done!\n");
        }
        Triangle* data();

    private:
        Triangle* database;

};

#endif
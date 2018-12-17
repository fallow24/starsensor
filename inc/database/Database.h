#ifndef DATABASE_H
#define DATABASE_H

#include <fstream>
#include <sstream>
#include <string>
#include <math.h> 

#define MAX_MAGNITUDE 6.5

#define degreesToRadians(angleDegrees) ((angleDegrees) * M_PI / 180.0)
#define radiansToDegrees(angleRadians) ((angleRadians) * 180.0 / M_PI)

using namespace std;

struct Star
{
    int id; 
    float x, y, z;
    float magnitude;
};

struct Startuple
{
    Star s1;
    Star s2;
};

class Database
{
    public:
        Database(const char* filename){
            printf("Reading star database...");
            fflush(stdout);
            this->filename = filename;
            this->data = readFromFile();
            this->stars = str2db();
            printf(" done!\n");
        }
        string strdata();
        Star* stardata();
        int size();
        Star getStarWithID(int, int, int);

        //should be private
        float calcbeta(Star s, Star t1, Star t2);
        Startuple findnearest(int index);
        float anglebetween(Star s1, Star s2);

    private: 
        const char* filename;
        string data;
        int values;
        Star* stars;
        string readFromFile();
        Star* str2db();
};

#endif
#ifndef SEQREG_H
#define SEQREG_H

#include<vector>

class Point
{
    public: 
        int x, y;
        Point(int x, int y){
            this->x = x;
            this->y = y;
        };
        Point(){};
};

class SeqReg
{
    private:
        Point *e, *a, *b, *c, *d, *f, *g, *h, *i;
        int numberOfStars;
        
    public:
        Point* neighbour(int i, int j, int width, int height);
        std::vector<Point*> * classify(int* pixels, int width, int height);
        int getNumberOfStars();
};

#endif
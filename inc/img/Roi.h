#ifndef ROI_H
#define ROI_H

#include <vector>
#include "SeqReg.h"
#include "Bmp.h"

struct Pointf
{
    float x, y;
    Pointf(float x, float y) : x(x), y(y) { }
};

class Roi 
{
    public:
        static Pointf* focus(int* grayscaledImage, int width, std::vector<Point*> star);
        static int determineSize(Point* brightest, int* grayscaledImage, int width);
        static Point* brightestPixel(int* grayscaledImage, int width, std::vector<Point*> star);
        static Pointf** focuspoints(int* grayscaledImage, int width, std::vector<Point*> *stars, int numberofstars);
    private:
        Roi(){}
};

#endif
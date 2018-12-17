#include "Roi.h"

//find a focuspoint from a star
Pointf* Roi::focus(int* grayscaledImage, int width, std::vector<Point*> star)
{
    //use a ROI with size nxn
    Point* brightest = brightestPixel(grayscaledImage, width, star);
    int n = determineSize(brightest, grayscaledImage, width); //with advanced dynamic roi

    float sumx = 0, sumy = 0, sumh = 0, h;
    //sum of all x, y and h
    for(int x = brightest->x - n/2; x < brightest->x + n/2; x++) {
        for(int y = brightest->y - n/2; y < brightest->y + n/2; y++) {
            h = grayscaledImage[y * width + x]; //function h(x,y) is brightnes
            sumx += x * h;
            sumy += y * h;
            sumh += h;
        }
    }

    //calc focuspoint (x, y) in float
    float x = sumx/sumh;
    float y = sumy/sumh;
    Pointf* focuspoint = new Pointf(x, y);

    return focuspoint;
}

//advanced dynamic ROI 
int Roi::determineSize(Point* brightest, int* grayscaledImage, int width)
{
    int brightness = grayscaledImage[brightest->y * width + brightest->x];
    return brightness / 34 + 3; //mindestesgroesse für ein ROI ist 3x3, maximalgroesse ist 10x10
}

Point* Roi::brightestPixel(int* grayscaledImage, int width, std::vector<Point*> star) 
{
    Point *result, *brightest;

    //find the pixel with the maximum magnitude
    int max_magnitude = 0, magnitude;
    for(int i = 0; i < star.size(); i++) {
            magnitude = grayscaledImage[star[i]->y * width + star[i]->x];
            if(magnitude > max_magnitude)
            {
                max_magnitude = magnitude;
                brightest = star[i];
            }
    }

    result = new Point(brightest->x, brightest->y);
    return result;
}

Pointf** Roi::focuspoints(int* grayscaledImage, int width, std::vector<Point*> *stars, int numberofstars)
{
    Pointf** focuspoints = new Pointf*[numberofstars]; 

    //calculate focus points
    for(int i = 0; i < numberofstars; i++) {
        focuspoints[i] = Roi::focus(grayscaledImage, width, stars[i]);
    }

    return focuspoints;
}